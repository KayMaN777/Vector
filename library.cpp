#include "library.h"

Vector::ValueType& Vector::Iterator::operator*() const {
    return *it_;
}
Vector::ValueType* Vector::Iterator::operator->() const {
    return it_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    it_ = other.it_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++it_;
    return reinterpret_cast<Iterator&>(it_);
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++it_;
    return tmp;
}
Vector::Iterator& Vector::Iterator::operator--() {
    --it_;
    return reinterpret_cast<Iterator&>(it_);
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator tmp = *this;
    --it_;
    return tmp;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    return Iterator(it_ + shift);
}
Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return it_ - other.it_;
}
Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    it_ += shift;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    it_ -= shift;
    return *this;
}
bool Vector::Iterator::operator==(const Iterator& other) const {
    return it_ == other.it_;
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}
std::strong_ordering Vector::Iterator::operator<=>(const Iterator& other) const {
    if (it_ < other.it_) {
        return std::strong_ordering::less;
    } else if (it_ == other.it_) {
        return std::strong_ordering::equal;
    } else {
        return std::strong_ordering::greater;
    }
}
Vector& Vector::operator=(const Vector& other) {
    sz_ = other.sz_;
    cap_ = other.cap_;
    val_ = other.val_;
    begin_it_ = other.begin_it_;
    end_it_ = other.end_it_;
    return *this;
}

Vector::SizeType Vector::Size() const {
    return sz_;
}
Vector::SizeType Vector::Capacity() const {
    return cap_;
}

const Vector::ValueType* Vector::Data() const {
    return val_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return val_[position];
}
Vector::ValueType Vector::operator[](size_t position) const {
    return val_[position];
}

bool Vector::operator==(const Vector& other) const {
    if (sz_ != other.sz_) {
        return false;
    } else if (cap_ != other.cap_) {
        return false;
    } else {
        for (size_t i = 0; i < sz_; ++i) {
            if (val_[i] != other.val_[i]) {
                return false;
            }
        }
        return true;
    }
}
bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}
std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < std::min(sz_, other.sz_); ++i) {
        if (val_[i] < other.val_[i]) {
            return std::strong_ordering::less;
        } else if (val_[i] > other.val_[i]) {
            return std::strong_ordering::greater;
        }
    }
    if (sz_ < other.sz_) {
        return std::strong_ordering::less;
    } else if (sz_ > other.sz_) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::equal;
    }
}

void Vector::Reserve(SizeType new_capacity) {
    if (cap_ >= new_capacity) {
        return;
    }
    int* val = new int[new_capacity];
    for (size_t i = 0; i < sz_; ++i) {
        val[i] = val_[i];
    }
    cap_ = new_capacity;
    delete[](val_);
    val_ = val;
    begin_it_ = Iterator(&val_[0]);
    end_it_ = begin_it_ + sz_;
}
void Vector::Clear() {
    sz_ = 0;
    end_it_ = begin_it_;
}

void Vector::PushBack(const ValueType& new_element) {
    if (sz_ == cap_) {
        if (cap_ == 0) {
            cap_ = 1;
        } else {
            cap_ *= 2;
        }
        int* val = new int[cap_];
        for (size_t i = 0; i < sz_; ++i) {
            val[i] = val_[i];
        }
        val[sz_] = new_element;
        delete[](val_);
        val_ = val;
        ++sz_;
        begin_it_ = Iterator(&val_[0]);
        end_it_ = begin_it_ + sz_;
    } else {
        ++end_it_;
        val_[sz_] = new_element;
        ++sz_;
    }
}
void Vector::PopBack() {
    if (sz_) {
        --sz_;
        --end_it_;
    }
}

void Vector::Swap(Vector& other) {
    std::swap(sz_, other.sz_);
    std::swap(cap_, other.cap_);
    std::swap(val_, other.val_);
    std::swap(begin_it_, other.begin_it_);
    std::swap(end_it_, other.end_it_);
}

Vector::Iterator Vector::Begin() {
    return begin();
}
Vector::Iterator Vector::End() {
    return end();
}

