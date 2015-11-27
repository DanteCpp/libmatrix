
#include "matrix.h"
#include <stdlib.h>
#include <math.h>


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
matrix_gram_schmidt(Matrix * V)
{

  long n = V->rows;
  long m = V->columns;

  Matrix * Q = matrix_new_zero(n,m);
  double r = 0;
  double norm = 0;

  for(int k=0; k<n; k++)
    norm += (V->values[k][0])*(V->values[k][0])
      ;
    norm = sqrt(norm);

  for(int k=0; k<n; k++)
    (Q->values[k][0])=(V->values[k][0])/norm
      ;
  norm = 0;

  for(int i =1; i < m; i++)
  {
    for(int k=0; k<n; k++)
      Q->values[k][i]=V->values[k][i]
        ;
    for(int j=0; j<i;j++)
    {
      for(int k=0; k<n; k++)
        r+=(Q->values[k][j])*(V->values[k][i])
          ;
      for(int k=0; k<n; k++)
        (Q->values[k][i])-=(r*(Q->values[k][j]))
          ;
      r = 0;
    }
    for(int k=0; k<n; k++)
      norm += (Q->values[k][i])*(Q->values[k][i])
        ;
    norm = sqrt(norm);

    for(int k=0; k<n; k++)
      Q->values[k][i]=(Q->values[k][i])/norm
        ;
    norm = 0;
  }

  return Q;
}
