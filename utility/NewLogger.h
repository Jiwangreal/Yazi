#pragma once
#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <time.h>
using namespace std;
#define BASENAME(str) (strrchr(str, '/') ? strrchr(str, '/') + 1 : str)
namespace yazi {
namespace NEW_UTILITY {

#define debug(format, ...)                                                     \
  Logger::instace()->log(                                                      \
    Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define info(format, ...)                                                      \
  Logger::instace()->log(                                                      \
    Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define warn(format, ...)                                                      \
  Logger::instace()->log(                                                      \
    Logger::WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define error(format, ...)                                                     \
  Logger::instace()->log(                                                      \
    Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

class Logger
{
public:
  enum Level
  {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL,
    LEVEL_COUNT
  };
  static Logger* instace();
  void log(Level log, const char* file, int line, const char* format, ...);
  void open(const string& logfile);
  void close();
  void setLevel(Level level) { m_level = level; }
  void max(int bytes) { m_max = bytes; }

private:
  Logger();
  ~Logger();
  void rotate();

private:
  string m_filename;
  Level m_level;
  ofstream m_fout;
  int m_max;
  int m_len;
  static const char* s_level[LEVEL_COUNT];
  static Logger* m_instance;
};
} // namespace NEW_UTILITY

} // namespace yazi
