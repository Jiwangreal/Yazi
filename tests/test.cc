
#include "utility/IniFile.h"
#include "utility/NewLogger.h"
#include "utility/Singleton.h"
#include "utility/SingletonA.h"
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <thread>
#include <unordered_map>

using namespace std;
using namespace yazi::utility;
using namespace std::chrono;

#define __NEW_FILENAME__                                                       \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __NEW_FILENAME_1__ (strrchr(__FILE__, '/') + 1)
#define BASENAME(str) (strrchr(str, '/') ? strrchr(str, '/') + 1 : str)

char *Getbasename(char *url) {
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

TEST(TestValue, IniFile) {
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

TEST(TestSIngletonA, SIngletonA) {

  A::instance()->show();
  Singleton<B>::instance()->show();
}

TEST(TestSomeFunctions, Functions) {
  std::list<int> l = {1, 2, 3};
  auto node = l.begin();
  std::cout << *(std::next(node, 1)) << std::endl;

  std::multimap<std::string, int> u_map;
  u_map.emplace(std::make_pair("w", 1));
  u_map.emplace(std::make_pair("w", 2));

  auto start = u_map.lower_bound("w");
  auto last = u_map.upper_bound("w");
  for (; start != last; ++start) {
    std::cout << start->first << "," << start->second << std::endl;
  }
  // std::cout << "u_map[w]" << u_map["w"] << std::endl;
}

class TestClass {
public:
  TestClass() { std::cout << "TestClass" << std::endl; }
  ~TestClass() { std::cout << "~TestClass" << std::endl; }
};

TEST(TestThrow, Throw) {
  auto fun = []() {
    std::shared_ptr<TestClass> ptr = std::make_shared<TestClass>();
    std::this_thread::sleep_for(seconds(1));
    throw std::runtime_error("simiulate RAII and throw");
  };

  try {
    fun();
  } catch (std::exception &e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}
