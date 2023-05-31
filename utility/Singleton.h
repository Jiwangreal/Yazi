#pragma once

namespace yazi {
namespace utility {

template <typename T> class Singleton {
public:
  static T *instance() {
    static T *instance = nullptr;
    if (instance == nullptr) {
      instance = new T();
    }
    return instance;
  }

protected:
  Singleton() {}
  Singleton(const Singleton<T> &);
  Singleton<T> &operator=(const Singleton<T> &);
  ~Singleton() {}
};

template <typename T> T *Singleton<T>::m_instance;

namespace other {
template <typename T> class Singleton {
public:
  static T *instance() {
    if (instance == nullptr) {
      m_instance = new T();
      atexit(destry);
    }
    return m_instance;
  }

protected:
  Singleton() {}
  Singleton(const Singleton<T> &);
  Singleton<T> &operator=(const Singleton<T> &);
  ~Singleton() {}

private:
  static T *m_instance;
  static void destry() { delete m_instance; }
};

template <typename T> T *Singleton<T>::m_instance = nullptr;
} // namespace other

} // namespace utility
} // namespace yazi
