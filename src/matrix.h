
#ifndef _MATRIX_H
#define _MATRIX_H

#define PRINT_FORMAT "%.2f "

typedef double Field;

typedef struct
{
  int rows;
  int columns;
  Field ** values;
}

Matrix;

/*Make and destroy */

Matrix * matrix_new( int, int );
Matrix * matrix_new_identity( int );
Matrix * matrix_new_zero( int, int );
Matrix * matrix_new_scalar( int, Field );
Matrix * matrix_new_values( int, int, ... );

void matrix_destroy( Matrix * );

/*Fill*/
void matrix_fill( Matrix *, ... );
void matrix_fill_random( Matrix *);
void matrix_fill_field( Matrix *, Field );
void matrix_fill_triangular_up( Matrix * );
void matrix_fill_triangular_down( Matrix * );

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

#include "matrix_algorithms.h"

#endif /* _MATRIX_H */
