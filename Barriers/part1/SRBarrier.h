#include <atomic>
#include <vector>
class barrier_object {
 public:
  barrier_object() {
    // Probably don't need to do anything here.
  }

  void init(int num_threads) {
    // Implement me
    counter = 0;
    this->num_threads = num_threads;
    sense = false;
    thread_sense = new bool[num_threads];
    for (int i = 0; i < num_threads; i++){
      thread_sense[i] = true;
    }
  }

  void barrier(int tid) {
    // Implement me
    int arrival_num = atomic_fetch_add(&counter, 1);
    if (arrival_num == num_threads - 1){
      counter.store(0);
      sense = thread_sense[tid];
    }else{
      while (sense != thread_sense[tid]);
    }
    thread_sense[tid] = !thread_sense[tid];
  }

private:
  // Give me some private variables
  std::atomic<int> counter;
  int num_threads;
  std::atomic<bool> sense;
  bool *thread_sense;
};
