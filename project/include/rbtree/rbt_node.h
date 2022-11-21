#pragma once

#include <exception>
#include <iostream>
#include <iterator>
#include <utility>

namespace my_rbt {
namespace rb_node {
enum colors { RED, BLACK };

template <typename T>
class RBNode {
   public:
    typedef T key_type;
    typedef T &key_ref;
    typedef const T &const_key_ref;
    typedef RBNode<T> node_type;
    typedef RBNode<T> *node_ptr;
    typedef RBNode<T> &node_ref;
    typedef const RBNode<T> &const_node_ref;

    key_type key_;
    node_ptr parent_;
    node_ptr left_;
    node_ptr right_;
    int color_;

    RBNode();
    explicit RBNode(key_type key);
    RBNode(const_node_ref other);

    ~RBNode() = default;

    node_ref operator=(const_key_ref key);
    node_ref operator=(const_node_ref other);

    node_ptr getMax();
    node_ptr getMin();
    node_ptr getNext();
    node_ptr getPrev();
};

template <typename T>
RBNode<T>::RBNode(key_type key)
    : key_{key},
      parent_{nullptr},
      left_{nullptr},
      right_{nullptr},
      color_{RED} {}

template <typename T>
RBNode<T>::RBNode(const RBNode<T> &other)
    : key_{other.key},
      parent_{other.parent_},
      left_{other.left},
      right_{other.right},
      color_{other.color} {}

template <typename T>
RBNode<T>::RBNode()
    : parent_{nullptr}, left_{nullptr}, right_{nullptr}, color_{BLACK} {}

template <typename T>
RBNode<T> &RBNode<T>::operator=(const_key_ref key) {
    key_ = key;
    return *this;
}

template <typename T>
typename RBNode<T>::node_ptr RBNode<T>::getMax() {
    return ((right_ == nullptr) ? this : right_->getMax());
}

template <typename T>
typename RBNode<T>::node_ptr RBNode<T>::getMin() {
    return ((left_ == nullptr) ? this : left_->getMin());
}

template <typename T>
typename RBNode<T>::node_ref RBNode<T>::operator=(const_node_ref other) {
    if (this == &other) return *this;
    try {
        parent_ = new RBNode(*other.parent_);
        left_ = new RBNode(*other.left);
        right_ = new RBNode(*other.right);
    } catch (...) {
        delete parent_;
        delete left_;
        delete right_;
        throw std::bad_alloc();
    }

    key_ = other.key;
    return *this;
}

template <typename T>
typename RBNode<T>::node_ptr RBNode<T>::getNext() {
    RBNode<T> *x = this;
    if (x->right_ != nullptr) {
        return x->right_->getMin();
    }

    RBNode<T> *root = x;
    while (root->parent_ != nullptr) {
        root = root->parent_;
    }

    RBNode<T> *right = root->getMax();
    if (x == right) {
        return right + 1;
    }

    while (x != x->parent_->left_) {
        x = x->parent_;
    }
    return x->parent_;
}

template <typename T>
typename RBNode<T>::node_ptr RBNode<T>::getPrev() {

    RBNode<T> *x = this;
    if (x->left_ != nullptr) {
        return x->left_->getMax();
    }

    RBNode<T> *root = x;
    while (root->parent_ != nullptr) root = root->parent_;

    RBNode<T> *lleft = root->getMin();

    if (x == lleft) return lleft - 1;

    while (x != x->parent_->right_) x = x->parent_;
    return x->parent_;
}
}  // namespace rb_node
}  // namespace my_rbt
