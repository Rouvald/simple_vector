#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cstdint>
#include <string>
#include <iostream>

namespace utils
{
    inline bool assert_with_msg(bool cond, const std::string& msg)
    {
        if (!cond)
        {
            std::cout << msg << std::endl;
        }
        return cond;
    }
};  // namespace utils

#endif  // _UTILS_HPP_