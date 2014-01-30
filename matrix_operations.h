#ifndef _MATRIX_OPERATIONS_H
#define _MATRIX_OPERATIONS_H

Matrix * matrix_add( Matrix *, Matrix * );

Matrix * matrix_scalar_mul( Real, Matrix * );

Matrix * matrix_trasposition( Matrix * );

Matrix * matrix_multiplication( Matrix *, Matrix * );

Real matrix_trace( Matrix * );

#endif /* _MATRIX_OPERATIONS_H */
