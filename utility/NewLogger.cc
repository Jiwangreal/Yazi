#include "NewLogger.h"

namespace yazi {
namespace NEW_UTILITY {

const char* Logger::s_level[LEVEL_COUNT] = { "DEBUG",
                                             "INFO",
                                             "WARN",
                                             "ERROR",
                                             "FATAL" };
Logger* Logger::m_instance = nullptr;
Logger*
Logger::instace()
{
  if (m_instance == nullptr)
    m_instance = new Logger();
  return m_instance;
}

Logger::Logger()
  : m_level(DEBUG)
  , m_max(0)
  , m_len(0)
{
}

Logger::~Logger()
{
  close();
}

void
Logger::open(const string& logfile)
{
  m_filename = logfile;
  m_fout.open(logfile, ios::app);
  if (m_fout.fail()) {
    throw std::logic_error("open file faild" + logfile);
  }
  m_fout.seekp(0, ios::end);
  m_len = m_fout.tellp();
}
void
Logger::close()
{
  m_fout.close();
}

void
Logger::log(Level log, const char* file, int line, const char* format, ...)
{
  if (log < m_level)
    return;

  if (m_fout.fail()) {
    throw std::logic_error("open file faild" + m_filename);
  }

  time_t ticks = time(NULL);
  struct tm* ptm = localtime(&ticks);
  char time[32];
  memset(time, 0, sizeof(time));
  strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S  ", ptm);
  const char* outformat = "%s %s %s:%d ";
  auto size =
    snprintf(nullptr, 0, outformat, time, s_level[log], BASENAME(file), line);
  if (size > 0) {
    char* buffer = new char[size + 1];
    snprintf(
      buffer, size + 1, outformat, time, s_level[log], BASENAME(file), line);
    buffer[size + 1] = 0;

    std::cout << buffer << std::endl;
    m_fout << buffer;
    m_len += size;

    delete buffer;
  }

  // 可变参数字符串格式化
  va_list arg_ptr;
  va_start(arg_ptr, format);
  size = vsnprintf(nullptr, 0, format, arg_ptr);
  va_end(arg_ptr);
  if (size > 0) {
    char* contend = new char[size + 1];
    vsnprintf(contend, size + 1, format, arg_ptr);
    contend[size + 1] = 0;
    m_len += size;
    std::cout << contend << std::endl;
    m_fout << contend;
    delete contend;
  }

  m_fout << '\n';
  m_fout.flush();

  if (m_len >= m_max && m_max > 0) {
    rotate();
  }
}

void
Logger::rotate()
{
  close();
  auto ticks = time(nullptr);
  auto ptm = localtime(&ticks);

  char timestamp[32];
  memset(timestamp, 0, sizeof(timestamp));
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d-%H:%M:%S", ptm);
  string filename = m_filename + "_" + timestamp;

  if (rename(m_filename.c_str(), filename.c_str()) != 0) {
    throw std::logic_error("rename log file faild: " + string(strerror(errno)));
  }

  open(m_filename);
}

} // namespace NEW_UTILITY
} // namespace yazi
