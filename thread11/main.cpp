#include <string>
#include <unistd.h>
using namespace std;
#include <utility/Logger.h>
#include <utility/Singleton.h>


#include <thread11/Task.h>
#include <thread11/TaskDispatcher.h>
#include <thread11/EchoTask.h>
using namespace tazi::task11;


int main()
{
    const string logfile = "./main.log";
    Logger::instance()->open(logfile);


    int threads = 8;
    Singleton<TaskDispatcher>::instance()->init(threads);

    for (int i = 0;i < 10;++i)
    {
        int* num = new int(i);
        Task* task = new EchoTask(num);
        Singleton<TaskDispatcher>::instance()->assign(task);
    }

    ::usleep(2000000);
    return 0;
}