#include "mylib/base/CurrentThread.h"

#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>

//glibc头文件execinfo.h中声明了三个函数可以获取当前线程函数调用堆栈
//
//
//
namespace mylib
{
namespace CurrentThread
{
__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "null";

static_assert(std::is_same<int, pid_t>::value, "pid_t should be int");

string stackTrace(bool demangle)
{
    string stack;
    const int max_frames = 128;
    void* frame[max_frames];
    int nptrs = backtrace(frame, max_frames);
    char** strings = backtrace_symbols(frame, nptrs);

    if(strings) {
        //分配足够空间给要被demangle函数名的字符
        size_t funcnamelen = 256;
        char* funcname = demangle ? static_cast<char*>(::malloc(funcnamelen)) : nullptr;
        //遍历symbols lines，第一个是此函数的地址
        for(int i = 1; i < nptrs; ++i)
        {
            if(demangle) 
            {
                char* begin_name = nullptr;
                char* begin_offset = nullptr;
                char* end_offset = nullptr;
                //找到函数名和地址偏移量
                //如./module(function+0x15c)[0x8048a6d]

                for(char* p = strings[i]; *p; ++p)
                {
                    if(*p == '(') 
                        begin_name = p;
                    else if(*p == '+') 
                        begin_offset = p;
                    else if(*p == ')' && begin_offset) {
                        end_offset = p;
                        break;
                    }
                }
                if(begin_name && begin_offset &&
                   end_offset && begin_name < begin_offset)
                {
                    *begin_name++ = '\0';
                    *begin_offset++ = '\0';
                    *end_offset++ = '\0';

                    //函数名在[begin_name,begin_offset]
                    //偏移在[begin_offset,end_offset)
                    
                    int status = 0;
                    char* ret = abi::__cxa_demangle(begin_name, funcname, &funcnamelen, &status);
                    if(status == 0)
                    {
                        funcname = ret;
                        stack.append(strings[i], begin_offset-begin_name);
                        stack.append(funcname);
                        stack.push_back('+');
                        stack.push_back('\n');
                        continue;
                    }
                }
            }
            stack.append(strings[i]);
            stack.push_back('\n');
        }
        free(funcname);
        free(strings);
    }
    return stack;
}

} //namespace CurrentThread

} //namespace mylib


