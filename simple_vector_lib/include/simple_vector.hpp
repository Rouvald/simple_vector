#ifndef _SIMPLE_VECTOR_HPP_
#define _SIMPLE_VECTOR_HPP_

#include <cstdint>
#include <cassert>
#include <algorithm>

#include "utils.hpp"

// @todo
#include <iostream>

template <class T>
class simple_vector
{
public:
    simple_vector();
    // @todo: create ctor like vector () - some elems , {} - 1 elen with value
    explicit simple_vector(const uint32_t& new_size);
    simple_vector(const simple_vector& new_vec);
    simple_vector(simple_vector&& new_vec) noexcept;

    simple_vector& operator=(const simple_vector& rhs);
    simple_vector& operator=(simple_vector&& rhs) noexcept;

    ~simple_vector();

    // getters
    const T* data() const { return this->_data; }
    [[nodiscard]] const uint32_t& size() const { return this->_size; }
    [[nodiscard]] const uint32_t& capacity() const { return this->_capacity; }

    T* data() { return this->_data; }
    uint32_t& size() { return this->_size; }
    uint32_t& capacity() { return this->_capacity; }

    T& at(const uint32_t& index);
    const T& at(const uint32_t& index) const;
    const T& front() const;
    const T& back() const;

    [[nodiscard]] bool is_empty() const { return this->_size == 0; };
    void reserve(const uint32_t& _capacity);
    void resize(const uint32_t& _size);

    void push_back(const T& value);
    // void emplace_back(const T& value);  // @todo: find diff in real vector
    void pop_back();

    void erase(const uint32_t& index);
    void clear();

private:
    T* _data{nullptr};
    uint32_t _size{0};
    uint32_t _capacity{0};

    [[nodiscard]] uint32_t calculate_capacity(const uint32_t& new_size);
    void create_new_data(const uint32_t& new_capacity);
    void clear_data();
    void zeroing_data(const uint32_t& start, const uint32_t& end);
};

/******************************************************************************
                                IMPLEMENTATION
*******************************************************************************/

template <class T>
simple_vector<T>::simple_vector() : _data{nullptr}, _size{0}, _capacity{0}
{
}

template <class T>
simple_vector<T>::simple_vector(const uint32_t& new_size)
    : _size{new_size},  //
      _capacity{new_size}  //
{
    if (new_size == 0)
    {
        simple_vector();
        return;
    }
    this->_data = new T[calculate_capacity(new_size)]{0};
    std::fill_n(this->_data, new_size, T{0});
}

// copy ctor
template <class T>
simple_vector<T>::simple_vector(const simple_vector<T>& new_vec)
    : _size{new_vec._size},  //
      _capacity{new_vec._capacity}  //
{
    std::cout << "TEMP: copy ctor" << std::endl;
    if (new_vec._capacity == 0 || new_vec._data == nullptr)
    {
        this->~simple_vector();
        return;
    }
    this->_data = new T[new_vec.capacity()]{0};
    std::copy_n(new_vec._data, new_vec._size, this->_data);
}

// move ctor
template <class T>
simple_vector<T>::simple_vector(simple_vector<T>&& new_vec) noexcept
    : _data{new_vec._data},  //
      _size{new_vec._size},  //
      _capacity{new_vec._capacity}  //
{
    std::cout << "TEMP: move constructor" << std::endl;
    if (new_vec._capacity == 0)
    {
        simple_vector();
    }
    new_vec.clear_data();
}

// copy assign
template <class T>
simple_vector<T>& simple_vector<T>::operator=(const simple_vector<T>& rhs)
{
    std::cout << "TEMP: copy assignment" << std::endl;
    if (rhs._capacity == 0 || rhs._data == nullptr)
    {
        this->~simple_vector();
        return *this;
    }
    if (this == &rhs)
    {
        return *this;
    }
    if (this->_capacity >= rhs._size)
    {
        std::copy_n(rhs._data, rhs._size, this->_data);
        this->_size = rhs._size;
        return *this;
    }
    T* new_arr = new T[rhs._capacity]{0};
    std::copy_n(rhs._data, rhs._size, new_arr);
    delete[] this->_data;
    this->_data = new_arr;
    this->_size = rhs._size;
    this->_capacity = rhs._capacity;
    return *this;
}

// move assign
template <class T>
simple_vector<T>& simple_vector<T>::operator=(simple_vector<T>&& rhs) noexcept
{
    std::cout << "TEMP: move assign" << std::endl;
    if (this == &rhs)
    {
        return *this;
    }
    delete[] this->_data;
    this->_data = rhs._data;
    this->_size = rhs._size;
    this->_capacity = rhs._capacity;

    rhs.clear_data();

    return *this;
}

template <class T>
simple_vector<T>::~simple_vector()
{
    delete[] this->_data;
    this->_data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

// methods

template <class T>
T& simple_vector<T>::at(const uint32_t& index)
{
    assert(utils::assert_with_msg(0 != this->_size && index < this->_size,
        "ERROR: incorrect size OR index"));
    return this->_data[index];
}

template <class T>
const T& simple_vector<T>::at(const uint32_t& index) const
{
    assert(utils::assert_with_msg(0 != this->_size && index < this->_size,
        "ERROR: incorrect size OR index"));
    return this->_data[index];
}

template <class T>
const T& simple_vector<T>::front() const
{
    assert(utils::assert_with_msg(0 != this->_size, "ERROR: incorrect size"));
    return this->_data[0];
}

template <class T>
const T& simple_vector<T>::back() const
{
    assert(utils::assert_with_msg(0 != this->_size, "ERROR: incorrect size"));
    return this->_data[this->_size - 1];
}

template <class T>
void simple_vector<T>::reserve(const uint32_t& new_capacity)
{
    if (new_capacity <= this->_capacity || new_capacity == 0)
    {
        return;
    }
    this->create_new_data(new_capacity);
}

template <class T>
void simple_vector<T>::resize(const uint32_t& new_size)
{
    if (this->_size < new_size && new_size < this->_capacity)
    {
        zeroing_data(this->_size, new_size);
    }
    if (new_size > this->_capacity)
    {
        this->create_new_data(calculate_capacity(new_size));
    }
    this->_size = new_size;
}

template <class T>
void simple_vector<T>::push_back(const T& value)
{
    if (this->_size < this->_capacity)
    {
        this->_data[this->_size] = value;
        ++this->_size;
        return;
    }
    this->resize(this->_size + 1);
    // @note: after resize, size == prev_size + 1
    // @todo: think about change -> "this->_size - 1"
    this->_data[this->_size - 1] = value;
}

template <class T>
void simple_vector<T>::pop_back()
{
    if (this->_size == 0)
    {
        return;
    }
    --this->_size;
}

template <class T>
void simple_vector<T>::erase(const uint32_t& index)
{
    if (this->_size == 0 || index >= this->_size)
    {
        return;
    }

    if (index < (this->_size - 1))
    {
        for (uint32_t index_for = index; index_for < this->_size; ++index_for)
        {
            this->_data[index_for] = this->_data[index_for + 1];
        }
    }
    resize(--this->_size);
}

template <class T>
void simple_vector<T>::clear()
{
    if (this->_capacity == 0 || this->_size == 0)
    {
        return;
    }
    this->_size = 0;
}

// private methods

template <class T>
uint32_t simple_vector<T>::calculate_capacity(const uint32_t& new_size)
{
    return (new_size > this->_capacity) ? new_size : this->_capacity * 2;
}

template <class T>
void simple_vector<T>::create_new_data(const uint32_t& new_capacity)
{
    if (new_capacity == 0)
    {
        return;
    }
    T* new_arr = new T[new_capacity]{0};
    std::copy_n(this->_data, this->_size, new_arr);
    delete[] this->_data;
    this->_data = new_arr;
    this->_capacity = new_capacity;
}

template <class T>
void simple_vector<T>::clear_data()
{
    this->_data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

template <class T>
void simple_vector<T>::zeroing_data(const uint32_t& start, const uint32_t& end)
{
    if (start > end || start > this->_capacity || end > this->_capacity)
    {
        return;
    }

    for (uint32_t index = start; index < end; ++index)
    {
        this->_data[index] = 0;
    }
}

#endif  // _SIMPLE_VECTOR_HPP_