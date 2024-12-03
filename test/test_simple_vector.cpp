#include "simple_vector.hpp"
#include "utils.hpp"
#include <gtest/gtest.h>
#include <random>

// @todo: global TODO: rewrite all notes with possible variants

template <class T>
struct test_data_ptr
{
    bool b_need_test_ptr{false};
    bool b_is_ptr_equals{true};
    T* data_ptr{nullptr};
};

template <class T>
struct test_simple_vector
{
    bool b_is_data_null{true};
    test_data_ptr<T> test_data{0};
    uint32_t _size{0};
    uint32_t _capacity{0};
};

uint32_t random_value(const uint32_t& min, const uint32_t& max)
{
    if (max < min || max == min)
        return 0;

    const uint32_t diap_vals{max - min};
    return (std::rand() % diap_vals) + min;
}

// @todo we have 2 equals methods, need optimiazztion
// @note: test default getters values
template <class T>
void test_getters_methods_vals(
    simple_vector<T>& vec, const test_simple_vector<T>& exp_data)
{
    EXPECT_TRUE(exp_data.b_is_data_null ? vec.data() == nullptr
                                        : vec.data() != nullptr);

    if (exp_data.test_data.b_need_test_ptr)
    {
        EXPECT_TRUE(exp_data.test_data.b_is_ptr_equals
                        ? vec.data() == exp_data.test_data.data_ptr
                        : vec.data() != exp_data.test_data.data_ptr);
    }
    EXPECT_EQ(vec.size(), exp_data._size);
    EXPECT_EQ(vec.capacity(), exp_data._capacity);
}

// @note: test const getterss
template <class T>
void test_getters_methods_const_vals(
    const simple_vector<T>& vec, const test_simple_vector<T>& exp_data)
{
    EXPECT_TRUE(exp_data.b_is_data_null ? vec.data() == nullptr
                                        : vec.data() != nullptr);

    if (exp_data.test_data.b_need_test_ptr)
    {
        EXPECT_TRUE(exp_data.test_data.b_is_ptr_equals
                        ? vec.data() == exp_data.test_data.data_ptr
                        : vec.data() != exp_data.test_data.data_ptr);
    }
    EXPECT_EQ(vec.size(), exp_data._size);
    EXPECT_EQ(vec.capacity(), exp_data._capacity);
}

template <class T>
void test_vector_data(
    simple_vector<T>& vec, const test_simple_vector<T>& exp_data)
{
    test_getters_methods_vals(vec, exp_data);
    //test_getters_methods_vals( const_cast<simple_vector<T>&>(vec), exp_data);
    test_getters_methods_const_vals(vec, exp_data);
}

TEST(test_simple_vector, ctor_def)
{
    simple_vector<uint32_t> vec;
    constexpr test_simple_vector<uint32_t> exp_data{true, {0}, 0, 0};

    test_vector_data(vec, exp_data);
}

TEST(test_simple_vector, ctor_with_size)
{
    // @note: size == 0
    {
        constexpr uint32_t size_1{0};
        simple_vector<uint32_t> vec_1{size_1};
        const test_simple_vector<uint32_t> exp_data_1{
            true, {0}, size_1, utils::calculate_capacity(size_1)};

        test_vector_data(vec_1, exp_data_1);
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2 = 5;
        simple_vector<uint32_t> vec_2{size_2};
        const test_simple_vector<uint32_t> exp_data_2{
            false, {0}, size_2, utils::calculate_capacity(size_2)};
        //
        test_vector_data(vec_2, exp_data_2);

        for (uint32_t index = 0; index < vec_2.size(); ++index)
        {
            EXPECT_EQ(vec_2.data()[index], 0);
        }
    }
}

TEST(test_simple_vector, ctor_with_vector)
{
    // @note: size == 0
    {
        constexpr uint32_t size_1{0};
        const simple_vector<uint32_t> vec_1_1{size_1};
        simple_vector<uint32_t> vec_1_2{vec_1_1};
        const test_simple_vector<uint32_t> exp_data_1{true, {0}, vec_1_1.size(),
            utils::calculate_capacity(vec_1_1.size())};

        test_vector_data(vec_1_2, exp_data_1);
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2{5};
        const simple_vector<uint32_t> vec_2_1{size_2};
        simple_vector<uint32_t> vec_2_2{vec_2_1};

        const test_simple_vector<uint32_t> exp_data_2{false, {0},
            vec_2_1.size(), utils::calculate_capacity(vec_2_1.size())};

        test_vector_data(vec_2_2, exp_data_2);

        for (uint32_t index = 0; index < vec_2_2.size(); ++index)
        {
            EXPECT_EQ(vec_2_2.data()[index], 0);
        }
    }
    // @note: size != 0, fill random data
    {
        constexpr uint32_t size_3{7};
        simple_vector<uint32_t> vec_3_1{size_3};
        for (uint32_t index = 0; index < vec_3_1.size(); ++index)
        {
            vec_3_1.data()[index] = random_value(0, 100);
        }
        simple_vector<uint32_t> vec_3_2{vec_3_1};

        const test_simple_vector<uint32_t> exp_data_3{false, {0},
            vec_3_1.size(), utils::calculate_capacity(vec_3_1.size())};

        test_vector_data(vec_3_2, exp_data_3);
        for (uint32_t index = 0; index < vec_3_2.size(); ++index)
        {
            EXPECT_EQ(vec_3_2.data()[index], vec_3_1.data()[index]);
        }
    }
}

TEST(test_simple_vector, ctor_copy)
{
    // @note: both vectors size == 0
    {
        constexpr uint32_t size_1{0};
        simple_vector<uint32_t> vec_1_lhs{size_1}, vec_1_rhs{0};
                const test_simple_vector<uint32_t> exp_data_1{
            true, {0}, vec_1_rhs.size(), vec_1_rhs.capacity()};

        vec_1_lhs = vec_1_rhs;
        test_vector_data(vec_1_lhs, exp_data_1);
    }
    // @note: vector 1 size != 0, vector 2 size == 0
    {
        constexpr uint32_t size_2{5};
        simple_vector<uint32_t> vec_2_lhs{0}, vec_2_rhs{size_2};

        const test_simple_vector<uint32_t> exp_data_2{
            false, {true, false, vec_2_lhs.data()}, vec_2_rhs.size(), vec_2_rhs.capacity()};

        vec_2_lhs = vec_2_rhs;

        test_vector_data(vec_2_lhs, exp_data_2);
    }
    // @note: vector 1 size != 0, fill random data, vector 2 size == 0
    {
        constexpr uint32_t size_3{8};
        simple_vector<uint32_t> vec_3_lhs{0}, vec_3_rhs{size_3};
        for (uint32_t index = 0; index < vec_3_rhs.size(); ++index)
        {
            vec_3_rhs.data()[index] = random_value(0, 100);
        }
        const test_simple_vector<uint32_t> exp_data_3{
            false, {0}, vec_3_rhs.size(), vec_3_rhs.capacity()};

        vec_3_lhs = vec_3_rhs;

        test_vector_data(vec_3_lhs, exp_data_3);
    }
    // @note: test diff size copy ctor
    {
        constexpr uint32_t size_4_1{20}, size_4_2{6};
        simple_vector<uint32_t> vec_4_lhs{size_4_1}, vec_4_rhs{size_4_2};
        const test_simple_vector<uint32_t> exp_data_4{
            false, {true, true, vec_4_lhs.data()}, vec_4_rhs.size(), vec_4_lhs.capacity()};

        vec_4_lhs = vec_4_rhs;
        test_vector_data(vec_4_lhs, exp_data_4);
    }
    // @note: test diff size with values copy ctor
    {
        constexpr uint32_t size_5_1{18}, size_5_2{4};
        simple_vector<uint32_t> vec_5_lhs{size_5_1}, vec_5_rhs{size_5_2};
        for (uint32_t index = 0; index < vec_5_rhs.size(); ++index)
        {
            vec_5_rhs.data()[index] = random_value(0, 100);
        }
        const test_simple_vector<uint32_t> exp_data_5{
            false, {true, true, vec_5_lhs.data()}, vec_5_rhs.size(), vec_5_lhs.capacity()};

        vec_5_lhs = vec_5_rhs;
        test_vector_data(vec_5_lhs, exp_data_5);

        for (uint32_t index = 0; index < vec_5_rhs.size(); ++index)
        {
            EXPECT_EQ(vec_5_lhs.data()[index], vec_5_rhs.data()[index]);
        }
    }
}

TEST(test_simple_vector, dtor) 
{
    // @note: test dtor
    simple_vector<uint32_t> vec{10};
    for (uint32_t index = 0; index < vec.size(); ++index)
    {
        vec.data()[index] = random_value(0, 100);
    }
    constexpr test_simple_vector<uint32_t> exp_data{true, {0}, 0, 0};

    vec.~simple_vector();
    test_vector_data(vec, exp_data);
}

TEST(test_simple_vector, methods_at)
{
    // @note: lambdas test const at() methods
    const auto func_const_at_zero_size{[&](const simple_vector<uint32_t>& vec)
        { EXPECT_DEATH(vec.at(0), "ERROR: incorrect size OR index"); }};
    const auto func_const_at_with_data{
        [&](const simple_vector<uint32_t>& vec, const uint32_t* vec_c,
            const uint32_t& size)
        {
            for (uint32_t index = 0; index < size; ++index)
            {
                EXPECT_EQ(vec.at(index), vec_c[index]);
            }
        }};
    // @note: DEATH size == 0
    {
        simple_vector<uint32_t> vec_1;
        EXPECT_DEATH(vec_1.at(0), "ERROR: incorrect size OR index");
        func_const_at_zero_size(vec_1);
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2{5};
        simple_vector<uint32_t> vec_2{size_2};
        uint32_t vec_2_c[size_2] = {0};
        for (uint32_t index = 0; index < vec_2.size(); ++index)
        {
            EXPECT_EQ(vec_2.at(index), vec_2_c[index]);
        }
        func_const_at_with_data(vec_2, vec_2_c, size_2);
    }
    // @note: size != 0, fill random data
    {
        constexpr uint32_t size_3{11};
        simple_vector<uint32_t> vec_3{size_3};
        uint32_t vec_3_c[size_3] = {0};
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            const uint32_t val{random_value(0, 100)};
            vec_3.at(index) = val;
            vec_3_c[index] = val;
        }
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            EXPECT_EQ(vec_3.at(index), vec_3_c[index]);
        }
        func_const_at_with_data(vec_3, vec_3_c, size_3);
    }
}

TEST(test_simple_vector, vec_front)
{
    // @note: DEATH size == 0
    {
        simple_vector<uint32_t> vec_1;
        EXPECT_DEATH(vec_1.front(), "ERROR: incorrect size");
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2{5};
        simple_vector<uint32_t> vec_2{size_2};
        uint32_t vec_2_c[size_2] = {0};
        EXPECT_EQ(vec_2.front(), vec_2_c[0]);
    }
    // @tnote: size != 0, fill random data
    {
        constexpr uint32_t size_3{11};
        simple_vector<uint32_t> vec_3{size_3};
        uint32_t vec_3_c[size_3] = {0};
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            const uint32_t val{random_value(0, 100)};
            vec_3.at(index) = val;
            vec_3_c[index] = val;
        }
        EXPECT_EQ(vec_3.front(), vec_3_c[0]);
    }
}

TEST(test_simple_vector, vec_back)
{
    // @note: DEATH size == 0
    {
        simple_vector<uint32_t> vec_1;
        EXPECT_DEATH(vec_1.back(), "ERROR: incorrect size");
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2{5};
        simple_vector<uint32_t> vec_2{size_2};
        uint32_t vec_2_c[size_2] = {0};
        EXPECT_EQ(vec_2.back(), vec_2_c[size_2 - 1]);
    }
    // @tnote: size != 0, fill random data
    {
        constexpr uint32_t size_3{11};
        simple_vector<uint32_t> vec_3{size_3};
        uint32_t vec_3_c[size_3] = {0};
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            const uint32_t val{random_value(0, 100)};
            vec_3.at(index) = val;
            vec_3_c[index] = val;
        }
        EXPECT_EQ(vec_3.back(), vec_3_c[size_3 - 1]);
    }
}

TEST(test_simple_vector, vec_is_empty)
{
    // @note: szie == 0
    {
        simple_vector<uint32_t> vec_1;
        EXPECT_TRUE(vec_1.is_empty());
    }
    // @note: size != 0
    {
        constexpr uint32_t size_2{13};
        simple_vector<uint32_t> vec_2{size_2};
        EXPECT_FALSE(vec_2.is_empty());
    }
}

TEST(test_simple_vector, vec_reserve)
{
    // @note: size == 0, reserved capacity: 1) == 0, 2) != 0
    {
        constexpr uint32_t capacity_1{5};
        simple_vector<uint32_t> vec;
        test_simple_vector<uint32_t> exp_data_1{true, {0}, 0, 0};

        vec.reserve(0);
        test_vector_data(vec, exp_data_1);

        exp_data_1.b_is_data_null = false;
        exp_data_1._capacity = capacity_1;
        vec.reserve(capacity_1);
        test_vector_data(vec, exp_data_1);
    }
    // @note: size != 0, reserved capacity: 1) < _capacity, 2) > _capacity
    {
        constexpr uint32_t size_2{10}, amount_2{7}, sub{4};
        simple_vector<uint32_t> vec_2{size_2};
        test_simple_vector<uint32_t> exp_data_2{
            false, {true, true, vec_2.data()},
             size_2, vec_2.capacity()
        };

        vec_2.reserve(vec_2.capacity() - sub);
        test_vector_data(vec_2, exp_data_2);

        for (uint32_t index = 0; index < amount_2; ++index)
        {
            const uint32_t val{vec_2.capacity() + random_value(1, 20)};
            vec_2.reserve(val);
            exp_data_2.test_data.data_ptr = vec_2.data();
            exp_data_2._capacity = val;
            test_vector_data(vec_2, exp_data_2);
        }
    }
    // @note: test reserve some size with some value
    {
        constexpr uint32_t size_3{9}, sub{5};
        simple_vector<uint32_t> vec_3{size_3};
        uint32_t vec_3_c[size_3] = {0};

        test_simple_vector<uint32_t> exp_data_3{
            false, {true, true, vec_3.data()},
             size_3, vec_3.capacity()
        };

        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            const uint32_t val{random_value(0, 100)};
            vec_3.at(index) = val;
            vec_3_c[index] = val;
        }
        vec_3.reserve(vec_3.capacity() - sub);
        test_vector_data(vec_3, exp_data_3);
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            EXPECT_EQ(vec_3.at(index), vec_3_c[index]);
        }

        const uint32_t val_reserve{random_value(size_3 + 1, 50)};
        vec_3.reserve(val_reserve);
        exp_data_3.test_data.data_ptr = vec_3.data();
        exp_data_3._capacity = val_reserve;
        test_vector_data(vec_3, exp_data_3);
        for (uint32_t index = 0; index < vec_3.size(); ++index)
        {
            EXPECT_EQ(vec_3.at(index), vec_3_c[index]);
        }
    }
    // @todo: check capacity < size
    {
    }
}

TEST(test_simple_vector, vec_resize)
{
    // @note: size == 0, new_size == 0
    {
        constexpr uint32_t size_1{0};
        simple_vector<uint32_t> vec_1;
        constexpr test_simple_vector<uint32_t> exp_data_1{true, {0}, 0, size_1};

        vec_1.resize(size_1);
        test_vector_data(vec_1, exp_data_1);
    }
    // @note: size != 0, new_size == 0
    {
        constexpr uint32_t size_2{6};
        simple_vector<uint32_t> vec_2(size_2);
        const test_simple_vector<uint32_t> exp_data_2{
            false, {true, true, vec_2.data()},
             0,
            utils::calculate_capacity(size_2)
        };
        vec_2.resize(0);
        test_vector_data(vec_2, exp_data_2);
    }
    // @note: size != 0. new_size <= capacity
    {
        constexpr uint32_t size_3{7}, sub{2};
        constexpr uint32_t resize_3{size_3 - sub};
        simple_vector<uint32_t> vec_3(size_3);
        const test_simple_vector<uint32_t> exp_data_3{
            false, {0}, resize_3, utils::calculate_capacity(size_3)};

        vec_3.resize(resize_3);
        test_vector_data(vec_3, exp_data_3);
    }
    // @note: size != 0, new_size > capacity
    {
        constexpr uint32_t size_4{8}, add{5};
        constexpr uint32_t resize_4{size_4 + add};
        simple_vector<uint32_t> vec_4(size_4);
        const test_simple_vector<uint32_t> exp_data_4{
            false, {0}, resize_4, utils::calculate_capacity(resize_4)};

        vec_4.resize(resize_4);
        test_vector_data(vec_4, exp_data_4);
    }
}

TEST(test_simple_vector, vec_erase)
{
    // @note: DEATH size == 0, index < size
    {
        constexpr uint32_t amount_1{5};
        simple_vector<uint32_t> vec_1;
        constexpr test_simple_vector<uint32_t> exp_data_1{true, {0}, 0, 0};

        for(uint32_t index = 0; index < amount_1; ++index)
        {
            vec_1.erase(random_value(10, 40));
            test_vector_data(vec_1, exp_data_1);
        }
    }
    // @note: DEATH size != 0, index >= size
    {
        constexpr uint32_t size_2{6}, amount_2{5};
        simple_vector<uint32_t> vec_2{size_2};
        const test_simple_vector<uint32_t> exp_data_2{false, {true, true, vec_2.data()}, size_2, utils::calculate_capacity(size_2)};

        for(uint32_t index = 0; index < amount_2; ++index)
        {
            vec_2.erase(random_value(size_2 + 1, 40));
            test_vector_data(vec_2, exp_data_2);
        }
    }
    // @note: size != 0, index == this->size
    {
        constexpr uint32_t size_3{7};
        simple_vector<uint32_t> vec_3{size_3};
        const test_simple_vector<uint32_t> exp_data_3{false, {true, true, vec_3.data()}, size_3, utils::calculate_capacity(size_3)};

        vec_3.erase(size_3);
        test_vector_data(vec_3, exp_data_3);
    }
    // @note: size != 0, index == size - 1
    {
        constexpr uint32_t size_4{10};
        simple_vector<uint32_t> vec_4{size_4};
        const test_simple_vector<uint32_t> exp_data_4{false, {true, true, vec_4.data()}, size_4 - 1, utils::calculate_capacity(size_4)};

        vec_4.erase(size_4 - 1);
        test_vector_data(vec_4, exp_data_4);
    }
    // @note: size != 0, index < size - 1
    {
        constexpr uint32_t size_5{12};
        simple_vector<uint32_t> vec_5{size_5};
        test_simple_vector<uint32_t> exp_data_5{false, {true, true, vec_5.data()}, size_5, utils::calculate_capacity(size_5)};

        while (vec_5.size() != 0 && exp_data_5._size != 0)
        {
            vec_5.erase(random_value(1, vec_5.size() - 1));
            exp_data_5._size -= 1;
            test_vector_data(vec_5, exp_data_5);
        }
    }
}

TEST(test_simple_vector, vec_clear)
{
    // @note: capacity == 0
    {
        simple_vector<uint32_t> vec_1;
        constexpr test_simple_vector<uint32_t> exp_data_1{true, {0}, 0, 0};
        vec_1.clear();
        test_vector_data(vec_1, exp_data_1);
    }
    // @note: capacity != 0
    {
        constexpr uint32_t size_2{11};
        simple_vector<uint32_t> vec_2{size_2};
        constexpr test_simple_vector<uint32_t> exp_data_2{true, {0}, 0, 0};

        vec_2.clear();
        test_vector_data(vec_2, exp_data_2);
    }
}
