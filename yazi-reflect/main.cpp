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

public:
  Test(const string &name, int age) : m_name(name), m_age(age) {}
  ~Test() {}
};

#define OFFSET(className, fieldName) ((size_t)(&((className *)0)->fieldName))

int main() {
  ClassFactory *factory = Singleton<ClassFactory>::instance();
  Object *a = factory->create_class("A");

  string name;
  a->get("m_name", name);
  a->set("m_name", "kitty");

  int age;
  a->get("m_age", age);
  a->set("m_age", 30);

  a->call("f1");
  a->call("f2");
  a->show();

  // 黑科技方式1：类数据成员反射：获取类数据成员的便宜地址offset（有的编译器不支持）
  auto age_offset = (std::size_t)(&((Test *)0->m_age));
  auto name_offset = (std::size_t)(&((Test *)0->m_name));

  // 等价于auto offset = ::offsetof(Test, m_name);
  auto offset = OFFSET(Test, m_name);

  Test t("wangji", 18);

  // 解决办法：黑科技2，采用
  auto offset_2 = (std::size_t)(&(t.m_name)) - (std::size_t)(&t);

  int age = *(int *)((std::size_t)&t + age_offset);
  std::string name = *(std::string *)((std::size_t)&t + name_offset);

  return 0;
}
