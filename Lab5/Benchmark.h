#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <iomanip>
#include <cmath>

template<typename RHMap>
class Benchmark {
public:
    using Clock = std::chrono::high_resolution_clock;

    static std::vector<std::string> generateStrings(
        const std::size_t count,
        const std::size_t len = 12,
        const unsigned seed = 0) {
        std::mt19937_64 rng(seed ? seed : std::random_device{}());
        if (seed) rng.seed(seed);

        static const std::string alphabet =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::uniform_int_distribution<std::size_t> dist(0, alphabet.size() - 1);

        std::vector<std::string> data;
        data.reserve(count);

        for (std::size_t i = 0; i < count; ++i) {
            std::string s(len, '\0');
            for (std::size_t j = 0; j < len; ++j)
                s[j] = alphabet[dist(rng)];
            data.emplace_back(std::move(s));
        }
        return data;
    }

    static void benchmarkString(
        const std::vector<std::string> &keys,
        long long &rhIns, long long &stdIns,
        long long &rhFind, long long &stdFind,
        long long &rhErase, long long &stdErase) {
        auto values = generateStrings(keys.size(), 20);

        RHMap rh;
        auto start = Clock::now();
        for (std::size_t i = 0; i < keys.size(); ++i)
            rh.insert({keys[i], values[i]});
        rhIns = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();

        using StdMap = std::unordered_map<std::string, std::string>;
        StdMap stdm;
        start = Clock::now();
        for (std::size_t i = 0; i < keys.size(); ++i)
            stdm.emplace(keys[i], values[i]);
        stdIns = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();

        volatile size_t rhSink = 0, stdSink = 0;

        start = Clock::now();
        for (const auto &k: keys) {
            auto it = rh.find(k);
            if (it == rh.end()) std::exit(1);
            rhSink += it->second.size();
        }
        (void)rhSink;
        rhFind = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();

        start = Clock::now();
        for (const auto &k: keys) {
            auto it = stdm.find(k);
            if (it == stdm.end()) std::exit(1);
            stdSink += it->second.size();
        }
        (void)stdSink;
        stdFind = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();

        start = Clock::now();
        for (const auto &k: keys) rh.erase(k);
        rhErase = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();

        start = Clock::now();
        for (const auto &k: keys) stdm.erase(k);
        stdErase = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start).count();
    }

    static void runAllTests(
        const std::vector<std::size_t> &sizes,
        const std::string &outputCsv,
        const unsigned seed = 12345) {
        std::ofstream out(outputCsv);

        out << "size,rh_insert,std_insert,rh_find,std_find,rh_erase,std_erase,"
                "rh_insert_ns_op,std_insert_ns_op,rh_find_ns_op,std_find_ns_op,"
                "rh_erase_ns_op,std_erase_ns_op\n";


        long long rh_ins = 0, std_ins = 0;
        long long rh_find = 0, std_find = 0;
        long long rh_erase = 0, std_erase = 0;
        std::size_t last_n = 0;

        for (std::size_t i = 0; i < sizes.size(); ++i) {
            const std::size_t n = sizes[i];

            auto data = generateStrings(n, 12, seed);

            long long cur_rh_ins = 0, cur_std_ins = 0;
            long long cur_rh_find = 0, cur_std_find = 0;
            long long cur_rh_erase = 0, cur_std_erase = 0;


            benchmarkString(data, cur_rh_ins, cur_std_ins, cur_rh_find, cur_std_find, cur_rh_erase, cur_std_erase);


            if (i == sizes.size() - 1) {
                rh_ins = cur_rh_ins;
                std_ins = cur_std_ins;
                rh_find = cur_rh_find;
                std_find = cur_std_find;
                rh_erase = cur_rh_erase;
                std_erase = cur_std_erase;
                last_n = n;
            }

            out << n << ','
                    << cur_rh_ins << ',' << cur_std_ins << ','
                    << cur_rh_find << ',' << cur_std_find << ','
                    << cur_rh_erase << ',' << cur_std_erase;


            auto ns_op = [&](const long long us) { return (us * 1000.0) / n; };
            out << ',' << ns_op(cur_rh_ins)
                    << ',' << ns_op(cur_std_ins)
                    << ',' << ns_op(cur_rh_find)
                    << ',' << ns_op(cur_std_find)
                    << ',' << ns_op(cur_rh_erase)
                    << ',' << ns_op(cur_std_erase);

            out << '\n';
        }

        std::cout << "\nBenchmark completed. Results saved to " << outputCsv << "\n";

        if (last_n > 0) {
            std::cout << "\n=== Summary (N = " << last_n << ") ===\n";
            std::cout << std::fixed << std::setprecision(1);
            const auto ops = static_cast<double>(last_n);
            std::cout << "Insert:  RH=" << (rh_ins * 1000.0 / ops) << " ns/op, std=" << (std_ins * 1000.0 / ops) <<
                    " ns/op\n";
            std::cout << "Find:    RH=" << (rh_find * 1000.0 / ops) << " ns/op, std=" << (std_find * 1000.0 / ops) <<
                    " ns/op\n";
            std::cout << "Erase:   RH=" << (rh_erase * 1000.0 / ops) << " ns/op, std=" << (std_erase * 1000.0 / ops) <<
                    " ns/op\n";
        }
    }
};
