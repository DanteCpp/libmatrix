#include <stdio.h>
#include <matrix.h>

#define n 3
#define m n

int main(){
  Matrix * V = matrix_new_values(3,3, 1.,1.,0.,
                                      0.,0.,1.,
                                      1.,0.,2.);

  Matrix * Q = matrix_gram_schmidt(V);

  printf("\n" );
  matrix_print(Q);
  matrix_destroy(Q);
  matrix_destroy(V);

  return 0;
}
