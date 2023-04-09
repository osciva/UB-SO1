#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXVALUE 1000

void sigusr1(int signo)
{
  printf("El pare ha rebut el SIGUSR1\n");
}

void sigusr2(int signo)
{
  printf("El fill ha rebut el SIGUSR2\n");
}

int main(void)
{
    int i, num_values, value, sum, fd[2]; 
    int ret, parent_pid, child_pid;

    num_values = 1000;   

    pipe(fd);

    ret = fork();


   
    if (ret == 0) { // child
      
        /* Inserir codi aqui per gestionar senyals */
	parent_pid = getppid();

        signal(SIGUSR2, sigusr2);

        /* Esperar a rebre senyal del pare */
        printf("Waiting for signal...\n");
	pause();
        /* Llegir el nombre de valors que ens envia el pare */

        i=0;
        sum = 0;
        for(i=0; i < num_values; i++) {
            /* Llegir valors de la canonada i fer la suma */
	    read(fd[0], &value, sizeof(int));
            sum += value;	    
            
        }
        write(fd[1], &sum, sizeof(int));
	printf("Envio SIGUSR1 al pare %d\n", parent_pid);
	kill(parent_pid, SIGUSR1);

	    


        /* Avisar al pare que s'han escrit els valors */ 
	printf("Missatge enviat");

        exit(0);
    } else { // parent

        /* Inserir codi aqui per gestionar senyals */
	child_pid = ret;


	signal(SIGUSR1, sigusr1);
	

        /* Random seed */
        srand(time(NULL));

        
       
        /* Escriure aquest valor a la canonada */
        
	
        i=0;
        for(i=0; i < num_values; i++) {  
            /* Generar valor aleatori i inserir a la canonada */
            value = rand() % MAXVALUE + 1;
	    write(fd[1], &value, sizeof(int));

            
        }

        printf("Envio SIGUSR2 al fill %d\n", child_pid);
	kill(child_pid, SIGUSR2);

	pause();




        /* Inserir codi aqui per esperar senyal del pare */


        printf("El pare espera la suma...\n");
	sleep(2);
	
	

        /* Llegir el resultat */
	read(fd[0], &sum, sizeof(int));

        printf("El fill em diu que la suma es: %d\n", sum);

	printf("Missatge rebut");

        wait(NULL);
    }

    return 0;
}
