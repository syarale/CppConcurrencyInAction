#ifndef SRC_HIERARCHICAL_H_
#define SRC_HIERARCHICAL_H_

#include <climits>
#include <thread>
#include <mutex>

class hierarchical_mutex {
 public:
  explicit hierarchical_mutex(unsigned long value) : hierarchical_val(value) { }
  hierarchical_mutex(const hierarchical_mutex&) = delete;
  hierarchical_mutex& operator= (const hierarchical_mutex&) = delete;
  ~ hierarchical_mutex() { }

  void lock() {
    check_violation();
    internal_mtx.lock();
    update_thread_val();
    return;
  }

  void unlock() {
    if (curr_thread_val != hierarchical_val) {
      throw std::logic_error("unlock: mutex hierarchical violation");
    }
    curr_thread_val = prev_thread_val;
    internal_mtx.unlock();
    return;
  }

  bool try_lock() {
    check_violation();
    if (!internal_mtx.try_lock()) {
      return false;
    }
    internal_mtx.lock();
    update_thread_val();
    return true;
  }

 private:
  void check_violation() {
    if (curr_thread_val <= hierarchical_val) {
      throw std::logic_error("lock: mutex hierarchical violation");
    }
    return;
  }

  void update_thread_val() {
    prev_thread_val = curr_thread_val;
    curr_thread_val = hierarchical_val;
    return;
  }

  const unsigned long hierarchical_val;
  unsigned long prev_thread_val = 0;
  static thread_local unsigned long curr_thread_val;

  std::mutex internal_mtx;
};

thread_local unsigned long hierarchical_mutex::curr_thread_val = ULONG_MAX;


#endif // SRC_HIERARCHICAL_H_