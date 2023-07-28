#ifndef SRC_THREADSAFE_QUEUE_H_
#define SRC_THREADSAFE_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class threadsafe_queue {
 public:
  threadsafe_queue() { };
  threadsafe_queue(const threadsafe_queue& other) {
    std::lock_guard<std::mutex> guard(other.mx);
    que = other.que;
  }

  threadsafe_queue& operator= (const threadsafe_queue&) = delete;
  ~ threadsafe_queue() { }

  void push(T val) {
    std::lock_guard<std::mutex> guard(mx);
    que.push(val);
    data_cond.notify_one();
    return;
  }
  
  bool try_pop(T& value) {
    std::lock_guard<std::mutex> guard(mx);
    if (que.empty()) {
      return false;
    }
    value = que.front();
    que.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> guard(mx);
    if (que.empty()) {
      return nullptr;
    }
    std::shared_ptr<T> res = std::make_shared<T>(que.front());
    que.pop();
    return res;
  }

  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> ulk(mx);
    data_cond.wait(ulk, [this](){ return !que.empty(); });
    value = que.front();
    que.pop();
    return;
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> ulk(mx);
    data_cond.wait(ulk, [this](){ return !que.empty(); });
    std::shared_ptr<T> res = std::make_shared<T>(que.front());
    que.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> guard(mx);
    return que.empty();
  }

 private:
  std::queue<T> que;
  mutable std::mutex mx;
  std::condition_variable data_cond;
};


#endif // SRC_THREADSAFE_QUEUE_H_