#include <iostream>
#include "CurrentThread.cc"

using namespace std;

int main()
{
    string stackStr = mylib::CurrentThread::stackTrace(true);
    cout << stackStr << endl;
}
