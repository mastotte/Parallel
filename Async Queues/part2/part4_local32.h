ScheduleType t = local_32_t;

#include <atomic>
#include <vector>
#include <thread>
#include "IOQueue.h"

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

void parallel_enq(int size, int tid, int num_threads) {
  // Use this function to equeue indexes to each of the local
  // workstealing queues

  // Hint: this should be the same as in main3.cpp
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

  // Unlike in part3_local.h, you should deq 32 elements
  // at a time.
  int *x_32 = new int[32];
  for (int x = Q[tid].deq_32(x_32); x != -1; x = Q[tid].deq_32(x_32)){
    for (int i = 0; i < 32; i++){
      int index = x_32[i];
      float base = result[index];
      for (int w = 0; w < mult[index]-1; w++) {
        result[index] = result[index]+base;
      }
    }
  }
  // steal from other threads
  atomic_fetch_add(&finished_threads,1);
  int picker = 1;
  while (finished_threads.load() != num_threads) {
    int target = (tid + picker)%num_threads;
    int task = Q[target].deq_32(x_32);
    if (task != -1) {
      // perform task
      for (int i = 0; i < 32; i++){
        int index = x_32[i];
        float base = result[index];
        for (int w = 0; w < mult[index]-1; w++) {
          result[index] = result[index]+base;
        }
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

  // hint: this part should be the same as in part3_local.h
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