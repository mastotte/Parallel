#pragma once

#include <atomic>
#include <vector>
#include <thread>

using namespace std;

class mutex {
 public:
  mutex() {
    // Implement me!
    mutex_lock.store(0);
  }
  
  void init (int num_threads) {
    // Implement me!
    numberOfThreads = num_threads;
    level.resize(numberOfThreads);
    victims.resize(numberOfThreads);
    for (int i = 0; i < num_threads; i++){
      victims[i] = -1;
      level[i] = -1;
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    int me = thread_id;
    for (int i = 1; i < numberOfThreads; i++){
      level[me] = i;
      victims[i] = me;
      bool k_condition = true;
      bool v_condition = true;
      while (k_condition && v_condition) {
        v_condition = false;
        int v = victims[i];
        if (v == me){
          v_condition = true;
        }
        k_condition = false;
        for(int k = 1; k < numberOfThreads; k++){
          if (k != me && level[k] >= i){
            k_condition = true;
          }
        }
        std::this_thread::yield();
      }
    }
    mutex_lock.store(1);
  }

  
  void unlock(int thread_id) {
    // Implement me!
    level[thread_id] = 0;
    mutex_lock.store(0);
  }

 private:
  // Give me some private variables!
  std::atomic<int> mutex_lock;
  int numberOfThreads;
  vector<int> level;
  vector<int> victims;
  
};
