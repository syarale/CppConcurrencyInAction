#include <iostream>
#include <thread>

class scoped_thread {
 public:
  explicit scoped_thread(std::thread t)
      : thread_(std::move(t)) {
    if (!thread_.joinable()) {
      throw std::logic_error("No thread");
    }

  }
  ~ scoped_thread() {
    thread_.join();
  }

  scoped_thread(const scoped_thread&) = delete;
  scoped_thread& operator= (const scoped_thread&) = delete;

 private:
  std::thread thread_;
};


int main() {
  auto func = [] {
    for (int i = 0; i < 5; i ++) {
      std::cout << "i is : " << i << std::endl; 
    }
  };
  
  // std::thread t(func);
  // scoped_thread scth(std::move(t));
  scoped_thread scth{std::thread(func)};

  return 0;
}