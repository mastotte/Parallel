#pragma once

#include <atomic>
#include <mutex>
#include <thread>

using namespace std;

class rw_mutex {
 public:
  rw_mutex(){
    // Initialize private variables
    writerFlag.store(0);
    readerCount.store(0);
  }

  void lock_reader() {
    while (writerFlag.load()) {
      // Wait until the writer releases the token
      this_thread::yield();
    }

    readerCount.fetch_add(1);
  }
  
  void unlock_reader() {
    readerCount.fetch_sub(1);
  }

  void lock() {
    int expected = 0;
    while (!writerFlag.compare_exchange_weak(expected, 1)) {
      // Wait until the writer lowers the flag
      this_thread::yield();
      expected = 0;
    }

    while (readerCount.load() != 0) {
      // Wait until all readers release the mutex
      this_thread::yield();
    }
  }
  
  void unlock() {
    writerFlag.store(0);
  }

 private:
  atomic<int> writerFlag;
  atomic<int> readerCount;
};

