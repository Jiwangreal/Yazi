#pragma once

#include "Task.h"
#include "Thread.h"
#include "ThreadPool.h"
#include <list>
#include <pthread.h>
#include <signal.h>

namespace yazi {
namespace thread {

class TaskDispatcher : public Thread {
public:
  TaskDispatcher();
  ~TaskDispatcher();

  void init(int threads);
  void assign(Task *task);
  void handle(Task *task);
  virtual void run();

protected:
  std::list<Task *> m_tasks;
};

} // namespace thread
} // namespace yazi
