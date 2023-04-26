#include <functional>
#include <iostream>
using namespace std;

#include "ClassFactory.h"
#include <stddef.h>
using namespace yazi::reflect;

#include "test/A.h"

class Test {
public:
  std::string m_name;
  int m_age;
  void f1() { std::cout << "Test::f1" << std::endl; }

  void call() {
    typedef std::function<void(decltype(this))> memeber_method;
    memeber_method method = &Test::f1;
    method(this);
  }

public:
  Test(const string &name, int age) : m_name(name), m_age(age) {}
  ~Test() {}
};

#define OFFSET(className, fieldName) ((size_t)(&((className *)0)->fieldName))

typedef void (*func)(void);
void func1() { std::cout << "func" << std::endl; }

typedef void (Test::*classfunc)(void);
typedef std::function<void(Test *)> test_method;

int main() {
  ClassFactory *factory = Singleton<ClassFactory>::instance();
  Object *a = factory->create_class("A");

  string name;
  a->get("m_name", name);
  a->set("m_name", "kitty");

  int age;
  a->get("m_age", age);
  a->set("m_age", 30);

  auto count = a->get_field_count();

  for (int i = 0; i < count; ++i) {
    auto field = a->get_field(i);
    std::cout << field->name() << "," << field->offset() << std::endl;
  }

  a->call("f1");
  a->call("f2");
  auto ret = a->call("f3", 100);
  a->show();

  {
    func f = func1;
    //   printf("f type %x,%x\n", f, &f);
    // printf("func1 type %x,%x\n", func1, &func1);
    f();

    Test t2{"wangji", 30};
    classfunc f2 = &Test::f1;
    // f2(); // rror: must use ‘.*’ or ‘->*’ to call pointer-to-member function
    // in ‘f2 (...)’, e.g. ‘(... ->* f2) (...)’

    test_method f10 = &Test::f1;
    Test t3{"wangji", 31};
    f10(&t3);
    t3.call();

    uintptr_t f4 = (uintptr_t)&f10;
    (*(test_method *)f4)(&t3);
  }

  {

    // 黑科技方式1：类数据成员反射：获取类数据成员的便宜地址offset（有的编译器不支持）
    // auto age_offset = (std::size_t)(&((Test *)0->m_age));
    // auto name_offset = (std::size_t)(&((Test *)0->m_name));

    // 等价于auto offset = ::offsetof(Test, m_name);
    auto offset = OFFSET(Test, m_name);

    Test t("wangji", 18);

    // 解决办法：黑科技2，采用
    auto offset_2 = (std::size_t)(&(t.m_name)) - (std::size_t)(&t);

    // int age = *(int *)((std::size_t)&t + age_offset);
    // std::string name = *(std::string *)((std::size_t)&t + name_offset);
  }

  return 0;
}
