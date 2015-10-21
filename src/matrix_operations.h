
#ifndef _MATRIX_OPERATIONS_H
#define _MATRIX_OPERATIONS_H

Matrix * matrix_add( Matrix *, Matrix * );

Matrix * matrix_scalar_mul( Field, Matrix * );

Matrix * matrix_trasposition( Matrix * );

Matrix * matrix_multiplication( Matrix *, Matrix * );

Field matrix_trace( Matrix * );

Field matrix_determinant( Matrix * );

Matrix * matrix_inverse_gauss( Matrix * );

Matrix * matrix_inverse( Matrix * );

Matrix * matrix_cofactors( Matrix * );

Matrix * matrix_adjunct( Matrix * );

#endif /* _MATRIX_OPERATIONS_H */
