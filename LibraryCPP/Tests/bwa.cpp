#include "bwa.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    BwaMap map;
    int counter = 0;
    // find in empty bwamap
    counter += (map.find("key") == nullptr && map.size() == 0 && !map.erase("key") && map.size() == 0);
    // insert new pair with same key (will update value)
    map.insert("key", "1");
    map.insert("key", "2");
    counter += (map.find("key") != nullptr && *map.find("key") == "2" && map.size() == 1);
    // restore existed key
    map.insert("key3", "3");
    map.insert("key4", "4");
    map.insert("key5", "6");
    bool temp = map.erase("key3");
    counter += (temp && map.find("key3") == nullptr && map.size() == 3 && !map.erase("key3") && map.size() == 3);
    map.insert("key3", "5");
    counter += (map.find("key3") != nullptr && *map.find("key3") == "5" && map.size() == 4);
    // demote test
    temp = map.size() == 4;
    map.erase("key");
    map.erase("key3");
    counter += (temp && map.size() == 2 && map.find("key") == nullptr && map.find("key3") == nullptr 
    && map.find("key4") != nullptr && *map.find("key4") == "4"
    && map.find("key5") != nullptr && *map.find("key5") == "6");

    // demote with merge
    map.erase("key4");
    map.erase("key5");
    map.insert("a", "1");
    map.insert("b", "2");
    map.insert("c", "3");
    map.insert("d", "4");
    map.insert("e", "5");
    map.insert("f", "6");
    map.erase("a");
    map.erase("b");
    counter += (map.size() == 4 && map.find("a") == nullptr && map.find("b") == nullptr 
    && map.find("c") != nullptr && *map.find("c") == "3" && map.find("d") != nullptr 
    && *map.find("d") == "4" && map.find("e") != nullptr && *map.find("e") == "5" 
    && map.find("f") != nullptr && *map.find("f") == "6");
    // erase all check size == 0 then restore 1 key
    map.erase("c");
    map.erase("d");
    map.erase("e");
    map.erase("f");
    temp = (map.size() == 0 && map.find("c") == nullptr && map.find("d") == nullptr 
    && map.find("e") == nullptr && map.find("f") == nullptr);
    map.insert("key", "1");
    counter += (temp && map.size() == 1 && map.find("key") != nullptr && *map.find("key") == "1");
    
    // iterator for empty map
    BwaMap empty;
    auto empty_it = empty.begin();
    temp = !empty_it.valid();
    empty_it.next();
    counter += (temp && !empty_it.valid());

    // sorted iteration over several blocks
    BwaMap ordered;
    ordered.insert("d", "4");
    ordered.insert("b", "2");
    ordered.insert("f", "6");
    ordered.insert("a", "1");
    ordered.insert("e", "5");
    ordered.insert("c", "3");
    ordered.insert("g", "7");
    string keys[] = {"a", "b", "c", "d", "e", "f", "g"};
    string values[] = {"1", "2", "3", "4", "5", "6", "7"};
    size_t index = 0;
    temp = true;
    for (auto it = ordered.begin(); it.valid(); it.next()) {
        if (index >= 7) {
            temp = false;
            break;
        }
        if (it.key() != keys[index] || it.value() != values[index]) {
            temp = false;
        }
        index++;
    }
    counter += (temp && index == 7);

    // skip deleted entry without demote
    ordered.erase("b");
    string remaining[] = {"a", "c", "d", "e", "f", "g"};
    index = 0;
    temp = true;
    for (auto it = ordered.begin(); it.valid(); it.next()) {
        if (index >= 6) {
            temp = false;
            break;
        }
        if (it.key() != remaining[index]) {
            temp = false;
        }
        index++;
    }
    counter += (temp && index == 6);

    // iteration after demote with merge
    ordered.erase("a");
    string after_demote[] = {"c", "d", "e", "f", "g"};
    index = 0;
    temp = true;
    for (auto it = ordered.begin(); it.valid(); it.next()) {
        if (index >= 5) {
            temp = false;
            break;
        }
        if (it.key() != after_demote[index]) {
            temp = false;
        }
        index++;
    }
    counter += (temp && index == 5);

    // iterator for one entry and reading after end
    BwaMap single;
    single.insert("key", "value");
    auto it = single.begin();
    temp = (it.valid() && it.key() == "key" && it.value() == "value");
    it.next();
    temp = temp && !it.valid();
    it.next();
    temp = temp && !it.valid();

    bool key_error = false;
    bool value_error = false;

    try {
        it.key();
    } catch (const out_of_range &) {
        key_error = true;
    }

    try {
        it.value();
    } catch (const out_of_range &) {
        value_error = true;
    }

    counter += (temp && key_error && value_error);
    if (counter == 12) {
        cout << "All tests passed\n";
        return 0;
    }
    
    cout << "Some tests failed: " << counter << "/12\n";
    
    return 1;
}
