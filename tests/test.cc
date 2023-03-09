
#include "IniFile.h"
#include "NewLogger.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace yazi::utility;

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
}
