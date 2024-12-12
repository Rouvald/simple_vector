#include "simple_vector.hpp"

#include <vector>
#include <iostream>
#include <string>

template <class T>
void print_vector(const simple_vector<T>& sv, const std::string& msg)
{
    std::cout << msg << ": ";
    for (uint32_t index = 0; index < sv.size(); ++index)
    {
        std::cout << sv.at(index) << ' ';
    }
    std::cout << std::endl;
}

template <class T>
void test_dtor(const uint32_t& size)
{
    simple_vector<T> vec(size);
}

int main()
{
    // test simple_vector work

    simple_vector<uint32_t> vec_1(5);
    simple_vector<uint32_t> vec_2(5);

    for (uint32_t index = 0; index < vec_1.size(); ++index)
    {
        vec_1.at(index) = index + 13;
        vec_2.at(index) = index + 23;
    }

    print_vector(vec_1, "test");
    print_vector(vec_2, "test");

    vec_1 = std::move(vec_2);

    print_vector(vec_1, "test");

    simple_vector<uint32_t> vec_3(std::move(vec_1));

    return 0;
}
