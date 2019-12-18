#include "csim.h"
#include <stdio.h>

#define THINK_MEAN 25.0
#define BUS_MEAN 2.0
#define MEM_MEAN 4.0
#define M 9
#define N 4
#define SIM_TIME 5000000

FACILITY memories[N];   
FACILITY bus;

double total_time = 0;
double total_request = 0;


void cpu();

int cur_server = 0;

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
    r = uniform(0, 1);
    if (r < 0.95) {
      hold(exponential(2));   
    } else {
      hold(exponential(462));
    }
    double start = simtime();
    use(bus, exponential(BUS_MEAN));
    int id;
    id = floor(N * uniform(0, 1));
    use(memories[id], exponential(MEM_MEAN));
    use(bus, exponential(BUS_MEAN));
    double elapse = simtime() - start;
    total_time += elapse;
    total_request += 1;
  }
}


