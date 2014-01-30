#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix *
matrix_fork( Matrix *to_copy )
{
    if ( to_copy == NULL )
        matrix_error("matrix_fork(): to_copy == NULL")
            ;

    Matrix *copy = matrix_new( to_copy->columns, to_copy->rows );

    for ( int row = 0; row < to_copy->rows; row++ )
        for ( int column = 0; column < to_copy->columns; column++ )
            copy->values[row][column] = to_copy->values[row][column];

    return copy;
}

void
matrix_copy( Matrix *from, Matrix * to )
{
    if ( from == NULL || to == NULL )
        matrix_error("matrix_copy(): from == NULL || to == NULL")
            ;

    if(!matrix_same_size(from,to))
        matrix_error("matrix_copy(): !matrix_same_size(from,to)")
            ;
    for ( int row = 0; row < to->rows; row++ )
        for ( int column = 0; column < to->columns; column++ )
            to->values[row][column] = from->values[row][column];
}


void
matrix_fill( Matrix *m, ... )
{
    va_list rows;
 	int y=0, i = 0, j = 0, n = 0;

 	char * row = malloc( 1024 * sizeof(char));
 	if( row == NULL)
        matrix_error("matrix_fill(): row == NULL")
            ;
 	char * digit = malloc( m->columns * sizeof(char) );
 	if( digit == NULL)
        matrix_error("matrix_fill(): digit == NULL")
            ;
 	Real * digits = malloc( m->columns * sizeof(Real));
 	if( digits == NULL)
        matrix_error("matrix_fill(): digits == NULL")
                ;

 	va_start(rows, m);

	row = va_arg( rows, char* );

	while( row != NULL )
	{
		if( y >= m->rows )
            matrix_error("matrix_fill(): y >= m->rows")
                ;

		do{

			if( isdigit( row[i] ) || row[i] == '.' || row[i] == '-')
			{
				digit[j] = row[i]	;
				j++;
			}
			else
			{
				digit[j] = '\0';
				digits[n] = atof(digit);
				n++;
				j = 0;
			}
			i++;

		}while( row[i] != '\0');

		digit[j] = '\0';
		digits[n] = atoi(digit);

		if( n != m->columns-1 )
            matrix_error("matrix_fill(): n != m->columns-1")
                ;

		for( int x = 0 ; x < n+1 ; x++ )
			m->values[y][x] = digits[x]
				;

		row = va_arg( rows, char* );

		n = 0;  j = 0;  i = 0;  y++;
	}

	va_end(rows);

	free(row);
	free(digit);
	free(digits);
}

void
matrix_fill_random( Matrix *m )
{
    if ( m == NULL )
        matrix_error("matrix_fill_random(): m == NULL")
            ;

    for ( int row = 0; row < m->rows; row++ )
        for ( int column = 0; column < m->columns; column++ )
            m->values[row][column] = (Real) rand() / (RAND_MAX)
                ;
}

void
matrix_fill_real( Matrix *m , Real r )
{
  if ( m == NULL )
    matrix_error("matrix_fill_real(): m == NULL")
        ;

  for ( int row = 0; row < m->rows; row++ )
    for ( int column = 0; column < m->columns; column++ )
      m->values[row][column] = r
        ;
}


Matrix *
matrix_get_minor(  int x1 , int x2, Matrix * m, int y1, int y2 )
{

    if( x2-x1+1 > m->rows || y2-y1+1 > m->columns )
        matrix_error("matrix_get_minor(): x2-x1+1 > m->rows || y2-y1+1 > m->columns")
            ;

	Matrix *minor = matrix_new( x2-x1+1, y2-y1+1 );

	int i = 0;
    Real *temp = malloc( minor->rows * minor->columns * sizeof(Real) );

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
    if( !matrix_issquare(m) )
        matrix_error("matrix_get_diagonal(): !matrix_issquare(m)")
            ;

    Matrix * diagonal = matrix_new( 1, m->columns );

    for( int i = 0 ; i < m->rows ; i++ )
        diagonal->values[0][i] = m->values[i][i]
            ;

    return diagonal;
}


void
matrix_put_minor( Matrix * from, int x , int y, Matrix * to )
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
    matrix_put_minor(from, 0, r, to);
}


void
matrix_put_column( Matrix * from, int c , Matrix * to )
{
    if( from->rows != to->rows )
        matrix_error("matrix_put_column(): from->rows != to->rows")
            ;
    matrix_put_minor(from, c, 0, to);
}

void
matrix_put_diagonal( Matrix * d, Matrix * m )
{
    if( !( matrix_isvector(d) && matrix_issquare(m)) )
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
