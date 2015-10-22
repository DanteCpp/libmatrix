#include <stdlib.h>
#include <math.h>

#include "matrix.h"

Field
matrix_internal_mul(Matrix * v, Matrix * w)
{
  if(matrix_is_vector(v) && matrix_is_vector(w))
  {
    Field sum = 0;
    for(int i=0;i<v->rows;i++)
      sum+=(v->values[i][0])*(w->values[i][0]);
        ;
    return sum;
  }

  else
  {
    matrix_error("matrix_internal_mul(): matrix_is_vector(v) && matrix_is_vector(w)");
    return -1;
  }
}


Field
matrix_norm_euclide(Matrix * v){
  if(matrix_is_vector(v))
  {
    Field sum = 0;
    for(int i=0;i<v->rows;i++)
      sum+=pow(v->values[i][0],2)
        ;
    return sqrt(sum);
  }

  else
  {
    matrix_error("matrix_norm_euclide(): matrix_is_vector(v)");
    return -1;
  }
}

Matrix *
matrix_orthonormalization_gram_schmidt(Matrix * m)
{
    // # column vectors
    int n = m->columns;
    Matrix * q = matrix_fork(m);

    Matrix * r = matrix_new(n,1);
    Field norm = 0;

    int step = 0;

    while(step < n)
    {
      matrix_set_value(r, step,0,
        matrix_norm_euclide(matrix_get_column(m,step)));
      matrix_set_column( q, step,  )
    }

    return m;
}

#include "matrix.h"
