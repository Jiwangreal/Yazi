#pragma once

#include <iostream>
#include <string>

#include "Singleton.h"
using namespace std;

class A {
public:
  static A *instance() {
    if (m_instance == nullptr) {
      m_instance = new A();
    }
    return m_instance;
  }
  void show() { std::cout << "A: " << m_name << std::endl; }

private:
  A() : m_name("A") {}
  A(const A &) = default;
  ~A() { delete m_instance; }
  A &operator=(A const &) = default;

private:
  string m_name;
  static A *m_instance;
};

A *A::m_instance = nullptr;

using namespace yazi::utility;
class B {
  // 使用friend的方式调用B的私有构造函数
  friend class Singleton<B>;

public:
  void show() { std::cout << "B: " << m_name << std::endl; }

private:
  B() : m_name("B") {}

  B(const B &) = default;
  ~B() = default;
  B &operator=(B const &) = default;

private:
  string m_name;
};
