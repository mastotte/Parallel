#include <atomic>
#include <thread>
#include <iostream>
#include <iomanip>
#define CQUEUE_SIZE 2048

class CQueue {
 public:

  CQueue() {
    // Implement me!
    head.store(0);
    tail.store(0);
  }

  void enq(float e) {
    // Implement me!
    while(size()+1 >= CQUEUE_SIZE){
      std::this_thread::yield();
    }
    buffer[head.load()%CQUEUE_SIZE] = e;
    head.fetch_add(1);
  }

  float deq() {
    // Implement me!
    while(size() == 0){
      std::this_thread::yield();
    }
    float val = buffer[tail.load()%CQUEUE_SIZE];
    tail.fetch_add(1);
    return val;
  }

  int size() {
    // Implement me!
    return head.load() - tail.load();
  }

  void deq_8(float e[8]) {
    // Implement me for part 3
    while (size() < 8){
      std::this_thread::yield();
    }
    tail.fetch_add(8);
    for(int i = 0; i < 8; i++){
      e[i] = deq();
    }
  }

  void enq_8(float e[8]) {
    // Implement me for part 3
    while (size() >= CQUEUE_SIZE-8){
      std::this_thread::yield();
    }
    head.fetch_add(8);
    for(int i = 0; i < 8; i++){
      enq(e[i]);
    }
  }
  
 private:
  std::atomic<int> head;
  std::atomic<int> tail;
  float buffer[CQUEUE_SIZE];
  // give me some variables!
};
