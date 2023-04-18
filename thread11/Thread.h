#pragma once

#include <thread>
#include <thread11/Task.h>
#include <thread11/Mutex.h>
#include <thread11/Condition.h>

namespace yazi {
    namespace thread11 {

        class Thread
        {
        public:
            Thread();
            virtual ~Thread();

            virtual void run() = 0;

            void start();
            void stop();

            void set_task(Task* task);
            Task* get_task();

        protected:
            static void* thread_func(void* ptr);

        protected:
            Task* m_task;
            Mutex               m_mutex;
            Condition           m_cond;
        };

    }
}