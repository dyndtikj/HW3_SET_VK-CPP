#include <memory>

#include "rb_tree.h"

namespace my_stl {
template <class Key>
class Set {
   private:
    typedef std::vector<Key> Vector;
    typedef my_rbt::RBTree<Key> Tree;

   public:
    typedef Key key_type;
    typedef typename Tree::iterator iterator;
    typedef typename Tree::iterator const_iterator;

    Set();
    template <class Iterator>
    Set(Iterator, Iterator);
    Set(std::initializer_list<key_type> list);
    Set(const Set& other);
    Set& operator=(const Set& other);
    Set& operator=(std::initializer_list<key_type> list);
    // The dtor only erases the elements, and note that if the elements
    // themselves are pointers, the pointed-to memory is not touched in any way.
    // Managing the pointer is the user's responsibility.
    ~Set(){};
    void clear();

    // 2
    const_iterator begin() const;
    const_iterator end() const;

    // 3
    std::pair<const_iterator, bool> insert(const key_type&);
    template <class Iterator>
    void insert(Iterator, Iterator);

    void erase(iterator);
    size_t erase(const key_type&);

    // 4
    size_t size() const;
    bool empty() const;

    const_iterator find(const key_type&) const;
    const_iterator lower_bound(const key_type&) const;

    friend std::ostream& operator<<(std::ostream& os, const Set<Key>& s) {
        os << s.rbtree_;
        return os;
    }

   private:
    //        std::vector<Key> rbtree_;
    my_rbt::RBTree<Key> rbtree_;
};

template <class Key>
Set<Key>::Set() : rbtree_() {}

template <class Key>
template <class Iterator>
Set<Key>::Set(Iterator beginInput, Iterator endInput) : rbtree_() {
    while (beginInput != endInput) {
        insert(*beginInput);
        ++beginInput;
    }
}

template <class Key>
typename Set<Key>::const_iterator Set<Key>::begin() const {
    return rbtree_.begin();
}

template <class Key>
typename Set<Key>::const_iterator Set<Key>::end() const {
    return rbtree_.end();
}

template <class Key>
bool Set<Key>::empty() const {
    return rbtree_.IsEmpty();
}

template <class Key>
size_t Set<Key>::size() const {
    return rbtree_.GetSize();
}

template <class Key>
std::pair<typename Set<Key>::const_iterator, bool> Set<Key>::insert(
    const Key& value) {
    std::pair<typename Tree::iterator, bool> p = rbtree_.InsertUnique(value);
    return std::pair<iterator, bool>(p.first, p.second);
}

template <class Key>
template <class Iterator>
void Set<Key>::insert(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        insert(*first);
    }
}

template <class Key>
void Set<Key>::erase(typename Set<Key>::iterator position) {
    rbtree_.Erase(position);
}

template <class Key>

size_t Set<Key>::erase(const key_type& x) {
    iterator i = find(x);
    if (i != rbtree_.end()) {
        erase(i);
        return 1;
    }
    return 0;
}

template <class Key>
void Set<Key>::clear() {
    rbtree_.Clear();
}

template <class Key>
typename Set<Key>::const_iterator Set<Key>::find(const key_type& value) const {
        const_iterator i(lower_bound(value));
        if (i != end() && (value < *i)) {
            i = end();
        }
        return i;
}

template <class Key>
typename Set<Key>::const_iterator Set<Key>::lower_bound(
    const key_type& value) const {
    return rbtree_.LowerBound(value);
}

template <class Key>
Set<Key>& Set<Key>::operator=(const Set& other) {
    rbtree_ = other.rbtree_;
    return *this;
}

template <class Key>
Set<Key>::Set(std::initializer_list<key_type> list) {
    for (auto& e : list) {
        rbtree_.Insert(e);
    }
}

template <class Key>
Set<Key>::Set(const Set& other) {
    for (auto it = other.begin(); it != other.end(); it++) {
        rbtree_.Insert(*it);
    }
}
}  // namespace my_stl
