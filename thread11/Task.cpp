#include "thread11/Task.h"
#include "thread11/AutoLock.h"

using namespace yazi::thread11;

Task::Task(): m_data(NULL)
{
}

Task::Task(void* data): m_data(data)
{
}

Task::~Task()
{
}

void* Task::get_data()
{
    AutoLock lock(&m_mutex);
    return m_data;
}

void Task::set_data(void* data)
{
    AutoLock lock(&m_mutex);
    m_data = data;
}
