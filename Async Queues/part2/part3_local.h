ScheduleType t = local_t;
#include <thread>
#include <vector>
#include <atomic>
#include "IOQueue.h"

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

void parallel_enq(int size, int tid, int num_threads) {
  // Use this function to enqueue indexes to each of the local
  // workstealing queues
  int chunk_size = size / num_threads;
  int start = chunk_size * tid;
  int end = start + chunk_size;
  if (tid == num_threads -1){
    end = size;
  }
  for (int x = start; x < end; x++){
    Q[tid].enq(x);
  }
}

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed
  for (int x = Q[tid].deq(); x != -1; x = Q[tid].deq()){
    float base = result[x];
    for (int w = 0; w < mult[x]-1; w++) {
      result[x] = result[x]+base;
    }
  }
  atomic_fetch_add(&finished_threads,1);
  int picker = 1;
  while (finished_threads.load() != num_threads) {
    int target = (tid + picker)%num_threads;
    int task = Q[target].deq();
    if (task != -1) {
      // perform task
      float base2 = result[task];
      for (int w = 0; w < mult[task]-1; w++) {
        result[task] = result[task]+base2;
      }
    }
    picker++;
  }
}

void launch_threads(float* result_parallel, int* mult) {
  // Launch NUM_THREADS threads to intialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.

  // Next, launch the parallel function that performs the parallel_mult
  // function from part1_static.h and part2_global.h but using workstealing
  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; i++){
    Q[i].init(SIZE);
  }
  for (int i = 0; i < NUM_THREADS; i++){
    threads.emplace_back(parallel_enq,SIZE,i,NUM_THREADS);
  }

  for (auto& t: threads){
    t.join();
  }

  threads.clear();
  for (int i = 0; i < NUM_THREADS; i++){
    threads.emplace_back(parallel_mult,result_parallel,mult,SIZE,i,NUM_THREADS);
  }

  for (auto& t: threads){
    t.join();
  }
}