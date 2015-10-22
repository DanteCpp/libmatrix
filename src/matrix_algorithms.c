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
matrix_orthonormalization_gram_schmidt(Matrix * v)
{
    // # column vectors
    int n = v->columns;
    // orthogonal
    Matrix * t = matrix_fork(v);
    // t normalized
    Matrix * q = matrix_fork(v);

    Matrix * r = matrix_new(n,n);

    Matrix * t1;
    Matrix * t2;

    //steps counter
    int i = 0;

    while(i < n)
    {
      // r[j][i] = <q[j],v[i]>
      for(int j=0; j<i; j++)
        matrix_set_value(r, j,i,
          matrix_internal_mul(
            matrix_get_column(q,j),
            matrix_get_column(v,i)
          )
        );
      //               i-2
      // t[i] = v[i] - sum( r[k][i]*q[k] )
      //               k=0



      // normalization
      // q[i] = t[i]/sqrt(r[i][i])


    }

    matrix_destroy(t1);
    matrix_destroy(t2);
    matrix_destroy(t);
    matrix_destroy(r);
    return q;
}

#include "matrix.h"
