
#include "utility/IniFile.h"
#include "utility/NewLogger.h"
#include "utility/Singleton.h"
#include "utility/SingletonA.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sys/time.h>
#include <list>


using namespace std;
using namespace yazi::utility;

#define __NEW_FILENAME__                                                       \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __NEW_FILENAME_1__ (strrchr(__FILE__, '/') + 1)
#define BASENAME(str) (strrchr(str, '/') ? strrchr(str, '/') + 1 : str)

char*
Getbasename(char* url)
{
  auto result = strchr(url, '/');
  while (result) {
    url++;
    result = strchr(url, '/');
    if (result == nullptr) {
      break;
    }
  }
  return url;
}

TEST(TestValue, IniFile)
{
  Value v(1);
  int v1 = v; // 等价于int v1 = (int)v;

  Value v2("hello world");
  string t_v2 = v2;

  string s = " 123  ";
  s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
  std::cout << s << std::endl;
  EXPECT_EQ(s, "123");

  IniFile ini;
  ini.load(INI_FILE);
  ini.show();

  string ip = ini["server"]["ip"];
  EXPECT_EQ(ip, "127.0.0.1");

  using namespace yazi::NEW_UTILITY;
  Logger::instace()->open("./txt.log");
  Logger::instace()->log(Logger::ERROR, __FILE__, __LINE__, "china no 1");
  char str[] = "/home/wangji/txt.log";
  std::cout << Getbasename(str) << std::endl;
  std::cout << __NEW_FILENAME__ << std::endl;
  std::cout << __NEW_FILENAME_1__ << std::endl;
  std::cout << BASENAME(str) << std::endl;

  // Logger::instace()->setLevel(Logger::INFO);

  debug("wang yan xi");
  info("info: wang yan xi");
  // Logger::instace()->setLevel(Logger::DEBUG);
  Logger::instace()->max(1024); // 单位是bytes
  info("info: wang yan xi");
  info("info: wang yan xi");
  info("info: wang yan xi");
  info("info: wang yan xi");
  info("info: wang yan xi");
  info("info: wang yan xi");
  info("info: wang yan xi");
}

TEST(TestSIngletonA, SIngletonA)
{

  A::instance()->show();
  Singleton<B>::instance()->show();
}

TEST(TestSomeFunctions, Functions)
{
  std::list<int> l = { 1,2,3 };
  auto node = l.begin();
  std::cout << *(std::next(node, 1)) << std::endl;



}
