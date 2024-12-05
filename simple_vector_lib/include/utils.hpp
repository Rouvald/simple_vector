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

    inline uint32_t calculate_capacity(const uint32_t& size)
    {
        // @todo: fix? diff formula or round
        return static_cast<uint32_t>(static_cast<float>(size) * 1.5f);
    }
};  // namespace utils

#endif  // _UTILS_HPP_