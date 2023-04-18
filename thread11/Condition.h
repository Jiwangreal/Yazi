#pragma once

#include <pthread.h>
#include "thread11/Mutex.h"

namespace yazi {
    namespace thread11 {

        class Condition
        {
        public:
            Condition();
            ~Condition();

            int wait(Mutex* mutex);
            int signal();
            int broadcast();

        protected:
            pthread_cond_t      m_cond;
            //pthread_condattr_t  m_attr;

        };

    }
}
