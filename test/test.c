
#include <matrix.h>

int main(){
  Matrix * m = matrix_new(3,3);
  matrix_print(m);
  matrix_destroy(m);
  return 0;
}
