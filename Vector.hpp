#pragma once
#include <bits/stdc++.h>

template <typename T>
class Vector {
public:
    Vector() : a_(std::make_unique<T[]>(1)), cap_(1), sz_(0){};

    Vector(int n) : a_(std::make_unique<T[]>(n)), cap_(n), sz_(n){};

    Vector(int n, T init) : a_(std::make_unique<T[]>(n)), cap_(n), sz_(n) {
        for (int i = 0; i < sz_; i++) {
            a_[i] = init;
        }
    }

    Vector(const Vector &oth)
        : a_(std::make_unique<T[]>(oth.cap_)), cap_(oth.cap_), sz_(oth.sz_) {
        for (int i = 0; i < sz_; i++) {
            a_[i] = oth.a_[i];
        }
    }

    Vector(Vector &&oth) noexcept
        : a_(std::move(oth.a_)), cap_(oth.cap_), sz_(oth.sz_){};

    ~Vector() = default;

    Vector &operator=(const Vector &oth) {
        if (this == &oth) {
            return *this;
        }
        Clear();
        cap_ = oth.cap_;
        sz_ = oth.sz_;
        a_ = std::make_unique<T[]>(cap_);
        for (int i = 0; i < sz_; i++) {
            a_[i] = oth.a_[i];
        }
        return *this;
    }

    Vector &operator=(Vector &&oth) noexcept {
        if (this == &oth) {
            return *this;
        }
        Clear();
        cap_ = oth.cap_;
        sz_ = oth.sz_;
        a_ = std::move(oth.a_);
        return *this;
    }

    void ChangeCap() {
        if (sz_ < cap_ / 4) {
            while (sz_ < cap_ / 4) cap_ /= 2;
            Vector tmp(cap_);
            for (int i = 0; i < sz_; i++) {
                tmp[i] = a_[i];
            }
            int wsz = sz_;
            *this = std::move(tmp);
            sz_ = wsz;
            return;
        }
        if (sz_ > cap_) {
            while (cap_ < sz_) cap_ *= 2;
            Vector tmp(cap_);
            for (int i = 0; i < sz_; i++) {
                tmp[i] = a_[i];
            }
            int wsz = sz_;
            *this = std::move(tmp);
            sz_ = wsz;
        }
    }

    void Resize(int n) {
        if (cap_ >= n) {
            sz_ = n;
            ChangeCap();
            return;
        }
        Vector tmp(n);
        for (int i = 0; i < sz_; i++) {
            tmp[i] = a_[i];
        }
        *this = std::move(tmp);
    }

    void Assign(int n, T init) {
        Resize(n);
        for (int i = 0; i < sz_; i++) {
            a_[i] = init;
        }
    }

    bool Empty() const { return !sz_; }

    int Size() const { return sz_; }

    int Capacity() const { return cap_; }

    T &operator[](int pos) { return a_[pos]; }

    const T &operator[](int pos) const { return a_[pos]; }

    T &At(int pos) {
        if (pos >= sz_) {
            throw std::out_of_range("at(): index out of range");
        }
        return a_[pos];
    }

    const T &At(int pos) const {
        if (pos >= sz_) {
            throw std::out_of_range("at(): index out of range");
        }
        return a_[pos];
    }

    T &Front() { return At(0); }

    const T &Front() const { return At(0); }

    T &Back() { return At(sz_ - 1); }

    const T &Back() const { return At(sz_ - 1); }

    T *Data() { return a_.get(); }

    const T *Data() const { return a_.get(); }

    void Reserve(int n) {
        if (cap_ >= n) {
            return;
        }
        int wsz = sz_;
        Resize(n);
        sz_ = wsz;
    }

    void ShrinkToFit() {
        if (sz_ != cap_) {
            Vector tmp(sz_);
            for (int i = 0; i < sz_; i++) {
                tmp[i] = a_[i];
            }
            *this = std::move(tmp);
        }
    }

    void Clear() {
        a_ = std::make_unique<T[]>(1);
        cap_ = 0;
        sz_ = 0;
    }

    void PushBack(T x) {
        sz_++;
        ChangeCap();
        a_[sz_ - 1] = std::move(x);
    }

    void PopBack() {
        sz_--;
        ChangeCap();
    }

    void Swap(Vector &&oth) {
        Vector tmp = std::move(oth);
        oth = std::move(*this);
        *this = std::move(tmp);
    }

    template <typename U>
    friend bool operator==(const Vector<U> &, const Vector<U> &);

    struct Iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(T *whr) : cur_(whr){};
        Iterator() : cur_(nullptr){};
        Iterator &operator++() {
            ++cur_;
            return *this;
        }
        Iterator operator++(int) {
            Iterator was(cur_);
            ++cur_;
            return was;
        }
        Iterator &operator--() {
            --cur_;
            return *this;
        }
        Iterator operator--(int) {
            Iterator was(cur_);
            --cur_;
            return was;
        }
        Iterator operator+(int sz) const { return Iterator(cur_ + sz); }
        Iterator operator-(int sz) const { return Iterator(cur_ - sz); }
        difference_type operator-(const Iterator &oth) const {
            return cur_ - oth.cur_;
        }
        bool operator==(const Iterator &rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(const Iterator &rhs) const { return cur_ != rhs.cur_; }
        bool operator<(const Iterator &rhs) const { return cur_ < rhs.cur_; }
        bool operator<=(const Iterator &rhs) const { return cur_ <= rhs.cur_; }
        bool operator>(const Iterator &rhs) const { return cur_ > rhs.cur_; }
        bool operator>=(const Iterator &rhs) const { return cur_ >= rhs.cur_; }
        reference operator*() const { return *cur_; }
        pointer operator->() const { return cur_; }

        T *cur_;
    };

    struct ReverseIterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        ReverseIterator(T *whr) : cur_(whr){};
        ReverseIterator() : cur_(nullptr){};
        ReverseIterator &operator++() {
            --cur_;
            return *this;
        }
        ReverseIterator operator++(int) {
            ReverseIterator was(cur_);
            --cur_;
            return was;
        }
        ReverseIterator &operator--() {
            ++cur_;
            return *this;
        }
        ReverseIterator operator--(int) {
            ReverseIterator was(cur_);
            ++cur_;
            return was;
        }
        ReverseIterator operator+(int sz) const {
            return ReverseIterator(cur_ - sz);
        }
        ReverseIterator operator-(int sz) const {
            return ReverseIterator(cur_ + sz);
        }
        difference_type operator-(const ReverseIterator &oth) const {
            return oth.cur_ - cur_;
        }
        bool operator==(const ReverseIterator &rhs) const {
            return cur_ == rhs.cur_;
        }
        bool operator!=(const ReverseIterator &rhs) const {
            return cur_ != rhs.cur_;
        }
        bool operator<(const ReverseIterator &rhs) const {
            return cur_ > rhs.cur_;
        }
        bool operator<=(const ReverseIterator &rhs) const {
            return cur_ >= rhs.cur_;
        }
        bool operator>(const ReverseIterator &rhs) const {
            return cur_ < rhs.cur_;
        }
        bool operator>=(const ReverseIterator &rhs) const {
            return cur_ <= rhs.cur_;
        }
        reference operator*() const { return *(cur_ - 1); }
        pointer operator->() const { return cur_ - 1; }

        T *cur_;
    };

    Iterator begin() { return Iterator(a_.get()); }

    Iterator end() { return Iterator(a_.get() + sz_); }

    ReverseIterator rbegin() { return ReverseIterator(a_.get() + sz_); }

    ReverseIterator rend() { return ReverseIterator(a_.get()); }

    Iterator Insert(Iterator whr, T wht) {
        int pos = whr - begin();
        sz_++;
        ChangeCap();
        for (int i = sz_; i > pos + 1; i--) {
            a_[i - 1] = std::move(a_[i - 2]);
        }
        a_[pos] = wht;
        return begin() + pos;
    }

    Iterator Erase(Iterator whr) {
        int pos = whr - begin();
        for (int i = pos; i < sz_ - 1; i++) {
            a_[i] = std::move(a_[i + 1]);
        }
        sz_--;
        ChangeCap();
        return begin() + pos;
    }

    template <typename... Args>
    void EmplaceBack(Args &&...args) {
        sz_++;
        ChangeCap();
        a_[sz_ - 1] = std::move(T(std::forward<Args>(args)...));
    }

    template <typename It, typename... Args>
    It Emplace(It whr, Args &&...args) {
        int pos = whr - begin();
        sz_++;
        ChangeCap();
        for (int i = sz_; i > pos + 1; i--) {
            a_[i - 1] = std::move(a_[i - 2]);
        }
        a_[pos] = std::move(T(std::forward<Args>(args)...));
        return begin() + pos;
    }

private:
    std::unique_ptr<T[]> a_;
    int cap_;
    int sz_;
};

template <typename T>
bool operator==(const Vector<T> &lhs, const Vector<T> &rhs) {
    if (lhs.sz_ != rhs.sz_) {
        return false;
    }
    for (int i = 0; i < lhs.sz_; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

struct MyClass {
    MyClass() = default;

    MyClass(int a, int b, int c) { x = a + b + c; }

    int x;
};