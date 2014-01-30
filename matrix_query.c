#include <stdio.h>

#include "matrix.h"


int
matrix_equal( Matrix *m1, Matrix * m2 )
{
    if ( m1 == NULL || m2 == NULL )
        matrix_error("matrix_equal(): m1 == NULL || m2 == NULL")
            ;

    if(!matrix_same_size(m1,m2))
        return 0;

    for ( int row = 0; row < m1->rows; row++ )
        for ( int column = 0; column < m1->columns; column++ )
            if( m1->values[row][column] != m2->values[row][column])
                return 0
                    ;
    return 1;
}

int
matrix_same_size( Matrix * m1, Matrix * m2)
{
    int flag = (m1->columns == m2->columns && m1->rows == m2->rows ) ? 1 : 0 ;
    return flag;
}
int
matrix_issquare( Matrix * m )
{
    if( m->rows == m->columns )
        return 1;
    else
        return 0;
}

int
matrix_isvector( Matrix * m )
{
    if( m->rows == 1 || m->columns == 1 )
        return 1;
    else
        return 0;
}


int matrix_can_mul( Matrix * m1, Matrix * m2 )
{
    if ( m1->columns == m2->rows )
        return 1;
    else
        return 0;
}
