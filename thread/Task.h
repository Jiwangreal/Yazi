#pragma once
#include "Mutex.h"

namespace yazi {
namespace thread {
class Task {
public:
  Task();
  Task(void *data);
  virtual ~Task();

  void *get_data();
  void set_data(void *data);

  virtual void run() = 0;
  virtual void destroy() = 0;

protected:
  void *m_data; // task携带的数据
  Mutex m_mutex;
};

} // namespace thread
} // namespace yazi