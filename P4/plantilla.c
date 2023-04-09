#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>


struct Matrix {
  int numberOfRows;
  int numberOfColumns;
  float ∗grid;
  int fd;
}



struct Matrix createEmptyMatrix (int numberOfRows , int numberOfColumns , char∗ filepathPersistence){
  a = malloc(numberOfRows*sizeof(double*));
  for (int k = 0; k < numberOfRows; k++){
    a[k]= (double*)malloc(numberOfRows*sizeof(double));
  }
  for(int i = 0; i<numberOfRows; i++){
      for(int j = 0; j < numberOfColumns; j++){
        a[i*numberOfColumns+j] = *((i+1)*numberOfColumns*j);

}

float VandermondeCoefficients(int row , int column){
  if (column == 0)
    return (float) 1.0;
  return (float)pow(row,column);
}

void fillMatrix (struct Matrix *matrix , FILL_MATRIX_FUNC func ){
  //a[k]=*(a+k);  -> on k = i+ncol+j ->(i = fila i, j = columna j)
    double a;
    int n;
    n = 1000;
    
    float *a = matrix->grid;
    for(int i = 0; i < matrix->numberOfRows; i++){
        for( int j = 0; j < matrix->numberOfColumns; j++){
           *a = func(i,j);
           a += 1;
} 

void printMatrix (struct Matrix ∗matrix){
  a = malloc(matrix->numberOfRows*sizeof(double*));
    for (int i = 0; i < matrix->numberOfRows; i++){
        a[i]= (double*)malloc(matrix->numberOfRows*sizeof(double));
    }
  for(int i = 0; i<matrix->numberOfRows; i++){
      for(int j = 0; j < matrix->numberOfColumns; j++){

        printf("%d ", *matrix[i][j]);

      }
  }
}

struct Matrix loadSavedMatrix (int numberOfRows, int numberOfColumns, char∗ filepath){

}