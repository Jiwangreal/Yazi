#pragma once
#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <time.h>
using namespace std;

namespace yazi {
namespace NEW_UTILITY {

class Logger {
public:
  enum Level { DEBUG = 0, INFO, WARN, ERROR, FATAL, LEVEL_COUNT };
  static Logger *instace();
  void log(Level log, const char *file, int line, const char *format, ...);
  void open(const string &logfile);
  void close();

private:
  Logger() = default;
  ~Logger() = default;

private:
  string m_filename;
  ofstream m_fout;
  static const char *s_level[LEVEL_COUNT];
  static Logger *m_instance;
};
} // namespace NEW_UTILITY

} // namespace yazi
