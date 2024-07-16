#include <shared_mutex>
using namespace std;

class Llist_node {
 public:  
  Llist_node(int d) {   
    data = d;
    next = NULL;
  }
  
  int data;
  Llist_node *next;
};

class CSE113_Stack {
 public:
  
  CSE113_Stack() {
    start = NULL;
  }
  
  int pop() {
    rw.lock();
    if (start == NULL) {
      rw.unlock();
      return -1;
    }

    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      rw.unlock();
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL) {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;
    rw.unlock();
    return ret;
  }

  
  int peek() {
    rw.lock_shared();
    if (start == NULL) {
      rw.unlock_shared();
      return -1;
    }
    
    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }
    int result = current->data;
    rw.unlock_shared();
    return result;    
  }
  
  void push(int p) {
    rw.lock();
    if (start == NULL) {

      start = new Llist_node(p);
      rw.unlock();
      return;
    }

    Llist_node *current = start;
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new Llist_node(p);
    rw.unlock();
  }

  void swaptop(int to_swap) {
    // Implement me!
    rw.lock();
    if (start == NULL){
      rw.unlock();
      return;
    }else{
      start->data = to_swap;
    }
    rw.unlock();
  }

 private:
  Llist_node *start; 
  shared_mutex rw; 
};
