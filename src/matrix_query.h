
#ifndef _MATRIX_QUERY_H
#define _MATRIX_QUERY_H

int matrix_same_size( Matrix *, Matrix *);

int matrix_is_square( Matrix * );

int matrix_is_vector( Matrix * );

int matrix_is_equal( Matrix *, Matrix * );

int matrix_is_sigular( Matrix * );

int matrix_can_mul( Matrix *, Matrix * );

#endif /*_MATRIX_QUERY_H*/
