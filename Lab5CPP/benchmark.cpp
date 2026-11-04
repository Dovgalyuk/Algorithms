#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "map.h"

typedef std::pair<std::string, std::string> Record;

struct Input
{
    std::string path;
    std::string pattern = "unknown";
    std::vector<Record> records;
};

static bool readInput(const std::string &path, Input &input, size_t maxRecords)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        return false;
    }

    input.path = path;
    std::string line;

    while ((maxRecords == 0 || input.records.size() < maxRecords) && std::getline(file, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
        {
            line.erase(line.size() - 1);
        }

        if (line.compare(0, 1, "#") == 0)
        {
            std::string::size_type at = line.find("pattern=");
            if (at != std::string::npos)
            {
                std::string::size_type to = line.find(' ', at);
                input.pattern = line.substr(at + 8, to == std::string::npos ? std::string::npos : to - at - 8);
            }
            continue;
        }

        if (line.compare(0, 4, "ADD ") != 0)
        {
            continue;
        }

        std::string::size_type keyEnd = line.find(' ', 4);
        if (keyEnd == std::string::npos)
        {
            continue;
        }
        input.records.push_back(Record(line.substr(4, keyEnd - 4), line.substr(keyEnd + 1)));
    }

    return !file.bad();
}

template <typename Function>
static double measureMs(Function function)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    function();
    std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(finish - start).count();
}

static double median(std::vector<double> values)
{
    std::sort(values.begin(), values.end());
    return values[values.size() / 2];
}

static bool parseSizes(const std::string &text, std::vector<size_t> &sizes)
{
    std::string::size_type begin = 0;
    while (begin <= text.size())
    {
        std::string::size_type comma = text.find(',', begin);
        std::string part = text.substr(begin, comma == std::string::npos ? std::string::npos : comma - begin);
        char *end = nullptr;
        long long value = std::strtoll(part.c_str(), &end, 10);
        if (part.empty() || *end != '\0' || value <= 0)
        {
            return false;
        }

        sizes.push_back((size_t)value);
        if (comma == std::string::npos)
        {
            break;
        }

        begin = comma + 1;
    }
    return !sizes.empty();
}

static std::vector<size_t> defaultSizes(size_t total)
{
    std::vector<size_t> sizes;
    for (size_t base = 1000; base <= total; base *= 10)
    {
        sizes.push_back(base);
        if (base * 3 <= total)
        {
            sizes.push_back(base * 3);
        }
    }
    if (sizes.empty() || sizes.back() != total)
    {
        sizes.push_back(total);
    }
    return sizes;
}

static void settleAllocator()
{
    std::vector<char> block(200000);
    block[0] = 1;
}

template <typename Container, typename InsertOne>
static void timedPass(const std::vector<Record> &records, const std::vector<size_t> &checkpoints, Container &container, InsertOne insertOne, std::vector<double> &elapsed)
{
    settleAllocator();
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    size_t next = 0;
    size_t last = checkpoints.back();

    for (size_t i = 0; i < last; i++)
    {
        insertOne(container, records[i]);
        if (i + 1 == checkpoints[next])
        {
            elapsed.push_back(std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count());
            next++;
        }
    }
}

static int repetitionsFor(size_t count, int repetitions)
{
    if (count <= 100000)
    {
        return repetitions;
    }
    return std::max(1, (int)((long long)repetitions * 100000 / (long long)count));
}

struct Result
{
    double avlMs;
    double mapMs;
    double unorderedMs;
};

static bool runAll(const std::vector<Record> &records, const std::vector<size_t> &sizes, int repetitions, std::vector<Result> &results)
{
    std::vector<std::vector<double>> samples[3];
    for (int c = 0; c < 3; c++)
    {
        samples[c].resize(sizes.size());
    }
    for (int pass = 0; pass < repetitions; pass++)
    {
        std::vector<size_t> included;
        std::vector<size_t> indexes;
        for (size_t i = 0; i < sizes.size(); i++)
            if (repetitionsFor(sizes[i], repetitions) > pass)
            {
                included.push_back(sizes[i]);
                indexes.push_back(i);
            }
        if (included.empty())
        {
            break;
        }
        std::vector<double> avlTimes, mapTimes, unorderedTimes;
        size_t avlSize = 0, mapSize = 0, unorderedSize = 0;

        AvlTreeMap<std::string, std::string> container;
        timedPass(records, included, container, [](AvlTreeMap<std::string, std::string> &c, const Record &r){ c.insert(r.first, r.second); }, avlTimes);
        avlSize = container.size();
        if (!container.validate())
        {
            std::cerr << "mismatch: AVL invariants are broken\n";
            return false;
        }

        std::map<std::string, std::string> container1;
        timedPass(records, included, container1, [](std::map<std::string, std::string> &c, const Record &r) { c.insert_or_assign(r.first, r.second); }, mapTimes);
        mapSize = container1.size();

        std::unordered_map<std::string, std::string> container2;
        timedPass(records, included, container2, [](std::unordered_map<std::string, std::string> &c, const Record &r) { c.insert_or_assign(r.first, r.second); }, unorderedTimes);
        unorderedSize = container2.size();

        if (avlSize != mapSize || mapSize != unorderedSize)
        {
            std::cerr << "mismatch: sizes differ, avl=" << avlSize << " map=" << mapSize
                      << " unordered_map=" << unorderedSize << "\n";
            return false;
        }

        for (size_t k = 0; k < indexes.size(); k++)
        {
            samples[0][indexes[k]].push_back(avlTimes[k]);
            samples[1][indexes[k]].push_back(mapTimes[k]);
            samples[2][indexes[k]].push_back(unorderedTimes[k]);
        }
    }

    results.clear();
    for (size_t i = 0; i < sizes.size(); i++)
    {
        Result r;
        r.avlMs = median(samples[0][i]);
        r.mapMs = median(samples[1][i]);
        r.unorderedMs = median(samples[2][i]);
        results.push_back(r);
    }
    return true;
}

static void usage()
{
    std::cerr << "Usage: AvlBenchmark [--sizes n1,n2,...] [--repeat R] [--out file.csv] input_file...\n";
}

int main(int argc, char **argv)
{
    std::vector<size_t> sizes;
    std::vector<std::string> files;
    std::string outPath;
    int repetitions = 5;

    for (int i = 1; i < argc; i++)
    {
        std::string argument = argv[i];
        if (argument == "--sizes" && i + 1 < argc)
        {
            if (!parseSizes(argv[++i], sizes))
            {
                std::cerr << "Invalid --sizes\n";
                return 1;
            }
        }
        else if (argument == "--repeat" && i + 1 < argc)
        {
            repetitions = std::atoi(argv[++i]);
            if (repetitions < 1)
            {
                std::cerr << "Invalid --repeat\n";
                return 1;
            }
        }
        else if (argument == "--out" && i + 1 < argc)
            outPath = argv[++i];
        else if (argument.compare(0, 2, "--") == 0)
        {
            usage();
            return 1;
        }
        else
            files.push_back(argument);
    }

    if (files.empty())
    {
        usage();
        return 1;
    }

    std::ostringstream csv;
    csv << "file,pattern,records,avl_ms,map_ms,unordered_map_ms\n";
    std::cout << "file,pattern,records,avl_ms,map_ms,unordered_map_ms\n";

    size_t maxRecords = 0;
    for (size_t s = 0; s < sizes.size(); s++)
        maxRecords = std::max(maxRecords, sizes[s]);

    for (size_t f = 0; f < files.size(); f++)
    {
        Input input;
        if (!readInput(files[f], input, maxRecords))
        {
            std::cerr << "Cannot read input file: " << files[f] << "\n";
            return 1;
        }
        if (input.records.empty())
        {
            std::cerr << "Cannot use input file without ADD records: " << files[f] << "\n";
            return 1;
        }

        std::vector<size_t> localSizes;
        if (sizes.empty())
            localSizes = defaultSizes(input.records.size());
        else
            for (size_t s = 0; s < sizes.size(); s++)
            {
                if (sizes[s] <= input.records.size())
                {
                    localSizes.push_back(sizes[s]);
                }
            }
        std::sort(localSizes.begin(), localSizes.end());
        localSizes.erase(std::unique(localSizes.begin(), localSizes.end()), localSizes.end());

        std::vector<Result> results;
        if (!runAll(input.records, localSizes, repetitions, results))
        {
            return 1;
        }
        for (size_t s = 0; s < localSizes.size(); s++)
        {
            std::ostringstream row;
            row << input.path << ',' << input.pattern << ',' << localSizes[s] << ',' << results[s].avlMs << ',' << results[s].mapMs << ',' << results[s].unorderedMs << '\n';
            csv << row.str();
        }
    }

    if (!outPath.empty())
    {
        std::ofstream out(outPath.c_str());
        if (!out.is_open())
        {
            std::cerr << "Cannot write output file: " << outPath << "\n";
            return 1;
        }
        out << csv.str();
        out.close();
    }

    return 0;
}