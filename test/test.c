#include <stdio.h>
#include <matrix.h>

int main(){
  Matrix * m = matrix_new(3,1);
  matrix_fill_random(m);
  matrix_print(m);
  Field norm = matrix_norm_euclide(m);
  printf("Norm: %.2f\n", norm);
  matrix_destroy(m);
  return 0;
}
