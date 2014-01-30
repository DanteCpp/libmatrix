
#ifndef _MATRIX_QUERY_H
#define _MATRIX_QUERY_H

int matrix_same_size( Matrix *, Matrix *);

int matrix_issquare( Matrix * );

int matrix_isvector( Matrix * );

int matrix_equal( Matrix *, Matrix * );

int matrix_can_mul( Matrix *, Matrix * );

#endif /*_MATRIX_QUERY_H*/
