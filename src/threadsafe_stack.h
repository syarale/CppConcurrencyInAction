#ifndef SRC_THREADSAFE_STACK_H_
#define SRC_THREADSAFE_STACK_H_

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

template<typename T>
class threadsafe_stack {
 public:
  threadsafe_stack() { }
  threadsafe_stack(const threadsafe_stack& stk) {
    std::lock_guard<std::mutex> guard(stk.mx);
    data = stk.data;
  }

  threadsafe_stack& operator= (const threadsafe_stack& stk) = delete;
  ~ threadsafe_stack() { }

  void push(T value) {
    std::lock_guard<std::mutex> guard(mx);
    data.push(std::move(value));  // it's maybe better to use T&& and std::forward.
    return;
  }

  void pop(T& value) {
    std::lock_guard<std::mutex> guard(mx);
    if (data.empty()) {
      throw std::logic_error("empty stack");
    }
    value = data.top();
    data.pop();
    return;
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> guard(mx);
    if (data.empty()) {
      throw std::logic_error("empty stack");
    }
    std::shared_ptr<T> const sptr = std::make_shared<T>(data.top());
    data.pop();
    return sptr;
  }

  bool empty() const {
    std::lock_guard<std::mutex> guard(mx);
    return data.empty();
  }

 private:
  std::stack<T> data;
  mutable std::mutex mx;
};

#endif //SRC_THREADSAFE_STACK_H_