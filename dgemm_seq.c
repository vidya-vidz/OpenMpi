/*
 * _DGMEMM_SEQ_C_
 *
 * Sequential DGEMM
 *
 * CS5332 OpenMP Programming Assignment
 *
 * John Leidel: john.leidel@ttu.edu
 * http://discl.cs.ttu.edu/gitlab/jleidel/cs5332_omp.git*
 *
 */


extern void naive_dgemm( double **restrict Result,
                         double **restrict A,
                         double **restrict B,
                         int N ){
  /* vars */
  int i = 0;
  int j = 0;
  int k = 0;
  double sum = 0.;
  /* --- */
#pragma omp parallel for
  for( i=0; i<N; i++ ){
#pragma omp parallel for
    for( j=0; j<N; j++ ){
      sum = 0.0;
#pragma omp parallel for
      for( k=0; k<N; k++ ){
        sum = sum + A[i][k] * B[k][j];
      }
      Result[i][j] = sum;
    }
  }
}

/* EOF */
