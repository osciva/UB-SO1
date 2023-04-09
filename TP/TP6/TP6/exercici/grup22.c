#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXVALUE 1000

void sigusr1(int signo) // Funció que s'executa quan el procés pare rep una senyal.
{
  printf("El pare ha rebut el SIGUSR1\n");
}

void sigusr2(int signo) // // Funció que s'executa quan el procés fill rep una senyal.
{
  printf("El fill ha rebut el SIGUSR2\n");
}

int main(void)
{
    int i, num_values = 1000, value, sum, fd[2];
    int ret, parent_pid, child_pid;

    pipe(fd);  // Creem la canonada.

    ret = fork();  

    if (ret == 0) { // child

        parent_pid = getppid();
      
        /* Inserir codi aqui per gestionar senyals */
        signal(SIGUSR2, sigusr2);

        /* Esperar a rebre senyal del pare */
        pause();
        
        i = 0;
        sum = 0;

        for(i = 0; i < num_values; i++){  // Aqui llegim des de la canonada els valors (enters aleatoris) que ens ha enviat el pare.
            read(fd[0], &value, sizeof(int));
            sum += value;
        }
        printf("El fill escriu el resultat: %d\n", sum);

        /* Escriure el valor de la suma a la canonada */
        write(fd[1], &sum, sizeof(int));
        

        /* Avisar al pare que s'han escrit els valors, enviem la senyal SIGUR1 */ 
        kill(parent_pid, SIGUSR1);


        exit(0);
    } else { // parent

        /* Inserir codi aqui per gestionar senyals */
        signal(SIGUSR1, sigusr1);
        child_pid = ret;

        /* Random seed */
        srand(time(NULL));

        i = 0;
        
        
        while (i < num_values) {  // Generem valors aleatoris i els inserim a la canonada.
            value = rand() % MAXVALUE + 1;
            i++;
            write(fd[1], &value, sizeof(int));
        }

        /* Inserir codi aqui per esperar senyal del pare */
        kill(child_pid, SIGUSR2);
        
        pause();  // Fem pause() fins que el procés fill hagi acabat de sumar els valors aleatoris.

        printf("El pare espera la suma...\n");
        sleep(5);

        /* Llegir el resultat des de la canonada */
        read(fd[0], &sum, sizeof(int));  
        printf("El fill em diu que la suma es: %d\n", sum);

        wait(NULL);
    }

    return 0;
}