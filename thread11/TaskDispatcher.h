#pragma once

#include "thread11/Task.h"
#include "thread11/Thread.h"
#include "thread11/ThreadPool.h"
#include <list>
#include <signal.h>

namespace yazi {
  namespace thread {

    class TaskDispatcher: public Thread {
    public:
      TaskDispatcher();
      ~TaskDispatcher();

      void init(int threads);
      void assign(Task* task);
      void handle(Task* task);
      virtual void run();

    protected:
      std::list<Task*> m_tasks;
    };

  } // namespace thread
} // namespace yazi
