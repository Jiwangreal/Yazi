#pragma once
#include "thread11/AutoLock.h"
#include "thread11/Condition.h"
#include "thread11/Mutex.h"
#include "thread11/Task.h"
#include "thread11/Thread.h"
#include <set>

namespace yazi {
namespace thread11 {

class ThreadPool {
public:
  ThreadPool();
  ~ThreadPool();

  void create(int threads);

  Thread *get_idle_thread();

  void move_to_idle_list(Thread *thread);
  void move_to_busy_list(Thread *thread);

  int get_idle_thread_numbers();
  int get_busy_thread_numbers();

  void assign(Task *task);

private:
  int m_threads;

  std::set<Thread *> m_list_idle;
  std::set<Thread *> m_list_busy;

  Mutex m_mutex_idle;
  Mutex m_mutex_busy;

  Condition m_cond_idle;
  Condition m_cond_busy;
};

} // namespace thread
} // namespace yazi
