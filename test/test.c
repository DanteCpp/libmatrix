#include <stdio.h>
#include <matrix.h>

int main(){
  Matrix * v = matrix_new_values(3,3, 1.,1.,0.,
                                      0.,0.,1.,
                                      1.,0.,2.);
  matrix_print(v);
  Matrix * q = matrix_orthonormalization_gram_schmidt(v);
  matrix_print(q);

  matrix_destroy(v);
  matrix_destroy(q);
  return 0;
}
