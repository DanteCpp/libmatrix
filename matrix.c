#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>

#include "matrix.h"

Matrix *
matrix_new( int rows, int columns )
{
    if( rows == 0 || columns == 0 )
        matrix_error("matrix_new(): rows == 0 || columns == 0")
            ;

    Matrix *m = malloc( sizeof *m );

    if ( m == NULL )
        matrix_error("matrix_new(): m == NULL")
            ;

    m->rows = rows;
    m->columns = columns;
    m->values = malloc( sizeof *m->values * rows );

    for( int i = 0; i < rows; i++ )
        m->values[i] = malloc( sizeof **m->values * columns );

    return m;
}

void
matrix_destroy( Matrix *m )
{
    if ( m == NULL )
        matrix_error("matrix_destroy(): m == NULL")
            ;

    for( int i = 0; i < m->rows; i++ )
        free( m->values[i] );
    free( m->values );

    free( m );
}

void
matrix_print( Matrix *m )
{
    if ( m == NULL )
        matrix_error("matrix_print(): m == NULL")
            ;

    for ( int row = 0; row < m->rows; row++ )
    {
        for ( int column = 0; column < m->columns; column++ )
            printf("%.16f ", m->values[row][column]);
        printf("\n");
    }
}

void
matrix_error( char * msg )
{
    perror(msg);
    exit(-1);
}

