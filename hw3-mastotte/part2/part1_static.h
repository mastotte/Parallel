#include <thread>
#include <vector>
ScheduleType t = static_t;

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)
  int chunk_size = size / num_threads;
  int start = chunk_size * tid;
  int end = start + chunk_size;
  if (tid == num_threads -1){
    end = size;
  }
  for (int i = start; i < end; i++) {
    float base = result[i];
    for (int w = 0; w < mult[i]-1; w++) {
      result[i] = result[i]+base;
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