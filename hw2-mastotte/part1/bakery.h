#pragma once

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
class mutex {
 public:
  mutex() {
    // nothing
  }
  
  void init (int num_threads) {
    // Implement me!
    numberOfThreads = num_threads;
    flag.resize(num_threads, false); // initialize to false
    label.resize(num_threads, 0); // initialize to 0
  }
  
  void lock(int thread_id) {
    // Implement me!
    int i = thread_id;
    flag[i] = true;
    label[i] = *max_element(label.begin(), label.end()) + 1; // get maximum element
    bool not_first_in_line = true;
    while(not_first_in_line){
      not_first_in_line = false;
      for (int k = 0; k < numberOfThreads; k++){
        // check the condition: ((∃k != i)(flag[k] && (label[k],k) << (label[i],i)))
        if (k != i && flag[k] == true && ((label[k] < label[i]) || (label[k] == label[i] && k < i))){
          not_first_in_line = true;
        }
      }
      std::this_thread::yield();
    }
  }
  
  void unlock(int thread_id) {
    // Implement me!
    flag[thread_id] = false;
  }

 private:
  // Give me some private variables!
  int numberOfThreads;
  std::vector<bool> flag;
  std::vector<int> label;
};