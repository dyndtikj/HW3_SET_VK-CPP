#pragma once

#include <initializer_list>
#include <vector>

#include "rbt_const_iterator.h"

namespace my_rbt {

template <typename T>
class RBTree {
   public:
    typedef T key_type;
    typedef T& key_ref;
    typedef const T& const_key_ref;
    typedef my_rbt::rb_node::RBNode<T> node_type;
    typedef my_rbt::rb_node::RBNode<T>* node_ptr;
    typedef my_rbt::iterator::ConstIterator<T> iterator;

   private:
    size_t Size(node_ptr);
    void RotateLeft(node_ptr);
    void RotateRight(node_ptr);
    void FixInsert(node_ptr);
    void FixRemove(node_ptr);
    void DeleteNodes(node_ptr);
    void Copy(node_ptr);
    void DropNode(node_ptr);

   public:
    RBTree();
    RBTree(std::initializer_list<T>);
    template <typename Iterator>
    RBTree(Iterator, Iterator);
    ~RBTree();
    RBTree& operator=(const RBTree<T>&);
    RBTree& operator=(const std::initializer_list<T>&);

    node_ptr GetRoot() const;
    iterator Root();
    size_t GetSize() const;
    [[nodiscard]] bool IsEmpty() const;

    void Clear();
    node_ptr MaxNode() const;
    iterator MaxIter();
    node_ptr MinNode() const;
    iterator MinIter();
    iterator Insert(const_key_ref);
    void Insert(iterator first, iterator last);
    std::pair<iterator, bool> InsertUnique(const_key_ref&);
    bool Find(const_key_ref);

    explicit operator bool() const;
    iterator begin() const noexcept;
    iterator end() const noexcept;

    iterator IterateTo(const_key_ref) const;
    node_ptr FindNode(const_key_ref) const;
    bool Remove(const_key_ref);
    iterator Erase(iterator pos);
    iterator Erase(iterator first, iterator last);
    std::size_t Erase(const_key_ref);
    iterator LowerBound(const_key_ref) const;

    friend std::ostream& operator<<(std::ostream& os, const RBTree<T>& tree) {
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            os << *it << ", ";
        }
        os << std::endl;
        return os;
    }

   private:
    size_t size_;
    node_ptr root_;
};

template <typename T>
RBTree<T>::RBTree() : size_{0}, root_{nullptr} {}

template <typename T>
RBTree<T>::RBTree(std::initializer_list<T> init) : size_{0} {
    for (auto& e : init) {
        Insert(e);
    }
}

template <typename T>
template <typename Iterator>
RBTree<T>::RBTree(Iterator first, Iterator last) : size_{0} {
    for (auto it = first; it != last; it++) {
        Insert(*it);
    }
}

template <typename T>
void RBTree<T>::Copy(RBTree::node_ptr in) {
    if (in) {
        Insert(in->key_);
        Copy(in->left_);
        Copy(in->right_);
    }
}

template <typename T>
void RBTree<T>::DropNode(node_ptr n) {
    n->~RBNode();
}

template <typename T>
RBTree<T>::~RBTree() {
    Clear();
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& tree) {
    if (this != &tree) {
        DeleteNodes(root_);
        root_ = nullptr;
        Copy(tree.root_);
    }

    return *this;
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const std::initializer_list<T>& init) {
    DeleteNodes(root_);
    root_ = nullptr;
    for (auto& e : init) {
        Insert(e);
    }
    return *this;
}

template <typename T>
typename RBTree<T>::node_ptr RBTree<T>::GetRoot() const {
    return root_;
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::Root() {
    return iterator(root_);
}

template <typename T>
size_t RBTree<T>::GetSize() const {
    return size_;
}

template <typename T>
[[nodiscard]] bool RBTree<T>::IsEmpty() const {
    return (root_ == nullptr && size_ == 0);
}

template <typename T>
void RBTree<T>::Clear() {
    DeleteNodes(root_);
    root_ = nullptr;
}

template <typename T>
typename RBTree<T>::node_ptr RBTree<T>::MaxNode() const {
    return (IsEmpty() ? nullptr : root_->getMax());
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::MaxIter() {
    return iterator(MaxNode());
}

template <typename T>
typename RBTree<T>::node_ptr RBTree<T>::MinNode() const {
    return (IsEmpty() ? nullptr : root_->getMin());
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::MinIter() {
    return iterator(MinNode());
}

template <typename T>
void RBTree<T>::DeleteNodes(node_ptr in) {
    if (in) {
        while (in != 0) {
            DeleteNodes(in->right_);
            node_ptr y = in->left_;
            DropNode(in);
            in = y;
            size_--;
        }
    }
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::Insert(const_key_ref input) {
    node_ptr q;
    auto* create = new my_rbt::rb_node::RBNode<T>(input);
    auto p = root_;
    q = nullptr;

    if (root_ == nullptr) {
        root_ = create;
        create->parent_ = nullptr;
    } else {
        while (p != nullptr) {
            q = p;
            if (!(p->key_ < create->key_) && (create->key_ < p->key_))
                p = p->left_;
            else if (p->key_ < create->key_)
                p = p->right_;
            else
                return end();
        }

        create->parent_ = q;

        if (q->key_ < create->key_)
            q->right_ = create;
        else if (!(q->key_ < create->key_) && (create->key_ < q->key_))
            q->left_ = create;
        else
            return end();
    }

    size_++;
    FixInsert(create);
    return IterateTo(input);
}

template <typename T>
void RBTree<T>::FixInsert(node_ptr create) {
    auto* x = create;

    while (x != root_ && x->parent_->color_ == my_rbt::rb_node::RED) {
        if (x->parent_ == x->parent_->parent_->left_) {
            auto* y = x->parent_->parent_->right_;

            if ((y != nullptr) && (y->color_ == my_rbt::rb_node::RED)) {
                x->parent_->color_ = my_rbt::rb_node::BLACK;
                y->color_ = my_rbt::rb_node::BLACK;
                x->parent_->parent_->color_ = my_rbt::rb_node::RED;
                x = x->parent_->parent_;
            } else {
                if (x->parent_->right_ == x) {
                    x = x->parent_;
                    RotateLeft(x);
                }

                x->parent_->color_ = my_rbt::rb_node::BLACK;
                x->parent_->parent_->color_ = my_rbt::rb_node::RED;
                RotateRight(x->parent_->parent_);
            }
        } else {
            auto* y = x->parent_->parent_->left_;

            if ((y != nullptr) && (y->color_ == my_rbt::rb_node::RED)) {
                x->parent_->color_ = my_rbt::rb_node::BLACK;
                y->color_ = my_rbt::rb_node::BLACK;
                x->parent_->parent_->color_ = my_rbt::rb_node::RED;
                x = x->parent_->parent_;
            } else {
                if (x->parent_->left_ == x) {
                    x = x->parent_;
                    RotateRight(x);
                }

                x->parent_->color_ = my_rbt::rb_node::BLACK;
                x->parent_->parent_->color_ = my_rbt::rb_node::RED;
                RotateLeft(x->parent_->parent_);
            }
        }
    }

    root_->color_ = my_rbt::rb_node::BLACK;
}

template <typename T>
void RBTree<T>::RotateRight(node_ptr in) {
    if (in->left_ == nullptr)
        return;
    else {
        auto* x = in->left_;
        auto* b = x->right_;
        auto* f = in->parent_;

        if (f == nullptr) {
            x->parent_ = nullptr;
            root_ = x;
        } else {
            x->parent_ = f;

            if (f->left_ == in) f->left_ = x;
            if (f->right_ == in) f->right_ = x;
        }

        x->right_ = in;
        in->parent_ = x;
        in->left_ = b;

        if (b != nullptr) b->parent_ = in;
    }
}

template <typename T>
void RBTree<T>::RotateLeft(node_ptr x) {
    if (x->right_ == nullptr)
        return;
    else {
        auto* y = x->right_;
        auto* b = y->left_;
        auto* f = x->parent_;

        if (f == nullptr) {
            y->parent_ = nullptr;
            root_ = y;
        } else {
            y->parent_ = f;

            if (f->left_ == x) f->left_ = y;
            if (f->right_ == x) f->right_ = y;
        }

        y->left_ = x;
        x->parent_ = y;
        x->right_ = b;

        if (b != nullptr) b->parent_ = x;
    }
}

template <typename T>
bool RBTree<T>::Find(const_key_ref in) {
    auto* t = root_;

    while (t != nullptr) {
        if (t->key_ == in) return true;
        if (in > t->key_)
            t = t->right_;
        else if (in < t->key_)
            t = t->left_;
    }

    return false;
}
template <typename T>
RBTree<T>::operator bool() const {
    return !IsEmpty();
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::begin() const noexcept {
    return iterator(MinNode());
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::end() const noexcept {
    if (!root_) return iterator();
    auto tmp = root_;
    while (tmp->right_ != nullptr) tmp = tmp->right_;

    return iterator(tmp + 1);
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::IterateTo(const_key_ref x) const {
    return iterator(FindNode(x));
}

template <typename T>
typename RBTree<T>::node_ptr RBTree<T>::FindNode(const_key_ref in) const {
    auto* t = root_;

    while (t != nullptr) {
        if ((!(t->key_ < in)) && !(in < t->key_)) return t;
        if (!(in < t->key_) && (t->key_ < in))
            t = t->right_;
        else if (in < t->key_)
            t = t->left_;
    }

    return nullptr;
}

template <typename T>
size_t RBTree<T>::Size(node_ptr in) {
    if (in == nullptr)
        return 0;
    else {
        auto ls = Size(in->left_);
        auto rs = Size(in->right_);

        return (ls + rs + 1);
    }
}

template <typename T>
bool RBTree<T>::Remove(const_key_ref x) {
    if (root_ == nullptr) {
        std::cout << "Tree is Empty\n";
        return false;
    }

    auto* p = root_;
    auto found = 0;

    while (p != nullptr && found == 0) {
        if (p->key_ == x) found = 1;
        if (found == 0) {
            if (p->key_ < x)
                p = p->right_;
            else
                p = p->left_;
        }
    }

    if (found == 0)
        return false;
    else {
        node_ptr q, y;

        if (p->left_ == nullptr || p->right_ == nullptr)
            y = p;
        else
            y = p->getNext();

        if (y->left_ != nullptr)
            q = y->left_;
        else {
            if (y->right_ != nullptr)
                q = y->right_;
            else
                q = nullptr;
        }

        if (q != nullptr) q->parent_ = y->parent_;

        if (y->parent_ == nullptr)
            root_ = q;
        else {
            if (y == y->parent_->left_)
                y->parent_->left_ = q;
            else
                y->parent_->right_ = q;
        }

        if (y != p) {
            p->color_ = y->color_;
            p->key_ = y->key_;
        }

        if (y->color_ == my_rbt::rb_node::BLACK) FixRemove(q);

        size_--;
        return true;
    }
}

template <typename T>
void RBTree<T>::FixRemove(node_ptr p) {
    if (p != nullptr) {
        node_ptr s;

        while (p != root_ && p->color_ == my_rbt::rb_node::BLACK) {
            if (p->parent_->left_ == p) {
                s = p->parent_->right_;

                if (s->color_ == my_rbt::rb_node::RED) {
                    s->color_ = my_rbt::rb_node::BLACK;
                    p->parent_->color_ = my_rbt::rb_node::RED;
                    RotateLeft(p->parent_);
                    s = p->parent_->right_;
                }
                if (s->right_->color_ == my_rbt::rb_node::BLACK &&
                    s->left_->color_ == my_rbt::rb_node::BLACK) {
                    s->color_ = my_rbt::rb_node::RED;
                    p = p->parent_;
                } else {
                    if (s->right_->color_ == my_rbt::rb_node::BLACK) {
                        s->left_->color_ = my_rbt::rb_node::BLACK;
                        s->color_ = my_rbt::rb_node::RED;
                        RotateRight(s);
                        s = p->parent_->right_;
                    }

                    s->color_ = p->parent_->color_;
                    p->parent_->color_ = my_rbt::rb_node::BLACK;
                    s->right_->color_ = my_rbt::rb_node::BLACK;
                    RotateLeft(p->parent_);
                    p = root_;
                }
            } else {
                s = p->parent_->left_;

                if (s->color_ == my_rbt::rb_node::RED) {
                    s->color_ = my_rbt::rb_node::RED;
                    p->parent_->color_ = my_rbt::rb_node::RED;
                    RotateRight(p->parent_);
                    s = p->parent_->left_;
                }
                if (s->left_->color_ == my_rbt::rb_node::BLACK &&
                    s->right_->color_ == my_rbt::rb_node::BLACK) {
                    s->color_ = my_rbt::rb_node::RED;
                    p = p->parent_;
                } else {
                    if (s->left_->color_ == my_rbt::rb_node::BLACK) {
                        s->right_->color_ = my_rbt::rb_node::BLACK;
                        s->color_ = my_rbt::rb_node::RED;
                        RotateLeft(s);
                        s = p->parent_->left_;
                    }

                    s->color_ = p->parent_->color_;
                    p->parent_->color_ = my_rbt::rb_node::BLACK;
                    s->left_->color_ = my_rbt::rb_node::BLACK;
                    RotateRight(p->parent_);
                    p = root_;
                }
            }

            p->color_ = my_rbt::rb_node::BLACK;
            root_->color_ = my_rbt::rb_node::BLACK;
        }
    }
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::LowerBound(const_key_ref x) const {
    for (auto it = begin(); it != end(); ++it) {
        if (!(*it < x)) {
            return it;
        }
    }

    return end();
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::Erase(iterator pos) {
    auto ret = iterator(pos.getPtr());
    ++ret;
    Remove(*pos);

    return ret;
}

template <typename T>
typename RBTree<T>::iterator RBTree<T>::Erase(iterator first, iterator last) {
    auto ret = last;

    if (ret != end()) {
        ++ret;
    }

    std::vector<T> remover;
    for (auto it = first; it != last; ++it) {
        remover.push_back(*it);
    }

    for (auto& e : remover) {
        remove(e);
    }

    return ret;
}

template <typename T>
std::size_t RBTree<T>::Erase(const_key_ref key) {
    std::size_t count = 0;

    while (find(key)) {
        remove(key);
        count++;
    }

    return count;
}

template <typename T>
void RBTree<T>::Insert(iterator first, iterator last) {
    for (auto it = first; it != last; ++it) {
        Insert(*it);
    }
}

template <typename T>
std::pair<typename RBTree<T>::iterator, bool> RBTree<T>::InsertUnique(
    const_key_ref val) {
    auto check = GetSize();
    Insert(val);
    // если после вставки размер не поменялся
    if (check == GetSize()) {
        return {IterateTo(val), false};
    } else {
        for (auto it = begin(); it != end(); ++it) {
            if ((!(*it < val)) && !(val < *it)) {
                return {it, true};
            }
        }
    }
    return {IterateTo(val), false};
}
}  // namespace my_rbt
