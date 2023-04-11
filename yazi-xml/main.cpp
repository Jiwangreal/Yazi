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
    for (int i = 0;i < max;++i)
    {
        Xml root;
        root.parse(str);
        std::cout << root.str() << std::endl;
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
    //  error: cannot bind non-const lvalue reference of type ‘std::string&’ {aka ‘std::__cxx11::basic_string<char>&’} to an rvalue of type ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’}
/**
因为强转得到一个临时对象string，是个右值
In file included from main.cpp:3:
./xml/Xml.h:35:5: note:   after user-defined conversion: ‘yazi::xml::Value::operator std::string()’
   35 |     operator string();
      |     ^~~~~~~~
**/
// std::string& out_class = student.attr("class");//error
    const std::string& out_class = student.attr("class");//ok
    const string& name = student["name"].text();
    const string& age = student["age"].text();
    const string& gender = student["gender"].text();

    std::cout << id << "," << age << "," << gender << std::endl;
    std::cout << out_class << std::endl;



    for (Xml::iterator it = root["student"].begin(); it != root["student"].end();++it)
    {
        std::cout << it->name() << "," << it->text() << std::endl;
    }

    root.clear();
    return 0;
}