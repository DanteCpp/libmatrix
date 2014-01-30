
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

/*Fill*/
void matrix_fill( Matrix *, ... );
void matrix_fill_random( Matrix *);
void matrix_fill_real( Matrix *, Real );

/*Tools*/
void matrix_error( char * );
void matrix_print( Matrix * );
void matrix_copy( Matrix *, Matrix *);
Matrix * matrix_fork( Matrix * );

/*Query*/
#include "matrix_query.h"

/*Manipulation*/
#include "matrix_manipulation.h"

/*operation*/
#include "matrix_operations.h"

#endif /* _MATRIX_H */
