#include <stdlib.h>

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
matrix_scalar_mul( Real s, Matrix * m)
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

    Matrix *mul = matrix_new( m1->rows, m2->columns );

    for ( int row = 0; row < m1->rows; row++ )
        for ( int column = 0; column < m2->columns; column++ )
            for ( int i = 0; i < m1->columns; i++ )
                mul->values[row][column] += m1->values[row][i] * m2->values[i][column]
                    ;
    return mul;
}

Real
matrix_trace( Matrix * m )
{
    Real tr = 0;
    Matrix * d = matrix_get_diagonal(m);

    for( int i = 0 ; i < d->columns ; i++ )
        tr += d->values[0][i]
            ;

    matrix_destroy(d);

    return tr;
}

