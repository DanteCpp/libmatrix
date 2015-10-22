

#include <stdlib.h>
#include <math.h>

#include "matrix.h"


Matrix *
matrix_add( Matrix * m1, Matrix * m2 )
{
    if( !matrix_same_size(m1,m2))
        matrix_error("matrix_add(): !matrix_same_size(m1,m2)")
            ;
    Matrix * add = matrix_new(m1->rows,m1->columns);

    for ( int row = 0; row < m1->rows; row++ )
        for ( int column = 0; column < m1->columns; column++ )
            add->values[row][column] = m1->values[row][column] + m2->values[row][column]
                    ;
    return add;
}

Matrix *
matrix_scalar_mul( Field s, Matrix * m)
{
    Matrix * mul = matrix_new(m->rows,m->columns);

    for ( int row = 0; row < mul->rows; row++ )
        for ( int column = 0; column < mul->columns; column++ )
            mul->values[row][column] = s * m->values[row][column]
                    ;
    return mul;
}


Matrix *
matrix_trasposition( Matrix * m )
{
    Matrix * t = matrix_new(m->columns, m->rows);

    for ( int row = 0; row < m->rows; row++ )
        for ( int  column = 0; column < m->columns; column++ )
            t->values[column][row] = m->values[row][column]
                ;

  return t;
}


Matrix *
matrix_multiplication( Matrix * m1, Matrix * m2 )
{
    if( !matrix_can_mul(m1,m2) )
        matrix_error("matrix_multiplication(): !matrix_can_mul(m1,m2)")
            ;

    Matrix *mul = matrix_new_zero( m1->rows, m2->columns );

    for ( int row = 0; row < m1->rows; row++ )
        for ( int column = 0; column < m2->columns; column++ )
            for ( int i = 0; i < m1->columns; i++ )
                mul->values[row][column] += m1->values[row][i] * m2->values[i][column]
                    ;
    return mul;
}

Field
matrix_trace( Matrix * m )
{
    Field tr = 0;
    Matrix * d = matrix_get_diagonal(m);

    for( int i = 0 ; i < d->columns ; i++ )
        tr += d->values[0][i]
            ;

    matrix_destroy(d);

    return tr;
}

Field
matrix_determinant( Matrix *m )
{
    if( m->columns == 1)
        matrix_error("matrix_determinant(): n==1")
            ;
    if ( m->columns == 2 )
        return m->values[0][0] * m->values[1][1] - m->values[1][0] * m->values[0][1]
            ;
    Field det = 0;
    Matrix * minor = NULL;
    for ( int column = 0; column < m->columns; column++ )
    {
        minor = matrix_get_minor( 0, m, column );
        det += pow( -1, column ) * m->values[0][column] * matrix_determinant( minor );
        matrix_destroy(minor);
    }
    return det;
}

Matrix *
matrix_inverse_gauss( Matrix * mat )
{
    if( !matrix_is_square(mat) )
        matrix_error("matrix_inverse(): !matrix_is_square(m)")
            ;
    if( matrix_is_sigular(mat) )
        matrix_error("matrix_inverse(): matrix_is_sigular(mat)")
            ;
    Matrix * i = matrix_new_identity(mat->rows);
    Matrix * m = matrix_new_zero(mat->rows, 2*mat->rows);

    matrix_set_sub(mat,0,0,m);
    matrix_set_sub(i,0,m->rows,m);

    int temp;
    Field r, temporary;

    for ( int j = 0; j < m->rows; j++)
    {
        temp = j;
        /* finding maximum jth column element in last (dimension-j) rows */
        for ( int i = j + 1; i < m->rows; i++)
            if ( m->values[i][j] > m->values[temp][j])
                temp = i
                    ;

        /* swapping row which has maximum jth column element */
        if (temp != j)
            for ( int k = 0; k < m->columns; k++)
            {
                temporary = m->values[j][k];
                m->values[j][k] = m->values[temp][k];
                m->values[temp][k] = temporary;
            }

        /* performing row operations to form required identity matrix out of the input matrix */
        for ( int i = 0; i < m->rows; i++)
        {
            if (i != j)
            {
                r = m->values[i][j];
                for ( int k = 0; k < m->columns; k++)
                    m->values[i][k] -= m->values[j][k] * r / m->values[j][j]
                        ;
            }
            else
            {
                r = m->values[i][j];
                for ( int k = 0; k < m->columns; k++)
                    m->values[i][k] /= r
                        ;
            }
        }
    }
    matrix_destroy(i);
    Matrix * invers = matrix_get_sub(  m->rows, m->columns-1, m, 0, m->rows-1);
    matrix_destroy(m);

    return invers;
}

Matrix *
matrix_cofactors( Matrix * m )
{
    Matrix * r = matrix_new_zero(m->rows,m->columns);

    for( int row=0 ; row < m->rows ; row++ )
        for( int column=0; column < m->columns ; column++ )
        {
            Matrix * minor = matrix_get_minor( row, m, column );
            r->values[row][column] = pow( -1, row+column ) * matrix_determinant(minor);
            matrix_destroy(minor);
        }
    return r;
}

Matrix *
matrix_adjunct( Matrix * m )
{
    Matrix * r = matrix_cofactors(m);
    Matrix * t = matrix_trasposition(r);
    matrix_destroy(r);
    return t;
}

Matrix *
matrix_inverse( Matrix * m )
{
	Matrix * adj = matrix_adjunct(m);
    return matrix_scalar_mul(1/matrix_determinant(m),adj);
}
