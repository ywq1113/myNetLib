#ifndef MY_TYPES_H
#define MY_TYPES_H

#include <string>
#include <string.h>
#include <stdint.h>

// 如果定义了NDEBUG
// assert会什么也不做，被当作((void)0)
#ifndef NDEBUG
#include <assert.h>
#endif

namespace mylib 
{

    using std::string;

    inline void memZero(void* p, size_t n)
    {
          memset(p, 0, n);
    }

} //namespace

#endif //MY_TYPES_H
