#include "csim.h"
#include <stdio.h>

#define THINK_MEAN 2
#define BUS_MEAN 0.2
#define MEM_MEAN 4.0
#define M 10
#define N 4
#define SIM_TIME 500000

FACILITY memories[N];   
FACILITY bus;

double total_time = 0;
double total_request = 0;


void cpu();


void sim() {
  create("sim");        

  /*initialize facility*/
  facility_set(memories, "memories", N);    
  bus = facility("bus");

  int i;
  for (i = 0; i < M; i++) {
    cpu();
  }
  hold(SIM_TIME);
  report();
  printf("Mean response time: %.5f\n \n", total_time / total_request);
}

void cpu() {
  create("request");       
  while(simtime() < SIM_TIME) {
    double r;
    hold(exponential(THINK_MEAN));   

    double start = simtime();
    use(bus, exponential(BUS_MEAN));

    int id = 0;
    int i = 0;
    for (i = 0; i < N; i++) {
      if (qlength(memories[id]) + num_busy(memories[id]) 
            > qlength(memories[i]) + num_busy(memories[id])) {
        id = i;
      }
    }
    use(memories[id], exponential(MEM_MEAN));
    use(bus, exponential(BUS_MEAN));
    double elapse = simtime() - start;
    total_time += elapse;
    total_request += 1;
  }
}


