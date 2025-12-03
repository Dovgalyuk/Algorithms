#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include "RobinHoodMap.h"

void testBasicInsertFind() {
    RobinHoodMap<std::string, int> map;

    map.insert({"A", 10});
    map.insert({"B", 20});
    map.insert({"C", 30});

    if (!map.contains("A")) std::exit(1);
    if (!map.contains("B")) std::exit(1);
    if (!map.contains("C")) std::exit(1);

    if (map.find("A")->second != 10) std::exit(1);
    if (map.find("B")->second != 20) std::exit(1);
    if (map.find("C")->second != 30) std::exit(1);

    if (map.contains("NotExist")) std::exit(1);
}

void testOperatorAccess() {
    RobinHoodMap<std::string, int> map;

    map["X"] = 123;
    if (map["X"] != 123) std::exit(1);

    map["X"] = 555;
    if (map["X"] != 555) std::exit(1);

    if (map["New"] != 0) std::exit(1);
}

void testInsertOrAssign() {
    RobinHoodMap<std::string, int> map;

    if (auto [it1, inserted1] = map.insert_or_assign({"A", 1});
        !inserted1 || it1->second != 1) std::exit(1);

    auto [it2, inserted2] = map.insert_or_assign({"A", 999});
    if (inserted2) std::exit(1);
    if (it2->second != 999) std::exit(1);
}

void testErase() {
    RobinHoodMap<std::string, int> map;

    map.insert({"A", 10});
    map.insert({"B", 20});
    map.insert({"C", 30});

    if (map.erase("B") != 1) std::exit(1);
    if (map.contains("B")) std::exit(1);

    if (map.erase("B") != 0) std::exit(1);
}

void testIteratorBasic() {
    RobinHoodMap<std::string, int> map;

    map.insert({"A", 1});
    map.insert({"B", 2});
    map.insert({"C", 3});

    int sum = 0;
    for (auto it = map.begin(); it != map.end(); ++it)
        sum += it->second;

    if (sum != (1 + 2 + 3)) std::exit(1);
}

void testRehashExpand() {
    RobinHoodMap<int, int> map(4);

    for (int i = 0; i < 1000; ++i)
        map.insert({i, i * 2});

    for (int i = 0; i < 1000; ++i) {
        if (!map.contains(i)) std::exit(1);
        if (map.find(i)->second != i * 2) std::exit(1);
    }
}

void testStabilityAfterRehash() {
    RobinHoodMap<std::string, int> map(2);

    map.insert({"A", 1});
    map.insert({"B", 2});
    map.insert({"C", 3});
    map.insert({"D", 4});

    if (map.find("A")->second != 1) std::exit(1);
    if (map.find("B")->second != 2) std::exit(1);
    if (map.find("C")->second != 3) std::exit(1);
    if (map.find("D")->second != 4) std::exit(1);
}

void testRandomInsertErase() {
    RobinHoodMap<int, int> map;

    std::mt19937 rng{};
    std::uniform_int_distribution<int> dist(0, 10000);

    for (int i = 0; i < 5000; ++i) {
        int x = dist(rng);
        map.insert({x, x + 1});
    }

    for (int i = 0; i < 5000; ++i) {
        int x = dist(rng);
        map.erase(x);
    }

    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it->second != it->first + 1) std::exit(1);
    }
}

void testClear() {
    RobinHoodMap<int, int> map;

    for (int i = 0; i < 100; ++i)
        map.insert({i, i});

    map.clear();

    if (!map.empty()) std::exit(1);
    if (map.begin() != map.end()) std::exit(1);
}

void testEraseIterator() {
    RobinHoodMap<int, int> map;

    map.insert({1,1});
    map.insert({2,2});
    map.insert({3,3});

    const auto it = map.find(2);

    if (const auto next = map.erase(it); next != map.end() && next->first == 2)
        std::exit(1);

    if (map.contains(2)) std::exit(1);
}

void testOverwriteBehavior() {
    RobinHoodMap<std::string, int> map;

    map.insert({"A", 1});
    map.insert({"A", 2});

    if (map.find("A")->second != 1) std::exit(1);

    map.insert_or_assign({"A", 3});

    if (map.find("A")->second != 3) std::exit(1);
}

void loadTest() {
    using Key = int;
    using Value = int;
    constexpr std::size_t N = 1'000'000;

    std::mt19937_64 rng{std::random_device{}()};
    std::uniform_int_distribution<Key> keyDist(0, N * 2);
    std::uniform_int_distribution<Value> valDist(1, N);

    RobinHoodMap<Key, Value> map;
    map.reserve(N / 2);

    std::vector<Key> insertedKeys;
    insertedKeys.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < N; ++i) {
        Key k = keyDist(rng);
        Value v = valDist(rng);
        map.insert({k, v});
        insertedKeys.push_back(k);
    }
    const auto insertTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();

    std::cout << "Inserted " << map.size() << " unique keys (" << N << " ops) in "
              << insertTime << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (Key k : insertedKeys) {
        if (auto it = map.find(k); it == map.end()) {
            std::cerr << "ERROR: key " << k << " missing after insert!\n";
            std::exit(1);
        }
    }
    const auto findTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();

    std::cout << "Verified all keys via find() in " << findTime << " ms\n";

    std::shuffle(insertedKeys.begin(), insertedKeys.end(), rng);
    start = std::chrono::high_resolution_clock::now();
    std::size_t erased = 0;
    for (std::size_t i = 0; i < N / 2; ++i) {
        erased += map.erase(insertedKeys[i]);
    }
    const auto eraseTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();

    std::cout << "Erased " << erased << " keys (" << map.size() << " remain) in "
              << eraseTime << " ms\n";


    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    std::size_t count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        ++count;
        sum += static_cast<long long>(it->first) ^ it->second;
    }
    const auto iterTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();

    if (count != map.size()) {
        std::cerr << "iterator count (" << count << ") != size() (" << map.size() << ")\n";
        std::exit(1);
    }

    std::cout << "Iterated " << count << " elements, checksum = " << (sum % 10000)
              << " in " << iterTime << " ms\n";

    for (int i = 0; i < 1000; ++i) {
        map[i] = i * i;
    }
    if (map[500] != 250'000) {
        std::cerr << "operator[] broken\n";
        std::exit(1);
    }

    map.clear();
    if (!map.empty() || map.size() != 0 || map.begin() != map.end()) {
        std::cerr << "clear() failed\n";
        std::exit(1);
    }
}

std::string randomString(std::mt19937_64 &rng, const std::size_t len = 12) {
    static const std::string chars =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<std::size_t> dist(0, chars.size() - 1);
    std::string s(len, '\0');
    for (std::size_t i = 0; i < len; ++i)
        s[i] = chars[dist(rng)];
    return s;
}

std::string collidingString(std::mt19937_64 &rng, const std::size_t prefixLen = 8) {
    static const std::string prefix = "COLLIDE_";
    const auto suffix = randomString(rng, 6);
    return prefix.substr(0, prefixLen) + suffix;
}

void stringLoadTest() {
    constexpr std::size_t N = 1'000'000;

    std::mt19937_64 rng{std::random_device{}()};
    RobinHoodMap<std::string, std::string> map;
    map.reserve(N / 2);

    std::vector<std::string> keys;
    keys.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < N; ++i) {
        std::string key = (i % 5 == 0)
            ? collidingString(rng)
            : randomString(rng);
        std::string value = randomString(rng, 20);
        map.insert({key, value});
        keys.push_back(std::move(key));
    }

    const auto insertMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Inserted " << map.size() << " unique string keys (N=" << N
              << ") in " << insertMs << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto &k : keys) {
        if (auto it = map.find(k); it == map.end()) {
            std::cerr << "key missing: " << k << "\n";
            std::exit(1);
        }
    }
    const auto findMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Verified all keys via find() in " << findMs << " ms\n";

    std::shuffle(keys.begin(), keys.end(), rng);
    start = std::chrono::high_resolution_clock::now();
    std::size_t erased = 0;
    for (std::size_t i = 0; i < N / 2; ++i) {
        erased += map.erase(keys[i]);
    }
    const auto eraseMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Erased " << erased << " keys (" << map.size() << " left) in "
              << eraseMs << " ms\n";

    std::size_t count = 0;
    for ([[maybe_unused]] auto &p : map) ++count;
    if(count != map.size()) std::exit(1);
}

int main() {
    testBasicInsertFind();
    testOperatorAccess();
    testInsertOrAssign();
    testErase();
    testIteratorBasic();
    testRehashExpand();
    testStabilityAfterRehash();
    testRandomInsertErase();
    testClear();
    testEraseIterator();
    testOverwriteBehavior();
    loadTest();
    stringLoadTest();

    return 0;
}

