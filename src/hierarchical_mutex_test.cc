#include <iostream>
#include <mutex>

#include "hierarchical_mutex.h"

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff() {
  return 42;
}

int low_level_func() {
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int some_param){ }
void high_level_func() {
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
  return;
}

void thread_a() {
  high_level_func();
  return;
}

hierarchical_mutex other_mutex(100);
void do_other_stuff() { }

void other_stuff() {
  high_level_func();
  do_other_stuff();
  return;
}

void thread_b() {
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_stuff();
  return;
}

int main() {
  std::thread a_thread(thread_a);
  a_thread.join();
  // std::thread b_thread(thread_b);
  // b_thread.join();
  return 0;
}