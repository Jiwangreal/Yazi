#pragma once

#include "Condition.h"
#include "Mutex.h"
#include "Task.h"
#include <pthread.h>


namespace yazi {
namespace thread {

class Thread {
public:
  Thread();
  virtual ~Thread();

  virtual void run() = 0;

  void start();
  void stop();

  void set_task(Task *task);
  Task *get_task();

protected:
  static void *thread_func(void *ptr);

protected:
  pthread_t m_tid;
  Task *m_task;
  Mutex m_mutex;
  Condition m_cond;
};

} // namespace thread
} // namespace yazi
