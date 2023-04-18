#pragma once
#include "thread11/Task.h"

namespace yazi
{
    namespace task11 {
        class EchoTask: public Task {

            EchoTask(int* num): Task((void*)num) {}
            virtual ~EchoTask() {}

            virtual void run() override
            {
                printf("task run\n");
                int* input = static_cast<int*>(m_data);
                printf("num:}%d\n", *input);
                usleep(1000000);
            }

            virtual void destroy() override
            {
                printf("task destory");
                delete static_cast<int*>(m_data);
                delete this;
            }
        };


    }

} // namespace name



