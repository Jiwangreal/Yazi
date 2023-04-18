#pragma once

#include <pthread.h>
#include <signal.h>

#include "thread11/Thread.h"

namespace yazi {

    namespace thread11 {
        class WorkerThread: public Thread
        {
        public:
            WorkerThread();
            virtual ~WorkerThread();
            virtual void run();
            static void cleanup(void* ptr);
        };
    }
}
