
#ifndef _MATRIX_MANIPULATION_H
#define _MATRIX_MANIPULATION_H

Matrix * matrix_get_minor( int, Matrix *, int );
Matrix * matrix_get_sub(  int, int, Matrix *, int, int );
Matrix * matrix_get_row( Matrix *, int );
Matrix * matrix_get_column( Matrix *, int );
Matrix * matrix_get_diagonal( Matrix * );

void matrix_put_sub( Matrix *, int, int, Matrix * );
void matrix_put_row( Matrix *, int, Matrix * );
void matrix_put_column( Matrix *, int, Matrix * );
void matrix_put_diagonal( Matrix *, Matrix * );

void matrix_filter( Matrix *, Field (*)(Field) );

#endif /*_MATRIX_MANIPULATION_H*/
