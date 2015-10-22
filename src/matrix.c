
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>

#include "matrix.h"

void
matrix_error( char * msg )
{
    perror(msg);
    exit(-1);
}

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
matrix_fill_random( Matrix *m )
{
    if ( m == NULL )
        matrix_error("matrix_fill_random(): m == NULL")
            ;

    for ( int row = 0; row < m->rows; row++ )
        for ( int column = 0; column < m->columns; column++ )
            m->values[row][column] = (Field) rand() / (RAND_MAX)
                ;
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
            printf(PRINT_FORMAT, m->values[row][column]);
        printf("\n");
    }
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
 	Field * digits = malloc( m->columns * sizeof(Field));
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
matrix_fill_Field( Matrix *m , Field r )
{
  if ( m == NULL )
    matrix_error("matrix_fill_Field(): m == NULL")
        ;

  for ( int row = 0; row < m->rows; row++ )
    for ( int column = 0; column < m->columns; column++ )
      m->values[row][column] = r
        ;
}

void
matrix_fill_triangular_up( Matrix * m)
{
    if( ! matrix_is_square(m) )
        matrix_error("matrix_fill_triangular_up(): !matrix_is_square(m)")
            ;
    for( int i=0 ; i < m->rows ; i++)
        for( int j=0 ; j < m->rows; j++ )
           if( i < j )
                m->values[i][j] = 0
                    ;
}


void
matrix_fill_triangular_down( Matrix * m)
{
    if( ! matrix_is_square(m) )
        matrix_error("matrix_fill_triangular_up(): !matrix_is_square(m)")
            ;
    for( int i=0 ; i < m->rows ; i++)
        for( int j=0 ; j < m->rows; j++ )
           if( i > j )
                m->values[i][j] = 0
                    ;
}


Matrix *
matrix_new_identity( int dim )
{
    Matrix * i = matrix_new_zero(dim,dim);
    Matrix * d = matrix_new(1,dim);

    matrix_fill_Field(d,1);
    matrix_set_diagonal(d,i);

    matrix_destroy(d);

    return i;
}

Matrix *
matrix_new_zero( int rows, int columns )
{
    Matrix * m = matrix_new(rows,columns);

    matrix_fill_Field(m,0);

    return m;
}

Matrix *
matrix_new_scalar( int dim, Field r )
{
    Matrix * m = matrix_new_identity(dim);

    Matrix * scal = matrix_scalar_mul( r, m );

    matrix_destroy(m);

    return scal;
}


Matrix *
matrix_new_values( int rows, int columns, ... )
{
    va_list entry;

    Matrix * m = matrix_new(rows,columns);

 	va_start(entry, columns);

    for( int y = 0 ; y < rows ; y++ )
        for( int x = 0; x < columns ; x++ )
            m->values[y][x] = va_arg( entry, Field )
                ;
	va_end(entry);
	return m;
}
