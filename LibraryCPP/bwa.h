#ifndef BWA_H
#define BWA_H

#include <string>
#include <cstddef>
#include "vector.h"

class BwaMap {
public:
    class Iterator {
    public:
        explicit Iterator(const BwaMap &map);
        bool valid() const;
        const std::string &key() const;
        const std::string &value() const;
        void next();
    private:
        const BwaMap *map;
        Vector<size_t> positions;
        size_t current;

        void select();
    };

    Iterator begin() const;
    // add new pair, if key exist update value to new
    void insert(const std::string &key, const std::string &value);
    // find value by key
    const std::string *find(const std::string &key) const;
    // delete value by key. return True if key exist else False
    bool erase(const std::string &key);
    // return size of BWA map
    size_t size() const;
    
    BwaMap() = default;
private:
    struct Entry {
        std::string key;
        std::string value;
        bool deleted = false;
    };

    struct Block {
        Vector<Entry> entries;
        size_t deleted_count = 0;
    };
    Block merge(const Block &first, const Block &second);
    size_t lower_bound(const Block &block, const std::string &key) const;
    void demote(size_t level);
    Vector<Block> blocks;
    size_t count = 0;
};
#endif
