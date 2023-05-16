#include "WorkerThread.h"

#include "Logger.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "Task.h"
#include "ThreadPool.h"
using namespace yazi::thread;

WorkerThread::WorkerThread() : Thread() {}

WorkerThread::~WorkerThread() {}

void WorkerThread::cleanup(void *ptr) {
  info("worker thread cleanup handler: %x", ptr);
}

void WorkerThread::run() {
  sigset_t mask;
  if (0 != sigfillset(&mask)) {
    error("worker thread sigfillset faile!");
  }
  if (0 != pthread_sigmask(SIG_SETMASK, &mask, NULL)) {
    error("worker thread pthread_sigmask failed");
  }
  // 线程退出可能执行的函数
  pthread_cleanup_push(cleanup, this);

  while (true) {
    // start wait for task
    m_mutex.lock();
    while (m_task == NULL)
      m_cond.wait(&m_mutex);
    m_mutex.unlock();
    // end wait for task

    int rc = 0;
    int old_state = 0;
    rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);

    m_task->run();
    m_task->destroy();
    m_task = NULL;

    Singleton<ThreadPool>::instance()->move_to_idle_list(this);

    // Linux|
    // |pthread_cancel函数&&取消点(https://blog.csdn.net/qq_40399012/article/details/84255522)
    rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);
    pthread_testcancel(); // cancel-point
  }
  pthread_cleanup_pop(1);
}
