#include <iostream>
#include <thread>

#include "threadsafe_queue.h"

threadsafe_queue<int> ique;

void push_func() {
  for (int i = 0; i < 200; i ++) {
    ique.push(i);
    std::cout << "push: " << i << std::endl;
  }
  return;
}

void pop_func() {
  int tmp = 0;
  for (int i = 0; i < 100; i ++) {
    ique.wait_and_pop(tmp);
    std::cout << "pop: " << tmp << std::endl;
  }
  return;
}


int main() {
  std::thread push_thread(push_func);
  std::thread pop_thread(pop_func);

  push_thread.join();
  pop_thread.join();
  return 0;
}