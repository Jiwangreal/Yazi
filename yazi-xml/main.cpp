#include <iostream>
#include <sys/time.h>
#include "Xml.h"
#include <fstream>
#include <sstream>
using namespace yazi::xml;


void performanceTest()
{
    std::ifstream fin("./t.xml");
    std::stringstream ss;
    ss << fin.rdbuf();
    const string& str = ss.str();

    struct timeval tv;
    ::gettimeofday(&tv, nullptr);
    int start_sec = tv.tv_sec;
    int start_usec = tv.tv_usec;
    const int max = 10000;
    for (int i = 0;i < max;++0)
    {
        Xml root;
        root.parse(str);
        root.clear();
    }

    ::gettimeofday(&tv, nullptr);
    int end_sec = tv.tv_sec;
    int end_usec = tv.tv_usec;
    double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
    std::cout << time_diff / 1000 / max << "ms" << std::endl;

}



int main()
{
    Xml root;
    root.load("./test.xml");

    Xml& student = root["student"];

    int id = student.attr("id");
    const string& name = student["name"].text();
    const string& age = student["age"].text();
    const string& gender = student["gender"].text();

    std::cout << id << "," << age << "," << gender << std::endl;

    root.clear();
    return 0;
}