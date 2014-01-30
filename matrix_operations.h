
#ifndef _MATRIX_OPERATIONS_H
#define _MATRIX_OPERATIONS_H

Matrix * matrix_add( Matrix *, Matrix * );

Matrix * matrix_scalar_mul( Real, Matrix * );

Matrix * matrix_trasposition( Matrix * );

Matrix * matrix_multiplication( Matrix *, Matrix * );

Real matrix_trace( Matrix * );

Real matrix_determinant( Matrix * );

Matrix * matrix_inverse( Matrix * );

Matrix * matrix_cofactors( Matrix * );

Matrix * matrix_adjunct( Matrix * );

#endif /* _MATRIX_OPERATIONS_H */
