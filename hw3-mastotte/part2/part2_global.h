ScheduleType t = global_t;

#include <atomic>
#include <vector>
#include <thread>
std::atomic_int x(0);

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from incrementing the counter
  for (int local_x = atomic_fetch_add(&x, 1); local_x < size; local_x =  atomic_fetch_add(&x, 1)) {
    float base = result[local_x];
    for (int w = 0; w < mult[local_x]-1; w++) {
      result[local_x] = result[local_x]+base;
    }
  }
}

void launch_threads(float* result_parallel, int* mult) {
  // Launch NUM_THREADS threads and then join them
  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; i++){
    threads.emplace_back(parallel_mult,result_parallel,mult,SIZE,i,NUM_THREADS);
  }

  for (auto& t: threads){
    t.join();
  }
}