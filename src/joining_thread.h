#ifndef SRC_JOIN_THREAD_H_
#define SRC_JOIN_THREAD_H_

#include <thread>

class joining_thread {
 public:
  joining_thread() noexcept = default;
  
  template<typename  Callable, typename ... Args>
  explicit joining_thread(Callable&& func, Args&& ... args)
      : thread_(std::forward<Callable>(func), std::forward<Args>(args)...) { }
  
  explicit joining_thread(std::thread th) noexcept : thread_(std::move(th)) { }

  explicit joining_thread(const joining_thread&) = delete;
  explicit joining_thread(joining_thread&& jth) noexcept : thread_(std::move(jth.thread_)) { }

  joining_thread& operator= (const joining_thread&) = delete;
  joining_thread& operator= (joining_thread&& jth) noexcept {
    if (joinable()) {
      join();
    }
    thread_ = std::move(jth.thread_);
    return *this;
  }

  joining_thread& operator= (std::thread th) noexcept {
    if (joinable()) {
      join();
    }
    thread_ = std::move(th);
    return *this;
  }

  ~ joining_thread() noexcept{
    if (joinable()) {
      join();
    }
    std::cout << "~ joining_thread ... " << std::endl;
  }

  bool joinable() const noexcept {
    return thread_.joinable();
  }

  void join() {
    thread_.join();
    return;
  }

  void detach() {
    thread_.detach();
    return;
  }

  std::thread& as_thread() noexcept {
    return thread_;
  }

  const std::thread& as_thread() const noexcept {
    return thread_;
  }

  void swap(joining_thread& th) noexcept {
    thread_.swap(th.thread_);
    return;
  }

  std::thread::id get_id() const noexcept {
    return thread_.get_id();
  }

 private:
  std::thread thread_;

};

#endif // SRC_JOIN_THREAD_H_