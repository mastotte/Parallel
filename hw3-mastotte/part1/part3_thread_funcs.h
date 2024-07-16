void memory_load_thread_func(float *a, int size) {
  float *buf = new float[8];
  for (int i = 0; i < size; i+=8) {
    for (int j = 0; j < 8; j++){
      buf[j] = a[i+j];
    }
    memory_to_trig.enq_8(buf);
  }
}

void trig_thread_func(int size) {
  float *buf = new float[8];
  float *to_store = new float[8];
  for (int i = 0; i < size; i+=8) {
    memory_to_trig.deq_8(buf);
    
    for (int j = 0; j < 8; j++){
      to_store[j] = cos(buf[j]);
    }
    
    trig_to_memory.enq_8(to_store);
  }
}

void memory_store_thread_func(float *a, int size) {
  float *buf = new float[8];
  float *to_store = new float[8];
  for (int i = 0; i < size; i+=8) {
    trig_to_memory.deq_8(to_store);
    
    for (int j = 0; j < 8; j++){
      a[i+j] = to_store[j];
    } 
  }
}