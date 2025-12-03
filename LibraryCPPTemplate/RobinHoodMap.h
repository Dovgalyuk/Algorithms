#pragma once
#include <utility>
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <bit>
#include <memory>
#include "vector.h"

template<class Key, class Value, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key> >
class RobinHoodMap {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<Key, Value>;
    using size_type = std::size_t;
    using hasher = Hash;
    using key_equal = KeyEqual;

    template<bool IsConst>
    class internalIterator {
        using map_type = std::conditional_t<IsConst, const RobinHoodMap, RobinHoodMap>;
        map_type *map_;
        size_type idx_;

        void advance() {
            while (idx_ < map_->capacity() &&
                   !map_->buckets_[idx_].occupied) {
                ++idx_;
            }
        }

    public:
        using value_type = value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = std::conditional_t<IsConst, const value_type*, value_type*>;
        using reference = std::conditional_t<IsConst, const value_type&, value_type&>;
        using iterator_category = std::forward_iterator_tag;

        internalIterator(map_type *m, const size_type i)
            : map_(m), idx_(i) {
            advance();
        }

        reference operator*() const {
            return map_->buckets_[idx_].kv;
        }

        pointer operator->() const {
            return &map_->buckets_[idx_].kv;
        }

        internalIterator &operator++() {
            ++idx_;
            advance();
            return *this;
        }

        internalIterator operator++(int) {
            internalIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const internalIterator &other) const {
            return map_ == other.map_ && idx_ == other.idx_;
        }

        bool operator!=(const internalIterator &other) const {
            return !(*this == other);
        }
    };

    using iterator = internalIterator<false>;
    using const_iterator = internalIterator<true>;

    RobinHoodMap() { init(INITIAL_CAPACITY); }
    explicit RobinHoodMap(const size_type cap) { init(cap); }

    ~RobinHoodMap() { clear(); }

    iterator find(const key_type &key) {
        size_type idx = findImpl(key);
        return idx == capacity() ? end() : iterator(this, idx);
    }

    const_iterator find(const key_type &key) const {
        size_type idx = findImpl(key);
        return idx == capacity() ? cend() : const_iterator(this, idx);
    }

    mapped_type &operator[](const key_type &key) {
        if (loadFactor() >= MAX_LOAD_FACTOR) rehash(buckets_.size() * 2);
        auto [val, flag] = insertImpl(key, mapped_type{});
        auto it = iterator(this, val);
        return it->second;
    }

    void insert(const value_type &value) {
        if (loadFactor() >= MAX_LOAD_FACTOR) rehash(buckets_.size() * 2);
        insertImpl(value.first, value.second);
    }

    std::pair<iterator, bool> insert_or_assign(const value_type &value) {
        if (loadFactor() >= MAX_LOAD_FACTOR) rehash(buckets_.size() * 2);
        auto [idx, resFlag] = insertImpl(value.first, value.second);

        auto it = iterator(this, idx);
        if (!resFlag) it->second = value.second;
        return {it, resFlag};
    }

    size_type erase(const key_type &key) {
        if (buckets_.empty()) return 0;
        std::size_t h = hashFn(key);
        size_type idx = h & mask_;
        dib_type dib = 0;

        while (true) {
            Entry &e = buckets_[idx];
            if (!e.occupied || dib > e.dib) return 0;
            if (e.hash == h && equalFn(e.kv.first, key)) break;
            ++dib;
            idx = (idx + 1) & mask_;
        }

        buckets_[idx].occupied = false;
        --size_;

        size_type cur = idx;
        size_type next = (cur + 1) & mask_;
        while (buckets_[next].occupied && buckets_[next].dib > 0) {
            buckets_[cur].kv = std::move(buckets_[next].kv);
            buckets_[cur].hash = buckets_[next].hash;
            buckets_[cur].dib = buckets_[next].dib - 1;
            buckets_[cur].occupied = true;

            buckets_[next].occupied = false;
            cur = next;
            next = (next + 1) & mask_;
        }

        return 1;
    }

    iterator erase(iterator pos) {
        if (pos == end()) return end();

        iterator next = pos;
        ++next;
        erase((*pos).first);
        return next;
    }

    void reserve(const size_type n) {
        size_type newCap = nextPow2(std::max<size_type>(2, static_cast<size_type>(n / MAX_LOAD_FACTOR) + 1));
        if (newCap > buckets_.size()) rehash(newCap);
    }

    bool contains(const key_type &key) const {
        return find(key) != cend();
    }

    [[nodiscard]] double loadFactor() const {
        return buckets_.empty() ? 0.0 : static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

    [[nodiscard]] size_type capacity() const noexcept { return buckets_.size(); }

    [[nodiscard]] size_type size() const noexcept { return size_; }
    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

    void clear() noexcept {
        for (auto &e: buckets_) e.occupied = false;
        size_ = 0;
    }

    iterator begin() { return iterator(this, 0); }
    iterator end() { return iterator(this, capacity()); }

    const_iterator cbegin() const { return const_iterator(this, 0); }
    const_iterator cend() const { return const_iterator(this, capacity()); }

private:
    using dib_type = std::uint16_t;

    struct Entry {
        value_type kv{};
        std::size_t hash = 0;
        dib_type dib = 0;
        bool occupied = false;

        Entry() = default;
    };

    void rehash(size_type newCap) {
        newCap = nextPow2(newCap);
        Vector<Entry> oldBuckets = std::move(buckets_);
        init(newCap);

        for (auto &e: oldBuckets) {
            if (e.occupied) {
                insertImpl(std::move(e.kv.first), std::move(e.kv.second));
            }
        }
    }

    void init(size_type cap) {
        cap = nextPow2(cap);
        buckets_.clear();
        buckets_.resize(cap);
        mask_ = cap - 1;
        size_ = 0;
    }

    static size_type nextPow2(const size_type n) {
        return std::bit_ceil(n);
    }

    template<typename K, typename V>
    std::pair<size_type, bool> insertImpl(K &&key, V &&value) {
        const std::size_t h = hashFn(key);
        size_type idx = h & mask_;
        constexpr dib_type dib = 0;

        key_type carryKey = std::forward<K>(key);
        mapped_type carryValue = std::forward<V>(value);
        std::size_t carryHash = h;
        dib_type carryDib = dib;

        while (true) {
            Entry &e = buckets_[idx];

            if (!e.occupied) {
                e.kv = {std::move(carryKey), std::move(carryValue)};
                e.hash = carryHash;
                e.dib = carryDib;
                e.occupied = true;
                ++size_;
                return {idx, true};
            }

            if (e.hash == carryHash && equalFn(e.kv.first, carryKey))
                return {idx, false};

            if (carryDib > e.dib) {
                std::swap(carryKey, e.kv.first);
                std::swap(carryValue, e.kv.second);
                std::swap(carryHash, e.hash);
                std::swap(carryDib, e.dib);
            }

            ++carryDib;
            idx = (idx + 1) & mask_;
        }
    }

    size_type findImpl(const key_type &key) const {
        if (buckets_.empty()) return capacity();

        std::size_t h = hashFn(key);
        size_type idx = h & mask_;
        dib_type dib = 0;

        while (true) {
            const Entry &e = buckets_[idx];
            if (!e.occupied || dib > e.dib) return capacity();
            if (e.hash == h && equalFn(e.kv.first, key)) return idx;
            ++dib;
            idx = (idx + 1) & mask_;
        }

        return capacity();
    }

    Vector<Entry> buckets_;
    size_type size_ = 0;
    size_type mask_ = 0;
    Hash hashFn;
    KeyEqual equalFn;

    static constexpr double MAX_LOAD_FACTOR = 0.8;
    static constexpr size_type INITIAL_CAPACITY = 64;
};
