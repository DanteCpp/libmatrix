
#ifndef _MATRIX_H
#define _MATRIX_H

typedef float Real;

typedef struct
{
  int rows;
  int columns;
  Real ** values;
}

Matrix;

/*Make and destroy */
Matrix * matrix_new( int, int );
void matrix_destroy( Matrix * );

void matrix_error( char * );
void matrix_print( Matrix * );

/*Query*/
#include "matrix_query.h"

/*Manipulation*/
#include "matrix_manipulation.h"

/*operation*/
#include "matrix_operations.h"

#endif /* _MATRIX_H */
