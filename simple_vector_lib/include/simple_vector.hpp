#ifndef _SIMPLE_VECTOR_HPP_
#define _SIMPLE_VECTOR_HPP_

#include <cstdint>
#include <cassert>

#include "utils.hpp"

// @todo
#include <iostream>

template <class T>
class simple_vector
{
public:
    simple_vector();
    // @todo: create ctor like vector () - some elems , {} - 1 elen with value
    simple_vector(const uint32_t& new_size);
    simple_vector(const simple_vector<T>& new_data);

    simple_vector<T>& operator=(const simple_vector<T>& arg);

    ~simple_vector();

    // getters
    inline const T* data() const { return this->_data; }
    inline const uint32_t& size() const { return this->_size; }
    inline const uint32_t& capacity() const { return this->_capacity; }

    inline T* data() { return this->_data; }
    inline uint32_t& size() { return this->_size; }
    inline uint32_t& capacity() { return this->_capacity; }

    inline T& at(const uint32_t& index);
    inline const T& at(const uint32_t& index) const;
    const T& front() const;
    const T& back() const;

    inline bool is_empty() const;
    void reserve(const uint32_t& _capacity);
    void resize(const uint32_t& _size);

    void erase(const uint32_t& index);
    void clear();

private:
    T* _data{nullptr};
    uint32_t _size{0};
    uint32_t _capacity{0};

    // setters
    // inline void set_data(const simple_vector<T>& new_data)
    // {
    //     this->_data = new_data;
    // }
    // inline void set_size(const uint32_t& new_size) { this->_size = new_size;
    // } inline void set_capacity(const uint32_t& new_capacity)
    // {
    //     this->_capacity = new_capacity;
    // }
    void create_new_data(const uint32_t& new_capacity);
    void clear_data();
    void zeroing_data(const uint32_t& start, const uint32_t& end);
};

/******************************************************************************
                                IMPLEMENTATION
*******************************************************************************/

template <class T>
simple_vector<T>::simple_vector()
{
    this->_data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

template <class T>
simple_vector<T>::simple_vector(const uint32_t& new_size)
{
    if (new_size == 0)
    {
        simple_vector();
        return;
    }

    this->_size = new_size;
    this->_capacity = utils::calculate_capacity(new_size);

    this->_data = new T[this->_capacity]{0};

    for (uint32_t index = 0; index < new_size; ++index)
    {
        this->_data[index] = T{0};
    }
}

template <class T>
simple_vector<T>::simple_vector(const simple_vector<T>& new_data)
{
    if (new_data.capacity() == 0)
    {
        simple_vector();
        return;
    }

    this->_size = new_data.size();
    this->_capacity = new_data.capacity();

    this->_data = new T[new_data.capacity()]{0};

    for (uint32_t index = 0; index < new_data.size(); ++index)
    {
        this->_data[index] = new_data.data()[index];
    }
}

template <class T>
simple_vector<T>& simple_vector<T>::operator=(const simple_vector<T>& rhs)
{
    if (rhs.size() == 0)
        return *this;

    if (this == &rhs)
        return *this;

    if (this->_capacity >= rhs.size())
    {
        for (uint32_t index = 0; index < rhs.size(); ++index)
        {
            this->_data[index] = rhs.data()[index];
        }
        this->_size = rhs.size();
        return *this;
    }
    T* new_arr = new T[rhs.capacity()]{0};

    for (uint32_t index = 0; index < rhs.size(); ++index)
    {
        new_arr[index] = rhs.data()[index];
    }
    delete[] this->_data;
    this->_data = new_arr;
    this->_size = rhs.size();
    this->_capacity = rhs.capacity();
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
inline bool simple_vector<T>::is_empty() const
{
    return this->_size == 0;
}

template <class T>
void simple_vector<T>::reserve(const uint32_t& new_capacity)
{
    if (new_capacity <= this->_capacity)
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
        this->create_new_data(utils::calculate_capacity(new_size));
    }
    this->_size = new_size;
}

template <class T>
void simple_vector<T>::erase(const uint32_t& index)
{
    assert(utils::assert_with_msg(0 != this->_size && index < this->_size,
        "ERROR: incorrect size OR index"));

    if (index <= (this->_size - 1))
    {
        for (uint32_t index_for = index; index_for < this->_size; ++index_for)
        {
            this->_data[index_for] = this->_data[index_for + 1];
        }
        --this->_size;
    }
    resize(this->_size);
}

template <class T>
void simple_vector<T>::clear()
{
    assert(utils::assert_with_msg(0 != this->_size, "ERROR: incorrect size"));

    clear_data();
}

// private methods

template <class T>
void simple_vector<T>::create_new_data(const uint32_t& new_capacity)
{
    if (new_capacity == 0)
    {
        clear_data();
        return;
    }
    T* new_arr = new T[new_capacity]{0};

    for (uint32_t index = 0; index < this->_size; ++index)
    {
        new_arr[index] = this->_data[index];
    }
    delete[] this->_data;
    this->_data = new_arr;
    this->_capacity = new_capacity;
}

template <class T>
void simple_vector<T>::clear_data()
{
    delete[] this->_data;
    this->_data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

template <class T>
void simple_vector<T>::zeroing_data(const uint32_t& start, const uint32_t& end)
{
    assert(utils::assert_with_msg(start < end && 0 < start &&
                                      start <= this->_capacity && 0 < end &&
                                      end <= this->_capacity,
        "ERROR: incorrect size"));

    for (uint32_t index = start; index < end; ++index)
    {
        this->_data[index] = 0;
    }
}

#endif  // _SIMPLE_VECTOR_HPP_