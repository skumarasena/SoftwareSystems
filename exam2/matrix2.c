/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    double **data;
    int rows, cols;
} Matrix;


// Makes a new matrix and sets all elements to zero.
Matrix *make_matrix(int rows, int cols) {
    int i;
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->data = malloc(rows * sizeof(double *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (i=0; i<rows; i++) {
	// use calloc to initialize to 0
	matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

// Prints the elements of a matrix.
void print_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    printf("%lf ", matrix->data[i][j]);
	}
	printf("\n");
    }
}

// Adds a scalar to all elements of a matrix.
void increment_matrix(Matrix *matrix, int incr) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] += incr;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void consecutive_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] = i * matrix->cols + j;
	}
    }
}

// Adds two matrices elementwise and stores the result in the given
// destination matrix (C).
void add_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j;

    assert(A->rows == B->rows && B->rows == C->rows);
    assert(A->cols == B->cols && B->cols == C->cols);

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    C->data[i][j] =  A->data[i][j] + B->data[i][j];
	}
    }
}

// Adds two matrices elementwise and returns a new matrix.
Matrix *add_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, A->cols);
    add_matrix(A, B, C);
    return C;
}

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j, k;

    assert(A->rows == B->cols);
    assert(A->rows == C->rows);
    assert(B->cols == C->cols);

    for (i=0; i<C->rows; i++) {
	for (j=0; j<C->cols; j++) {
	    for (k=0; k<A->cols; k++) {
		C->data[i][j] += A->data[i][k] * B->data[k][j];
	    }
	}
    }
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, B->cols);
    mult_matrix(A, B, C);
    return C;
}

double matrix_sum1(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    
double matrix_sum2(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (j=0; j<A->cols; j++) {
	for (i=0; i<A->rows; i++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    

/*Adds up the rows of A and returns a heap-allocated array of doubles.*/
double *row_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->rows * sizeof(double));

    for (i=0; i<A->rows; i++) {
	total = 0.0;
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
	res[i] = total;
    }
    return res;
}

/*Adds up the columns of A and returns a heap-allocated array of doubles.*/
double *col_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->cols * sizeof(double));

    for (i=0; i<A->cols; i++) {
    total = 0.0;
    for (j=0; j<A->rows; j++) {
        total += A->data[j][i];
    }
    res[i] = total;
    }
    return res;
}

/*Adds up the forward-facing and backward-facing diagonals of A.
Returns a heap-allocated double array.*/
double *diag_sum(Matrix *A) {
    //total1: backward-facing diagonal
    //total2: forward-facing diagonal
    double total1, total2;
    int i, j;
    double *res = malloc(2* sizeof(double));

    assert(A->rows == A->cols);

    total1 = 0.0;
    total2 = 0.0;
    for (i=0; i<A->cols; i++) {
        j = A->cols -i - 1;
        total1 += A->data[i][i];        
        total2 += A->data[j][i];
    }
    res[0] = total1;
    res[1] = total2;
    return res;

}

/*
    Checks whether all elements of a given double array are the same.
    d is the array, n is the size of the array.

    From StackOverflow:
    http://stackoverflow.com/questions/14120346/c-fastest-method-to-check-if-all-array-elements-are-equal
*/

int is_equal(double *d, int n) {

    while(--n>0 && d[n]==d[0]);
        return n==0;

}

/* 
   http://en.wikipedia.org/wiki/Magic_square

   A magic square is an arrangement of numbers (usually integers) in a
   square grid, where the numbers in each row, and in each column, and
   the numbers in the forward and backward main diagonals, all add up
   to the same number. 

   Write a function called is_magic_square() that takes a matrix and 
   returns an int, 1 if the matrix is a magic square, and 0 otherwise.

   Feel free to use row_sum().
*/

int is_magic_square(Matrix *A) {
    //ensure the matrix is actually a square
    if(A->rows != A->cols) {
        return 0;
    }
    
    //Sum all the rows, and make sure all row sums are equivalent
    double *sum = row_sum(A);
    if(!is_equal(sum, A->rows)) {
        return 0;
    }

    //Sum all the columns, and make sure all column sums are equivalent
    //as well as equivalent to the row sums
    double *sum2 = col_sum(A);
    if(!is_equal(sum2, A->cols) || sum2[0] != sum[0]) {
        return 0;
    }

    //Sum both diagonals, and make sure they are equivalent to each other
    //as well as equivalent to the row sums
    double *sum3 = diag_sum(A);
    if(!is_equal(sum3, 2) || sum3[0] != sum[0]) {
        return 0;
    }

    return 1;
    
}


int main() {
    int i;

    Matrix *A = make_matrix(3, 4);
    consecutive_matrix(A);
    printf("A\n");
    print_matrix(A);

    Matrix *B = make_matrix(4, 3);
    increment_matrix(B, 1);
    printf("B\n");
    print_matrix(B);

    Matrix *C = add_matrix_func(A, A);
    printf("A + A\n");
    print_matrix(C);

    Matrix *D = mult_matrix_func(A, B);
    printf("D\n");
    print_matrix(D);

    double sum = matrix_sum1(A);
    printf("sum = %lf\n", sum);

    sum = matrix_sum2(A);
    printf("sum = %lf\n", sum);

    double *sums = row_sum(A);
    for (i=0; i<A->rows; i++) {
	printf("row %d\t%lf\n", i, sums[i]);
    }

    // should print 6, 22, 38


    //a test of the magic square.
    printf("\n\nMAGIC SQUARE TEST: E\n");
    Matrix *E = make_matrix(3, 3);
    increment_matrix(E, 1);
    print_matrix(E);

    printf("MAGIC: %i\n", is_magic_square(E));

    return 0;
}