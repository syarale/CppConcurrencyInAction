#include <iostream>
#include <thread>

class thread_guard {
 public:
  explicit thread_guard(std::thread& t) : thread_(t) { }
  ~ thread_guard() {
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  thread_guard(const thread_guard&) = delete;
  thread_guard& operator= (const thread_guard&) = delete;

 private:
  std::thread& thread_;
};


int main() {
  auto func = [] {
    for (int i = 0; i < 5; i ++) {
      std::cout << "i is : " << i << std::endl; 
    }
  };
  
  std::thread t(func);
  thread_guard guard(t);

  return 0;
}