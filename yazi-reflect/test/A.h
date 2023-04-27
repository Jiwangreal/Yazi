#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "ClassRegister.h"
using namespace yazi::reflect;

class A : public Object {
public:
  A() : m_name("a"), m_age(18) {}

  void show() {
    std::cout << "name=" << m_name << ",age=" << m_age << std::endl;
  }

  void f1() { std::cout << "f1" << std::endl; }

  void f2() { std::cout << "f2" << std::endl; }

  int f3(int num) {
    std::cout << "f3"
              << "," << num << std::endl;

    this->m_name = "b";
    std::cout << "m_name: " << m_name << std::endl;
    std::cout << this << std::endl;

    return num;
  }

public:
  string m_name;
  int m_age;
};

// 注册的类的头文件中创建一个全局变量
// 注册的位置：最好写到被反射类的.cc文件中，否则会反复注册
REGISTER_CLASS(A);
REGISTER_CLASS_FIELD(A, m_name, string);
REGISTER_CLASS_FIELD(A, m_age, int);
REGISTER_CLASS_METHOD(A, f1);
REGISTER_CLASS_METHOD(A, f2);
REGISTER_CLASS_METHOD_PARAMETERS(A, f3)