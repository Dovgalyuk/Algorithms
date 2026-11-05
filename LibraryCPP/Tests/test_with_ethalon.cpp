#include <map>
#include <random>
#include "bwa.h"
using namespace std;

int main(){
    BwaMap actual;
    map<string, string> expected;
    mt19937 random(53);
    bool ok = true;

    for (int i = 0; i < 10000; i++) {
        string key = "key" + to_string(random() % 1000);
        int operation = random() % 3;

        if (operation == 0) {
            string value = to_string(random());

            actual.insert(key, value);
            expected[key] = value;
        } else if (operation == 1) {
            bool removed = actual.erase(key);
            bool expected_removed = expected.erase(key) != 0;

            if (removed != expected_removed) ok = false;
        } else {
            const string *value = actual.find(key);
            auto found = expected.find(key);

            if (found == expected.end()) {
                if (value != nullptr) ok = false;
            } else {
                if (value == nullptr || *value != found->second) {
                    ok = false;
                }
            }
        }

        if (actual.size() != expected.size()) ok = false;

        if (!ok) {
            return 1;
        }
    }
    auto it = actual.begin();
    auto reference = expected.begin();

    while (it.valid() && reference != expected.end()) {
        if (it.key() != reference->first ||
            it.value() != reference->second) {
            return 1;
        }

        it.next();
        ++reference;
    }

    if (it.valid() || reference != expected.end()) {
        return 1;
    }

    return 0;
}