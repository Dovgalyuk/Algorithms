#pragma once
#include <memory>

template<class T>
class PolymorphicIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    template<class Iter>
    explicit PolymorphicIterator(Iter&& iter) : ptr(std::make_unique<model<std::decay_t<Iter>>>(std::forward<Iter>(iter))) {}

    value_type operator*() const { return ptr->dereference(); }
    PolymorphicIterator& operator++() { ptr->increment(); return *this; }

    bool operator==(const PolymorphicIterator& other) const { return (ptr && other.ptr) ? ptr->equals(*other.ptr) : ptr == other.ptr; }
    bool operator!=(const PolymorphicIterator& other) const { return !(*this == other); }

    PolymorphicIterator(const PolymorphicIterator& other) : ptr(other.ptr ? other.ptr->clone() : nullptr) {}
    PolymorphicIterator& operator=(const PolymorphicIterator& other) {
        if (this != &other) {
            ptr = other.ptr ? other.ptr->clone() : nullptr;
        }

        return *this;
    }

    PolymorphicIterator(PolymorphicIterator&& other) = default;
    PolymorphicIterator& operator=(PolymorphicIterator&& other) = default;
private:
    struct con {
        virtual ~con() = default;
        virtual value_type dereference() const = 0;
        virtual void increment() = 0;
        virtual bool equals(const con& other) const = 0;
        virtual std::unique_ptr<con> clone() const =0;
    };

    template<class Iter>
    struct model : con {
        Iter iter;

        explicit model(Iter iter) : iter(std::move(iter)) {}

        value_type dereference() const override {
            return *iter;
        }

        void increment() override {
            ++iter;
        }

        bool equals(const con& other) const override {
            const auto* ot = dynamic_cast<const model*>(&other);
            return ot && iter == ot->iter;
        }

        std::unique_ptr<con> clone() const override {
            return std::make_unique<model>(*this);
        }
    };

    std::unique_ptr<con> ptr;
};