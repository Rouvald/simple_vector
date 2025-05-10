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
        vec_1.data()[index] = index + 13;
        vec_2.data()[index] = index + 100;
    }

    for (uint32_t index = 0; index < vec_1.capacity(); ++index)
    {
        std::cout << vec_1.data()[index] << std::endl;
    }

    vec_1.resize(2);
    std::cout << &vec_1.data()[0] << std::endl;
    ;
    std::cout << &vec_2.data()[0] << std::endl;
    ;

    print_vector(vec_1, "vec_1");
    print_vector(vec_2, "vec_2");
    vec_2 = std::move(vec_1);
    std::cout << &vec_1.data()[0] << std::endl;
    ;
    std::cout << &vec_2.data()[0] << std::endl;
    ;

    print_vector(vec_2, "vec_2");

    simple_vector<uint32_t> vec_3(std::move(vec_2));

    std::cout << &vec_2.data()[0] << std::endl;
    ;
    std::cout << &vec_3.data()[0] << std::endl;
    ;

    print_vector(vec_3, "vec_3");

    return 0;
}
