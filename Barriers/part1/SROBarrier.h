#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
class barrier_object {
 public:
  barrier_object() {
    // Probably don't need to do anything here.
  }

  void init(int num_threads) {
    // Implement me
    counter.store(0);
    waiting.store(0);
    this->num_threads = num_threads;
    sense.store(false);
    thread_sense = new bool[num_threads];
    std::fill_n(thread_sense, num_threads, true);
  }

  void barrier(int tid) {
    // Implement me
    int arrival_num = atomic_fetch_add(&counter, 1);
    if (arrival_num == num_threads - 1){
      waiting.store(0);
      counter.store(0);
      sense.store(!sense.load());
      //sense.store(thread_sense[tid]);
    }else{
      atomic_fetch_add(&waiting, 1);
      while (sense.load() != thread_sense[tid]){
        std::this_thread::yield();
      }
    }
    thread_sense[tid] = !thread_sense[tid];
  }

  bool peek(int tid) {
      // Implement me
      if (waiting.load() == num_threads - 1 && sense.load() == thread_sense[tid]) {
          return true;
      }
      return false;
  }

private:
  // Give me some private variables
  std::atomic<int> counter;
  std::atomic<int> waiting;
  int num_threads;
  std::atomic<bool> sense;
  bool *thread_sense;
};