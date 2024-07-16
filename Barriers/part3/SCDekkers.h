#include <atomic>

class dekkers_mutex {
public:
  dekkers_mutex() {
    // implement me!
    wants_to_enter = new std::atomic<bool>[2];
    turn.store(0);
  }

  void lock(int tid) {
    // implement me!
    int other = tid == 0 ? 1 : 0;
    wants_to_enter[tid].store(true);
    while (wants_to_enter[other].load()){
      if (turn.load() != tid){
        wants_to_enter[tid].store(false);
        while (turn.load() != tid){

        };
        wants_to_enter[tid].store(true);
      }
    }
  }

  void unlock(int tid) {
    // implement me!
    int other = tid == 0 ? 1 : 0;
    turn.store(other);
    wants_to_enter[tid].store(false);
  }

private:
  // Give me some private variables  
  std::atomic<bool> *wants_to_enter;
  std::atomic<int> turn;
};
