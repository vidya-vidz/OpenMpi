/*
 * _MAIN_C_
 *
 * CS5332 OpenMP Programming Assignment
 *
 * John Leidel: john.leidel@ttu.edu
 * http://discl.cs.ttu.edu/gitlab/jleidel/cs5332_omp.git
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

/* --------------------------------- MACROS */
#define X_LEN 1024
#define Y_LEN 1024

/* --------------------------------- FUNCTION PROTOTYPES */
extern void naive_dgemm( double **Result,
                         double **A,
                         double **B,
                         int N );

/* --------------------------------- MYSECOND */
double mysecond(){
  struct timeval tp;
  struct timezone tzp;

  gettimeofday( &tp, &tzp );
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

/* --------------------------------- MAIN */
int main( int argc, char **argv ){
  /* vars */
  double *Ap  = NULL; /* A storage */
  double *Bp  = NULL; /* B storage */
  double *Rp  = NULL; /* R storage */
  double **A  = NULL; /* A pointer storage */
  double **B  = NULL; /* B pointer storage */
  double **R  = NULL; /* R pointer storage */
  double start_t = 0.;
  double end_t = 0.;
  double flop = 0.;
  unsigned long long i = 0;
  pid_t pid = -1;
  /* ---- */

  flop = ((double)(X_LEN)*(double)(Y_LEN))*((2.0*(double)(X_LEN))-1.0);

  /* -- allocate memory */
  Ap = malloc( sizeof( double ) * X_LEN * Y_LEN );
  if( Ap == NULL ){
    printf( "Error : could not allocate memory for Ap\n" );
    return -1;
  }

  Bp = malloc( sizeof( double ) * X_LEN * Y_LEN );
  if( Bp == NULL ){
    printf( "Error : could not allocate memory for Bp\n" );
    return -1;
  }

  Rp = malloc( sizeof( double ) * X_LEN * Y_LEN );
  if( Rp == NULL ){
    printf( "Error : could not allocate memory for Rp\n" );
    return -1;
  }

  A = malloc( sizeof( double * ) * X_LEN );
  if( A == NULL ){
    printf( "Error : could not allocate memory for A\n" );
    return -1;
  }

  B = malloc( sizeof( double * ) * X_LEN );
  if( B == NULL ){
    printf( "Error : could not allocate memory for B\n" );
    return -1;
  }

  R = malloc( sizeof( double * ) * X_LEN );
  if( R == NULL ){
    printf( "Error : could not allocate memory for R\n" );
    return -1;
  }

  /* init the memory with nonzero values */
  pid = getpid();
  for( i=0; i<(X_LEN*Y_LEN); i++ ){
    Ap[i] = (double)(pid)*(double)(i);
    Bp[i] = Ap[i]*2.0;
    Rp[i] = 0.;
  }

  /* init our 2D pointers */
  for( i=0; i<X_LEN; i++ ){
    A[i] = &(Ap[i*Y_LEN]);
    B[i] = &(Bp[i*Y_LEN]);
    R[i] = &(Rp[i*Y_LEN]);
  }

  /* execute the benchmark */
  start_t = mysecond();
  naive_dgemm( R, A, B, X_LEN );
  end_t = mysecond();

  printf( "Executed DGMEM in %f seconds; %f Gflops\n",
          (end_t-start_t),
          (flop/1000000000.0)/(end_t-start_t) );

  /* free the memory */
  free( A );
  free( B );
  free( R );
  free( Ap );
  free( Bp );
  free( Rp );

  return 0;
}

/* EOF */
