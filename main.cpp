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
    std::vector<uint32_t> vec22(0);
    vec22.clear();
    // std::cout << std::endl;
    // std::vector<uint32_t> vecqs = {1, 2, 4, 5, 6};
    // vecqs.reserve(100);
    // auto end{vecqs.end()};
    // std::cout << &vecqs[0] << '\t' << vecqs.size() << '\t' << vecqs.capacity()
    //           << std::endl;
    // vecqs.reserve(9);
    // std::cout << *(end - 1) << std::endl;
    // std::cout << &vecqs[0] << '\t' << vecqs.size() << '\t' << vecqs.capacity()
    //           << std::endl;
    // vecqs.resize(0);
    // std::cout << &vecqs[0] << '\t' << vecqs.size() << '\t' << vecqs.capacity()
    //           << std::endl;
    // vecqs.resize(2);
    // std::cout << &vecqs[0] << '\t' << vecqs.size() << '\t' << vecqs.capacity()
    //           << std::endl;

    // std::vector<uint32_t> vec12324(5);
    // std::vector<uint32_t> vec65765{5};
    // create
    simple_vector<uint32_t> test_1(5);

    print_vector(test_1, "create 5 elem");

    std::cout << std::endl;

    // add value for elems

    for (uint32_t index = 0; index < test_1.size(); ++index)
    {
        test_1.at(index) = index + 13;
    }
    print_vector(test_1, "add +13");

    // check front() and back()

    std::cout << "front: " << test_1.front() << "\t back: " << test_1.back()
              << std::endl;

    // create second simple vector

    simple_vector<int32_t> test_2(8);

    std::cout << "check sizes: " << test_1.size() << ' ' << test_2.size()
              << std::endl;
    std::cout << "check is_empty: " << test_1.is_empty() << ' '
              << test_2.is_empty() << std::endl;

    // reserve

    std::cout << "reserve before: " << test_2.data() << std::endl;
    test_2.reserve(20);
    std::cout << "reserve  after: " << test_2.data() << std::endl;

    // resize

    std::cout << "ptr before: " << test_2.data() << std::endl;
    print_vector(test_2, "resize before: ");

    test_2.resize(20);

    std::cout << "ptr  after: " << test_2.data() << std::endl;
    print_vector(test_2, "resize  after: ");

    // erase

    for (uint32_t index = 0; index < test_2.size(); ++index)
    {
        test_2.at(index) = index + 37;
    }
    print_vector(test_2, "erase before: ");

    for (uint32_t index = test_2.size() - 1; 0 != test_2.size(); --index)
    {
        test_2.erase(index);
    }

    test_2.resize(0);

    for (uint32_t index = 0; index < 3; ++index)
    {
        test_dtor<uint32_t>(index);
    }

    /*************************************************************/
    return 0;
}
