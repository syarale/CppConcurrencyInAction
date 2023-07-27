#include <iostream>
#include <thread>

#include "threadsafe_stack.h"


int main() {
  threadsafe_stack<int> stk;
  auto push_func = [&stk](int num) {
    for (int i = 0; i < num; i ++) {
      std::cout << "push: " << i << std::endl;
      stk.push(i);
    }
  };

  auto pop_func1 = [&stk](int trys) {
    for (int i = 0; i < trys; i ++) {
      if (!stk.empty()) {
        try {
          int tmp = 0;
          stk.pop(tmp);
          std::cout << "pop: " << tmp << std::endl;
        } catch(...) {

        }
      }
    }
  };

  auto pop_func2 = [&stk](int trys) {
    for (int i = 0; i < trys; i ++) {
      if (!stk.empty()) {
        try {
          std::shared_ptr<int> sptr = stk.pop();
          std::cout << "pop: " << *sptr << std::endl;
        } catch(...) { }
      }
    }
  };

  // std::thread pop_thread(pop_func1, 100000);
  std::thread pop_thread(pop_func2, 10000);
  std::thread push_thread(push_func, 20);
  
  push_thread.join();
  pop_thread.join();

  return 0;
}