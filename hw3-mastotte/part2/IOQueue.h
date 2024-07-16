#include <atomic>
class IOQueue {
 public:
  IOQueue() {
    front.store(0);
    end.store(0);
  }

  // Use this function to initialize the queue to
  // the size that you need.
  void init(int size) {
    queue = new int[size];
  }

  // enqueue the element e into the queue
  void enq(int e) {
    int reserved_index =  std::atomic_fetch_add(&end, 1);
    queue[reserved_index] = e;
  }

  // return a value from the queue.
  // return -1 if there is no more values
  // from the queue.
  int deq() {
    if(size() == 0){
      return -1;
    }
    int reserved_index = atomic_fetch_add(&front, 1);
    return queue[reserved_index];
  }

  int size() {
    // Implement me!
    return end.load() - front.load();
  }

  // return 32 values from the queue. The
  // values should be returned through
  // the array passed in.
  // return 0 if successful. return -1 if not
  // i.e. if the queue does not have 32 elements
  int deq_32(int ret[32]) {
    if(size() < 32){
      return -1;
    }
    int reserved_index = front.load();
    atomic_fetch_add(&front, 32);
    for(int i = 0; i < 32; i++){
      ret[i] = queue[reserved_index+i];
    }
    return 0;
  }

 private:
  // Give me some private variables
  std::atomic<int> front;
  std::atomic<int> end;
  int* queue;

};
