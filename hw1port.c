/* compile this with -gnu99 (clock_gettime throws an error without it) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*generate a list of random doubles within the interval [-bound, bound], length 'size'*/
double* generate_random_list(int size, double bound){
  double* ret = malloc(sizeof(double)*size);
  for(int i=0; i<size; i++){
    double x = (double)rand()/(double)(RAND_MAX/(2*bound)); /*generates a number in [0,2*bound]*/
      x = bound - x;
      ret[i]= x;
     }
  return ret;
}

/*update location by velocity, one time-step*/
void update_coords(int size, double* x, double* y, double* z, double* vx, double* vy, double* vz){
  for(int i=0; i<size; i++){
    x[i] += vx[i];
    y[i] += vy[i];
    z[i] += vz[i];
  }
}


int main(int argc, char** argv){
  if(argc != 3){
    printf("Ya goofed");
    return -1;
  }
  srand(time(NULL));
  int size = atoi(argv[1]);
  int iters = atoi(argv[2]);
 

  double* x = generate_random_list(size,1000.);
  double* y = generate_random_list(size,1000.);
  double* z = generate_random_list(size,1.);
  double* vx = generate_random_list(size,1.);
  double* vy = generate_random_list(size,1.);
  double* vz = generate_random_list(size,1.);

  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC, &end);

  for (int i=0; i < iters; i++) update_coords(size,x,y,z,vx,vy,vz);
  
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = end.tv_nsec - start.tv_nsec;
  double avg = elapsed/(double)(size * iters);
  printf("\nAverage Elapsed Time: %f\n",avg);
  return 0;
}