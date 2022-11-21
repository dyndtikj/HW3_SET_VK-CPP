#pragma once

#include "rbt_node.h"

namespace my_rbt {
namespace iterator {

template <typename T>
class ConstIterator {
   protected:
    my_rbt::rb_node::RBNode<T> *ptr_;

   public:
    typedef T key_type;
    typedef T &key_ref;
    typedef const T &const_key_ref;
    typedef T *key_ptr;

    ConstIterator();
    explicit ConstIterator(my_rbt::rb_node::RBNode<T> *ptr);
    ConstIterator(const ConstIterator &s);

    ConstIterator &operator=(const ConstIterator &other);

    my_rbt::rb_node::RBNode<T> *getPtr();

    // Bidirectional
    ConstIterator operator++();
    const ConstIterator operator++(int);
    ConstIterator operator--();
    const ConstIterator operator--(int);

    bool operator==(const ConstIterator &other) const;
    bool operator!=(const ConstIterator &other) const;

    T const &operator*() const;
    key_ptr operator->() const;
    explicit operator bool() const;
};

template <typename T>
ConstIterator<T>::ConstIterator() : ptr_{nullptr} {}

template <typename T>
ConstIterator<T>::ConstIterator(my_rbt::rb_node::RBNode<T> *ptr) : ptr_{ptr} {}

template <typename T>
ConstIterator<T>::ConstIterator(const ConstIterator &s) : ptr_{s.ptr_} {}

template <typename T>
my_rbt::rb_node::RBNode<T> *ConstIterator<T>::getPtr() {
    return ptr_;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator &other) {
    if (this != &other) {
        this->ptr_ = other.ptr_;
    }
    return (*this);
}

template <typename T>
bool ConstIterator<T>::operator==(const ConstIterator &other) const {
    return (ptr_ == other.ptr_);
}

template <typename T>
bool ConstIterator<T>::operator!=(const ConstIterator &other) const {
    return (ptr_ != other.ptr_);
}

template <typename T>
T const &ConstIterator<T>::operator*() const {
    return (ptr_->key_);
}

template <typename T>
typename ConstIterator<T>::key_ptr ConstIterator<T>::operator->() const {
    return reinterpret_cast<key_ptr>(std::addressof(ptr_->key_));
}

template <typename T>
ConstIterator<T>::operator bool() const {
    return (ptr_ != nullptr);
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++() {
    this->ptr_ = this->ptr_->getNext();
    return *this;
}

template <typename T>
const ConstIterator<T> ConstIterator<T>::operator++(int) {
    ConstIterator tmp(*this);
    this->ptr_ = this->ptr_->getNext();
    return tmp;
}

template <typename T>
const ConstIterator<T> ConstIterator<T>::operator--(int) {
    ConstIterator tmp(*this);
    this->ptr_ = this->ptr_->getPrev();
    return tmp;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--() {
    ptr_ -= 1;
    this->ptr_ = this->ptr_->getPrev();
    return *this;
}
}  // namespace iterator
}  // namespace my_rbt
