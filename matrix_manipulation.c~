
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


Matrix *
matrix_get_minor( int skip_row, Matrix *m, int skip_col )
{
    if( !matrix_is_square(m) )
        matrix_error("matrix_get_minor(): !matrix_is_square(m)")
            ;
    int i = 0, j = 0;
    Matrix * minor = matrix_new(m->rows-1,m->columns-1);

    for ( int row = 0; row < m->rows; row++ )
    {
        if ( row == skip_row )
            continue
                ;
          j=0;
        for ( int column = 0; column < m->columns; column++ )
        {
            if ( column == skip_col )
                continue
                    ;
            minor->values[i][j] = m->values[row][column];
            j++;
        }
        i++;
    }
    return minor;
}

Matrix *
matrix_get_sub( int x1 , int x2, Matrix * m, int y1, int y2 )
{

    if( x2-x1+1 > m->rows || y2-y1+1 > m->columns )
        matrix_error("matrix_get_sub(): x2-x1+1 > m->rows || y2-y1+1 > m->columns")
            ;

	Matrix *minor = matrix_new_zero( x2-x1+1, y2-y1+1 );

	int i = 0;
    Real *temp = malloc( minor->rows * minor->columns * sizeof(Real) );
    memset(temp,minor->rows * minor->columns, sizeof(Real));

    if( temp == NULL )
        matrix_error("matrix_get_minor(): temp == NULL")
            ;

    for( int row = y1 ; row < (y2+1) ; row++ )
		for( int column = x1 ; column < (x2+1) ; column++ )
	    	temp[i++] = m->values[row][column]
	    		;
    i = 0;
    for( int row = 0 ; row < minor->rows ; row++ )
		for( int column = 0 ; column < minor->columns ; column++ )
	    	minor->values[row][column] = temp[i++]
	    		;

    return minor;
}


Matrix *
matrix_get_row( Matrix * m, int r )
{
    if( r >= m->rows )
        matrix_error("matrix_get_row(): r >= m->rows")
            ;
    Matrix * row = matrix_new(1,m->columns);

    for( int column = 0 ; column < m->columns ; column++ )
        row->values[0][column] = m->values[r][column]
            ;
    return row;
}

Matrix *
matrix_get_column( Matrix * m, int c )
{
    if( c >= m->columns )
        matrix_error("matrix_get_column(): c >= m->columns")
            ;

    Matrix * column = matrix_new(m->rows,1);

    for( int row = 0 ; row < m->rows ; row++ )
         column->values[row][0] = m->values[row][c]
            ;
    return column;
}


Matrix *
matrix_get_diagonal( Matrix * m )
{
    if( !matrix_is_square(m) )
        matrix_error("matrix_get_diagonal(): !matrix_issquare(m)")
            ;

    Matrix * diagonal = matrix_new( 1, m->columns );

    for( int i = 0 ; i < m->rows ; i++ )
        diagonal->values[0][i] = m->values[i][i]
            ;

    return diagonal;
}


void
matrix_put_sub( Matrix * from, int y , int x, Matrix * to )
{
    if( y+from->rows > to->rows || x+from->columns > to->columns )
         matrix_error("matrix_put_minor(): y+from->rows > to->rows || x+from->columns > to->columns")
            ;
    for( int row = 0 ; row < from->rows ; row++ )
		for( int column = 0 ; column < from->columns ; column++ )
	    	to->values[row+y][column+x] = from->values[row][column]
	    		;
}

void
matrix_put_row( Matrix * from, int r , Matrix * to )
{
    if( from->columns != to->columns )
        matrix_error("matrix_put_row(): from->columns != to->columns")
            ;
    matrix_put_sub(from, 0, r, to);
}


void
matrix_put_column( Matrix * from, int c , Matrix * to )
{
    if( from->rows != to->rows )
        matrix_error("matrix_put_column(): from->rows != to->rows")
            ;
    matrix_put_sub(from, c, 0, to);
}

void
matrix_put_diagonal( Matrix * d, Matrix * m )
{
    if( !( matrix_is_vector(d) && matrix_is_square(m)) )
        matrix_error("matrix_put_diagonal(): !( matrix_isvector(d) && matrix_issquare(m))")
            ;

    if( d->rows == 1 )
    {
        if( d->columns != m->columns )
            matrix_error("matrix_put_diagonal(): d->columns != m->columns ")
                ;

        for( int i = 0 ; i < m->rows ; i++ )
            m->values[i][i] = d->values[0][i]
                ;
    }
    else
    {
        if( d->rows != m->columns )
            matrix_error("matrix_put_diagonal(): d->rows != m->columns")
                ;

        for( int i = 0 ; i < m->rows ; i++ )
            m->values[i][i] = d->values[i][0]
                ;
    }
}

void
matrix_filter( Matrix * m, Real (*func)(Real) )
{
    for ( int row = 0; row < m->rows; row++ )
        for ( int column = 0; column < m->columns; column++ )
            m->values[row][column] = (*func)( m->values[row][column] )
                    ;
}
