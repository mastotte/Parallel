#pragma once

#include <atomic>
#include <vector>
#include <thread>
#include <iostream>
#include <bits/stdc++.h>

class mutex {
 public:
  mutex() {
    mutex_lock.store(0);
    ticket_lock.store(0);
    max_ticket.store(0);
    picked_ticket.store(1);
  }
  
  void init (int num_threads) {
    // Implement me!
    numberOfThreads = num_threads;
  }
  
  void lock(int thread_id) {
    // Implement me!
    int i = thread_id;
    while (ticket_lock.load() != 0){
      std::this_thread::yield();
    }
    ticket_lock.store(1);
    int my_ticket = max_ticket.load() + 1;
    max_ticket.store(my_ticket);
    ticket_lock.store(0);

    while(true){
      while(mutex_lock.load() != 0){
        std::this_thread::yield();
      }
      mutex_lock.store(1);
      if (picked_ticket.load() == my_ticket){
        break;
      }
      mutex_lock.store(0);
    }
    
    //mutex_lock.store(1);
    /*if (picked_ticket.load() != my_ticket){
      std::cout<<"Picked Ticket: "<<picked_ticket<<" My Ticket: "<<my_ticket<<std::endl;
    }*/
    std::cout<<my_ticket<<" ID: "<<i<<std::endl;
    picked_ticket.store(picked_ticket.load() + 1);
  }
  
  void unlock(int thread_id) {
    // Implement me!
    mutex_lock.store(0);
  }

 private:
  // Give me some private variables!
  std::atomic<int> mutex_lock;
  std::atomic<int> picked_ticket;
  std::atomic<int> max_ticket;
  std::atomic<int> ticket_lock;
  int numberOfThreads;
};
#pragma once

#include <atomic>
#include <vector>
#include <thread>

class mutex {
 public:
  mutex() {
    // Implement me!
  }
  
  void init (int num_threads) {
    // Implement me!
  }
  
  void lock(int thread_id) {
    // Implement me!
  }
  
  void unlock(int thread_id) {
    // Implement me!
  }

 private:
  // Give me some private variables!
}