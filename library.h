#pragma once

#include <compare>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <algorithm>

class Vector {
public:
    using ValueType = int;
    using SizeType = size_t;
    using DifferenceType = ptrdiff_t;

    class Iterator {
    public:
        explicit Iterator(ValueType* pointer) {
            it_ = pointer;
        }
        Iterator() {
            it_ = nullptr;
        }

        ValueType& operator*() const;
        ValueType* operator->() const;

        Iterator& operator=(Iterator other);

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        Iterator operator+(DifferenceType shift);
        DifferenceType operator-(Iterator other);
        Iterator& operator+=(DifferenceType shift);
        Iterator& operator-=(DifferenceType shift);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        std::strong_ordering operator<=>(const Iterator& other) const;

    private:
        ValueType* it_;
    };

    Vector() {
        begin_it_ = Iterator();
        end_it_ = Iterator();
        sz_ = 0;
        cap_ = 0;
        val_ = new int[0];
    }
    explicit Vector(size_t size) {
        val_ = new int[size];
        sz_ = size;
        cap_ = size;
        begin_it_ = Iterator(&val_[0]);
        for (size_t i = 0; i < sz_; ++i) {
            val_[i] = 0;
        }
        end_it_ = begin_it_ + sz_;
    }
    Vector(std::initializer_list<ValueType> list) {
        val_ = new int[list.size()];
        sz_ = list.size();
        cap_ = list.size();
        int ind = 0;
        for (const auto& i : list) {
            val_[ind++] = i;
        }
        begin_it_ = Iterator(&val_[0]);
        end_it_ = begin_it_ + sz_;
    }
    Vector(const Vector& other) {
        sz_ = other.sz_;
        cap_ = other.cap_;
        val_ = other.val_;
        begin_it_ = other.begin_it_;
        end_it_ = other.end_it_;
    }
    Vector& operator=(const Vector& other);

    ~Vector() {
        delete[](val_);
        sz_ = 0;
        cap_ = 0;
        begin_it_ = Iterator();
        end_it_ = Iterator();
    }

    SizeType Size() const;
    SizeType Capacity() const;

    const ValueType* Data() const;

    ValueType& operator[](size_t position);
    ValueType operator[](size_t position) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    std::strong_ordering operator<=>(const Vector& other) const;

    void Reserve(SizeType new_capacity);
    void Clear();

    void PushBack(const ValueType& new_element);
    void PopBack();

    void Swap(Vector& other);

    Iterator Begin();
    Iterator End();

    Iterator begin() {  // NOLINT
        return begin_it_;
    }
    Iterator end() {  //   NOLINT
        return end_it_;
    }

private:
    Iterator begin_it_;
    Iterator end_it_;
    size_t sz_ = 0;
    size_t cap_ = 0;
    int* val_;
};
