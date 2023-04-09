#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// Variables globals
unsigned long int passengers_count, trip_seconds, num_elem;
int sr1 = 0, sr2 = 0;
int fd_col8, fd_col9;

// Inicialitzem els mètodes
int get_column_fields_taxis(int *column8, int *column9, char *line);
void productor(char* file_name, int n, int ret8, int ret9);
void consumidor8(int n);
void consumidor9(int n);
void sigusr1(int signo){sr1 = 1;}
void sigusr2(int signo){sr2 = 1;}

void productor(char* file_name, int n, int ret8, int ret9){

    FILE *file;
    char line[256];
    int invalid, value8, value9;
    int child1_pid, child2_pid;
    num_elem = 0;
    passengers_count = 0;
    trip_seconds = 0;

    // Obrim el fitxer com a lectura
    file = fopen(file_name, "r");
    // Tractem el possible error en obrir el fitxer
    if (!file) {
        printf("ERROR: No es pot obrir el fitxer '%s'\n", file_name);
        exit(1);
    }

    //Obrim els fitxers fills com a write only
    fd_col8 = open("col8.bin", O_WRONLY | O_CREAT | O_TRUNC, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    fd_col9 = open("col9.bin", O_WRONLY | O_CREAT | O_TRUNC, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
   
    child1_pid = ret8; 
    child2_pid = ret9;

    // Tractem el possible error en obrir el fitxer
    if (fd_col8 < 0) {
      printf("No es pot obrir el fitxer\n");
      exit(1);
    }else{
      // Enviem la senyal al productor8
      kill(child1_pid, SIGUSR1); 
    }
    if (fd_col9 < 0) {
      printf("No es pot obrir el fitxer\n");
      exit(1);
    }else{
      // Enviem la senyal al productor9
      kill(child2_pid, SIGUSR2); 
    }
    
    fgets(line, sizeof(line), file);



    // El consumidor8 ha d'obrir l'arxiu...
    while (!sr1) {}; 
    sr1 = 0;
    // El consumidor9 ha d'obrir l'arxiu...
    while (!sr2) {};
    sr2 = 0;

    // Comença la lectura de fitxer:
    while (fgets(line, sizeof(line), file)){
      invalid = get_column_fields_taxis(&value8, &value9, line);
      
      if (!invalid) {
        
        // Escriu els valors de les columnes al fitxer corresponent
        write(fd_col8,&value8,sizeof(int));  
        write(fd_col9,&value9,sizeof(int));

        num_elem++;
        if(num_elem == n){
          // Enviem senyal
          kill(child1_pid,SIGUSR1); 
          kill(child2_pid,SIGUSR2);
          while (!sr1) {};
          sr1 = 0;
          while (!sr2) {};
          sr2 = 0;
          num_elem = 0;
        }
      }
    }


    // Enviem senyal
    kill(child1_pid, SIGUSR1); 
    kill(child2_pid, SIGUSR2); 

    // Tanquem fitxers
    fclose(file); 
    close(fd_col8);
    close(fd_col9);

    // Esperem a que rebin els senyals
    while (!sr1) {}; 
          sr1 = 0;
    while (!sr2) {};
          sr2 = 0;

    // Tractem el possible error de que no pugui ser 0      
    if (num_elem == 0) {
        printf("El nombre d'elements no pot ser 0...\n");
        exit(1);
    }

    // Ús del remove per alliberar espai al disc i eliminar  
    // dades innecessàries per evitar possibles confusions

    remove("col8.bin"); 
    remove("col9.bin");
    printf("EL pare ha acabat el procés\n");
    
    
}


void consumidor8(int n){
  
  float p_count;
  int rd = 1, parent_pid, data, i;

  passengers_count = 0;
  num_elem = 0;
  // Fins que no rebi senyal...
  while (!sr1) {}; 
  sr1 = 0;
  parent_pid = getppid();
  // obrim el fitxer en mode read only
  fd_col8 = open("col8.bin", O_RDONLY); 
  // Enviem senyal avisant que hem llegit
  kill(parent_pid, SIGUSR1); 
  // i esperem a rebre senyal del pare...
  while (!sr1) {}; 
      sr1 = 0;
  while(rd){
    
    
    for (i = 0; i < n; i++ ){
      rd = read(fd_col8, &data, sizeof(int));
      if(!rd) break;
      passengers_count += data;
      num_elem += 1;
      
    }
    if(rd){
      // Enviem senyal
      kill(parent_pid, SIGUSR1); 
      // i esperem a rebre senyal del pare...
      while (!sr1) {}; 
      sr1 = 0;
    }

  }
  close(fd_col8);
  p_count = (float)passengers_count/(float)num_elem;  
  printf("llegint %ld elements de fd_col8...\n", num_elem);
  printf("Mitjana de passatgers: %f\n", p_count);
  // Enviem senyal
  kill(parent_pid, SIGUSR1);
}


void consumidor9(int n){
  float t_secs;
  int rd = 1, parent_pid, data, j;

  trip_seconds = 0;
  num_elem = 0;

  // Fins que no rebi senyal del pare...
  while (!sr2) {}; 
  sr2 = 0;
  parent_pid = getppid();
  // obrim el fitxer en mode read only
  fd_col9 = open("col9.bin", O_RDONLY); 
  // Enviem senyal avisant que hem llegit
  kill(parent_pid, SIGUSR2); 
  // i esperem a rebre senyal del pare...
  while (!sr2) {}; 
      sr2 = 0;


  while(rd){
    
    for (j=0; j < n; j++ ){
      rd = read(fd_col9, &data, sizeof(int));
      if(!rd) break;
      trip_seconds += data;
      num_elem += 1;
      
    }
    if(rd){
      // Enviem senyal
      kill(parent_pid, SIGUSR2); 
      // i esperem a rebre senyal del pare...
      while (!sr2) {}; 
      sr2 = 0;
    }
  }
  close(fd_col9);
  t_secs = (float)trip_seconds/(float)num_elem;
  printf("llegint %ld elements de fd_col9...\n", num_elem);
  printf("Mitjana del temps de desplaçament: %f s\n", t_secs);
  kill(parent_pid, SIGUSR2);
}

int main(int argc, char *argv[]){
  
    int ret8, ret9;
    if(argc != 3){
        printf("%s Has de passar els següents paràmetres: <file> <N> \n", argv[0]);
        exit(1);
    }

    char *file_name = argv[1];
    
    // Convertim la String passada per paràmetre a un int
    int n = atoi(argv[2]);

    
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, sigusr2);

    // Creem un nou procés fill
    ret8=fork();

    if(ret8==0){ 
      consumidor8(n);
    }else{
      ret9=fork(); 
      if(ret9==0){ 
        consumidor9(n);
      }else{
        productor(file_name,n,ret8,ret9);
      }
    }
    return 0;
}


/**
 * Esta funcion se utiliza para extraer informacion del fichero CSV que
 * contiene informacion sobre los trayectos. En particular, dada una linea
 * leida de fichero, la funcion extrae las columnas 8 y 9. 
 */

#define STRLEN_COLUMN 10
#define COLUMN8 8
#define COLUMN9 9

int get_column_fields_taxis(int *column8, int *column9, char *line) 
{
  /*Recorre la linea por caracteres*/
  char caracter;
  /* i sirve para recorrer la linea
   * iterator es para copiar el substring de la linea a char
   * coma_count es el contador de comas
   */
  int i, iterator, coma_count;
  /* start indica donde empieza el substring a copiar
   * end indica donde termina el substring a copiar
   * len indica la longitud del substring
   */
  int start, end, len;
  /* invalid nos permite saber si todos los campos son correctos
   * 1 hay error, 0 no hay error 
   */
  int invalid = 0;
  /* found se utiliza para saber si hemos encontrado los dos campos:
   * origen y destino
   */
  int found = 0;
  /*
   * eow es el caracter de fin de palabra
   */
  char eow = '\0';
  /*
   * substring para extraer la columna
   */
  char substring[STRLEN_COLUMN];
  /*
   * Inicializamos los valores de las variables
   */
  start = 0;
  end = -1;
  i = 0;
  coma_count = 0;
  /*
   * Empezamos a contar comas
   */
  do {
    caracter = line[i++];
    if (caracter == ',') {
      coma_count ++;
      /*
       * Cogemos el valor de end
       */
      end = i;
      /*
       * Si es uno de los campos que queremos procedemos a copiar el substring
       */
      if (coma_count == COLUMN8 || coma_count == COLUMN9) {
        /*
         * Calculamos la longitud, si es mayor que 1 es que tenemos 
         * algo que copiar
         */
        len = end - start;

        if (len > 1) {

          if (len > STRLEN_COLUMN) {
            printf("ERROR STRLEN_COLUMN\n");
            exit(1);
          }

          /*
           * Copiamos el substring
           */
          for(iterator = start; iterator < end-1; iterator ++){
            substring[iterator-start] = line[iterator];
          }
          /*
           * Introducimos el caracter de fin de palabra
           */
          substring[iterator-start] = eow;
          /*
           * Comprobamos que el campo no sea NA (Not Available) 
           */

          switch (coma_count) {
            case COLUMN8:
              *column8 = atoi(substring); 
              found++;
              break;
            case COLUMN9:
              *column9 = atoi(substring); 
              found++;
              break;
            default:
              printf("ERROR in coma_count\n");
              exit(1);
          }

        } else {
          /*
           * Si el campo esta vacio invalidamos la linea entera 
           */

          invalid = 1;
        }
      }
      start = end;
    }
  } while (caracter && invalid==0);

  if (found != 2)
    invalid = 1;

  return invalid;
}
