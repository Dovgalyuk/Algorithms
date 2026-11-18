#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "map.h"

using StringMap = SplayMap<std::string, std::string>;

template <typename Func>
double measure(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main(int argc, char** argv) {
    std::vector<size_t> sizes;
    std::string outPath;
    int repeat = 1;
    std::vector<std::string> files;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--sizes" && i + 1 < argc) {
            std::string s = argv[++i];
            std::stringstream ss(s);
            std::string item;
            while (std::getline(ss, item, ',')) sizes.push_back(std::stoull(item));
        } else if (arg == "--repeat" && i + 1 < argc) {
            repeat = std::stoi(argv[++i]);
        } else if (arg == "--out" && i + 1 < argc) {
            outPath = argv[++i];
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty()) return 1;

    std::ofstream fout;
    if (!outPath.empty()) fout.open(outPath);
    std::ostream& out = outPath.empty() ? std::cout : fout;

    out << "file,pattern,records,splay_ms,map_ms,unordered_map_ms\n";

    for (const auto& file : files) {
        std::ifstream in(file);
        if (!in.is_open()) continue;
        std::string line;
        std::vector<std::pair<std::string, std::string>> data;
        std::string pattern = "unknown";

        while (std::getline(in, line)) {
            if (line.empty()) continue;
            if (line[0] == '#') {
                size_t pos = line.find("pattern=");
                if (pos != std::string::npos) {
                    pattern = line.substr(pos + 8);
                    if (!pattern.empty() && pattern.back() == ' ') pattern.pop_back();
                }
                continue;
            }
            if (line.size() > 4 && line.substr(0, 4) == "ADD ") {
                size_t space = line.find(' ', 4);
                if (space != std::string::npos) {
                    data.push_back({line.substr(4, space - 4), line.substr(space + 1)});
                }
            }
        }

        std::vector<size_t> localSizes = sizes;
        if (localSizes.empty()) {
            for (size_t s = 1000; s <= data.size(); s *= 10) localSizes.push_back(s);
            if (localSizes.empty() || localSizes.back() != data.size()) localSizes.push_back(data.size());
        }

        for (size_t N : localSizes) {
            if (N > data.size()) continue;

            double t_splay = 1e9, t_map = 1e9, t_umap = 1e9;

            for (int r = 0; r < repeat; ++r) {
                StringMap splay;
                double ta = measure([&]() {
                    for (size_t i = 0; i < N; ++i) splay.insert(data[i].first, data[i].second);
                });
                if (ta < t_splay) t_splay = ta;

                std::map<std::string, std::string> mp;
                double tm = measure([&]() {
                    for (size_t i = 0; i < N; ++i) mp[data[i].first] = data[i].second;
                });
                if (tm < t_map) t_map = tm;

                std::unordered_map<std::string, std::string> um;
                double tu = measure([&]() {
                    for (size_t i = 0; i < N; ++i) um[data[i].first] = data[i].second;
                });
                if (tu < t_umap) t_umap = tu;
            }

            out << file << "," << pattern << "," << N << "," << t_splay << "," << t_map << "," << t_umap << "\n";
        }
    }
    return 0;
}