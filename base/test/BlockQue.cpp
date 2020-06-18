#include <iostream>
#include "../BlockingQueue.h"

int main() {
    mylib::BlockingQueue<int> bq;
    bq.put(5);
    int res = bq.take();
    std::cout << res << std::endl;
    int n = bq.size();
    std::cout << "n = " << n << std::endl;
}

