#include "thread11/Thread.h"
using namespace yazi::thread11;

Thread::Thread(): m_task(NULL)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    std::thread t{Thread::thread_func, this};
    t.detach();
}

void Thread::stop()
{

}

void* Thread::thread_func(void* ptr)
{
    Thread* thread = (Thread*)ptr;
    thread->run();
    return ptr;
}

void Thread::set_task(Task* task)
{
    m_mutex.lock();
    m_task = task;
    m_cond.signal();
    m_mutex.unlock();
}

Task* Thread::get_task()
{
    AutoLock lock(&m_mutex);
    return m_task;
}
