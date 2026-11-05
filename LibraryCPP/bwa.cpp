#include "bwa.h"
#include <stdexcept>

using namespace std;

size_t BwaMap::size() const
{
    return count;
}

size_t BwaMap::lower_bound(const Block &block, const string &key) const
{
    size_t left = 0;
    size_t right = block.entries.size();
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (block.entries.at(mid).key < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

const string *BwaMap::find(const string &key) const
{
    for (size_t i = 0; i < blocks.size(); i++) {
        const Block &block = blocks.at(i);
        size_t pos = lower_bound(block, key);
        for (size_t j = pos; j < block.entries.size(); j++) {
            const Entry &entry = block.entries.at(j);
            if (entry.key != key) break;
            if (!entry.deleted) return &entry.value;
        }
    }
    return nullptr;
}

BwaMap::Block BwaMap::merge(const Block &first, const Block &second)
{
    Block result;
    result.entries.resize(first.entries.size() + second.entries.size());
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while (i < first.entries.size() && j < second.entries.size()) {
        if (first.entries.at(i).key <= second.entries.at(j).key) {
            result.entries.at(k++) = first.entries.at(i++);
        } else {
            result.entries.at(k++) = second.entries.at(j++);
        }
    }
    while (i < first.entries.size()) {
        result.entries.at(k++) = first.entries.at(i++);
    }
    while (j < second.entries.size()) {
        result.entries.at(k++) = second.entries.at(j++);
    }
    result.deleted_count = first.deleted_count + second.deleted_count;
    return result;
}

void BwaMap::insert(const string &key, const string &value)
{
    for (size_t i = 0; i < blocks.size(); i++) {
        Block &block = blocks.at(i);
        size_t pos = lower_bound(block, key);
        if (pos < block.entries.size()) {
            Entry &entry = block.entries.at(pos);
            if (entry.key == key) {
                entry.value = value;
                if (entry.deleted) {
                    entry.deleted = false;
                    block.deleted_count--;
                    count++;
                }
                return;
            }
        }
    }
    Block current;
    current.entries.resize(1);
    current.entries.at(0).key = key;
    current.entries.at(0).value = value;
    size_t level = 0;
    while (true) {
        if (level == blocks.size()) {
            blocks.resize(level + 1);
        }
        Block &block = blocks.at(level);
        if (block.entries.size() == 0) {
            block.entries.swap(current.entries);
            block.deleted_count = current.deleted_count;
            count++;
            return;
        }
        Block combined = merge(block, current);
        block.entries.resize(0);
        block.deleted_count = 0;
        current.entries.swap(combined.entries);
        current.deleted_count = combined.deleted_count;
        level++;
    }
}

bool BwaMap::erase(const string &key)
{
    for (size_t i = 0; i < blocks.size(); i++) {
        Block &block = blocks.at(i);
        size_t pos = lower_bound(block, key);
        if (pos == block.entries.size()) continue;
        Entry &entry = block.entries.at(pos);
        if (entry.key != key || entry.deleted) continue;
        entry.deleted = true;
        block.deleted_count++;
        count--;
        demote(i);
        return true;
    }
    return false;
}

void BwaMap::demote(size_t level)
{
    Block &block = blocks.at(level);
    size_t slots = block.entries.size();
    if (level == 0) {
        if (block.deleted_count != 0) {
            block.entries.resize(0);
            block.deleted_count = 0;
        }
        return;
    }
    if (block.deleted_count < slots / 2) return;
    Block compact;
    compact.entries.resize(slots - block.deleted_count);
    size_t pos = 0;
    for (size_t i = 0; i < slots; i++) {
        const Entry &entry = block.entries.at(i);
        if (!entry.deleted) {
            compact.entries.at(pos++) = entry;
        }
    }
    Block &lower = blocks.at(level - 1);
    if (lower.entries.size() == 0) {
        lower.entries.swap(compact.entries);
        lower.deleted_count = 0;
        block.entries.resize(0);
        block.deleted_count = 0;
    } else {
        Block combined = merge(lower, compact);
        block.entries.swap(combined.entries);
        block.deleted_count = combined.deleted_count;
        lower.entries.resize(0);
        lower.deleted_count = 0;
    }
}

BwaMap::Iterator::Iterator(const BwaMap &map) : map(&map), current(map.blocks.size())
{
    positions.resize(map.blocks.size());
    select();
}

void BwaMap::Iterator::select()
{
    current = map->blocks.size();
    for (size_t i = 0; i < map->blocks.size(); i++) {
        const Block &block = map->blocks.at(i);
        size_t &pos = positions.at(i);
        while (pos < block.entries.size() &&
               block.entries.at(pos).deleted) {
            pos++;
        }
        if (pos == block.entries.size()) continue;
        if (current == map->blocks.size()) {
            current = i;
        } else {
            const Entry &candidate = block.entries.at(pos);
            const Entry &selected =
                map->blocks.at(current).entries.at(
                    positions.at(current));

            if (candidate.key < selected.key) {
                current = i;
            }
        }
    }
}

bool BwaMap::Iterator::valid() const
{
    return current < map->blocks.size();
}

const string &BwaMap::Iterator::key() const
{
    if (!valid()) {
        throw out_of_range("no more entries");
    }

    return map->blocks.at(current).entries.at(
        positions.at(current)).key;
}

const string &BwaMap::Iterator::value() const
{
    if (!valid()) {
        throw out_of_range("no more entries");
    }

    return map->blocks.at(current).entries.at(
        positions.at(current)).value;
}

void BwaMap::Iterator::next()
{
    if (!valid()) return;

    positions.at(current)++;
    select();
}

BwaMap::Iterator BwaMap::begin() const
{
    return Iterator(*this);
}