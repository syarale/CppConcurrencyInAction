#include <iostream>
#include <thread>

#include "joining_thread.h"

int main() {
  auto func = [] {
    for (int i = 0; i < 5; i ++) {
      std::cout << "i is : " << i << std::endl; 
    }
  };
  
  joining_thread th1(func);

  std::thread t1(func);
  joining_thread jth2(std::move(t1));

  joining_thread th3(std::move(th1));
  
  joining_thread th4;
  th4 = std::move(th1);

  std::thread t2(func);
  joining_thread th5;
  th5 = std::move(t2);
  th5.detach();

  return 0;
}