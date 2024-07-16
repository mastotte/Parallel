#include <atomic>
#include <thread>
class CQueue {
 public:

  CQueue() {
    // Implement me!
    flag.store(false);
  }

  void enq(float e) {
    // Implement me!
    box.store(e);
    flag.store(true);
    while(flag.load() == true){
      std::this_thread::yield();
    }
  }

  float deq() {
    // Implement me!
    while(flag.load() == false){
      std::this_thread::yield();
    }
    float val = box.load();
    flag.store(false);
    return val;
  }
  
 private:
  std::atomic<float> box;
  std::atomic<bool> flag;
  // Give me some private variables 
};
