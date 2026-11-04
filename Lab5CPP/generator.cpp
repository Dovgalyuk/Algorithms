#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

unsigned long long randomState = 88172645463325252ULL;

unsigned long long getRandomNumber()
{
    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    return randomState;
}

bool parseNumber(const char *text, long long &number)
{
    char *end = nullptr;
    number = std::strtoll(text, &end, 10);

    return end != text && *end == '\0';
}

class FastOutput
{
private:
    static const size_t BUFFER_SIZE = 1 << 20;

    std::FILE *file;
    std::vector<char> buffer = std::vector<char>(BUFFER_SIZE);
    size_t position = 0;
    bool error = false;

public:
    explicit FastOutput(std::FILE *f) : file(f) {}

    bool flush()
    {
        if (position == 0) return !error;

        if (std::fwrite(buffer.data(), 1, position, file) != position) error = true;

        position = 0;

        return !error;
    }

    inline void put(char c)
    {
        if (position == BUFFER_SIZE) flush();

        if (!error) buffer[position++] = c;
    }

    inline void write(const char *text, size_t length)
    {
        while (length > 0 && !error)
        {
            size_t available = BUFFER_SIZE - position;
            size_t amount = (length < available) ? length : available;

            std::memcpy(buffer.data() + position, text, amount);

            position += amount;
            text += amount;
            length -= amount;

            if (position == BUFFER_SIZE) flush();
        }
    }

    inline void writeString(const char *text)
    {
        write(text, std::strlen(text));
    }

    inline void writeNumber(long long number)
    {
        char temp[32];
        int length = 0;

        bool negative = number < 0;

        unsigned long long value = negative ? static_cast<unsigned long long>(-(number + 1)) + 1 : static_cast<unsigned long long>(number);

        do
        {
            temp[length++] = static_cast<char>('0' + value % 10);
            value /= 10;
        }
        while (value > 0);

        if (negative) temp[length++] = '-';

        while (length > 0) put(temp[--length]);
    }

    inline void writeKey(long long key)
    {
        char temp[32];
        int length = 0;

        unsigned long long value = static_cast<unsigned long long>(key);

        do
        {
            temp[length++] = static_cast<char>('0' + value % 10);
            value /= 10;
        }
        while (value > 0);

        for (int i = length; i < 10; ++i) put('0');

        while (length > 0) put(temp[--length]);
    }

    inline void writeValue(long long number)
    {
        if (number % 5 == 0)
        {
            writeString("value ");
            writeNumber(number);
            writeString(" with spaces");
        }
        else
        {
            writeString("value_");
            writeNumber(number);
        }
    }

    inline void writeAdd(long long key, long long value)
    {
        writeString("ADD ");
        writeKey(key);
        put(' ');
        writeValue(value);
        put('\n');
    }

    inline void writeFind(long long key)
    {
        writeString("FIND ");
        writeKey(key);
        put('\n');
    }

    inline void writeDelete(long long key)
    {
        writeString("DEL ");
        writeKey(key);
        put('\n');
    }

    bool hasError() const
    {
        return error;
    }
};

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 6)  return 1;

    long long count = 0;

    if (!parseNumber(argv[2], count) ||
        count < 1 || count > 20000000LL)
    {
        std::fprintf(stderr, "Invalid N\n");
        return 1;
    }

    long long inputSeed = 1;

    if (argc > 3)
    {
        if (!parseNumber(argv[3], inputSeed) || inputSeed < 0)
        {
            std::fprintf(stderr, "Invalid seed\n");
            return 1;
        }
    }

    unsigned long long seed = static_cast<unsigned long long>(inputSeed);

    std::string pattern = (argc > 4) ? argv[4] : "random";

    if (pattern != "random" &&pattern != "asc" && pattern != "desc" && pattern != "zigzag")
    {
        std::fprintf(stderr, "Invalid pattern\n");
        return 1;
    }

    long long extraOperations = count;

    if (argc > 5)
    {
        if (!parseNumber(argv[5], extraOperations) ||
            extraOperations < 0 ||
            extraOperations > 100000000LL)
        {
            std::fprintf(stderr, "Invalid ops\n");
            return 1;
        }
    }

    randomState ^= seed * 0x9E3779B97F4A7C15ULL;

    if (randomState == 0) randomState = 88172645463325252ULL;

    for (int i = 0; i < 8; ++i) getRandomNumber();

    std::vector<long long> order;

    if (pattern == "random")
    {
        order.resize(static_cast<size_t>(count));

        for (long long i = 0; i < count; ++i) order[static_cast<size_t>(i)] = i;

        for (long long i = count - 1; i > 0; --i)
        {
            size_t j = static_cast<size_t>(getRandomNumber() % static_cast<unsigned long long>(i + 1));

            long long temp = order[static_cast<size_t>(i)];
            order[static_cast<size_t>(i)] = order[j];
            order[j] = temp;
        }
    }

    std::FILE *file = std::fopen(argv[1], "wb");

    if (file == nullptr)
    {
        std::fprintf(stderr, "Cannot open file\n");
        return 1;
    }

    FastOutput out(file);

    char header[256];

    int headerLength = std::snprintf(header, sizeof(header), "# generator: pattern=%s seed=%llu add=%lld ops=%lld \n", pattern.c_str(), seed, count, extraOperations);

    out.write(header, static_cast<size_t>(headerLength));

    const bool ascending = pattern == "asc";
    const bool descending = pattern == "desc";
    const bool zigzag = pattern == "zigzag";

    for (long long i = 0; i < count; ++i)
    {
        long long index;

        if (ascending) index = i;
        
        else if (descending)index = count - 1 - i;
        
        else if (zigzag) index = (i % 2 == 0)? i / 2: count - 1 - i / 2;
        
        else index = order[static_cast<size_t>(i)];
        
        long long key = 2 * index;

        out.writeAdd(key, i);
    }

    unsigned long long keyCount =
        static_cast<unsigned long long>(count);

    for (long long i = 0; i < extraOperations; ++i)
    {
        unsigned long long choice =
            getRandomNumber() % 100;

        long long evenKey =2 * static_cast<long long>(getRandomNumber() % keyCount);

        long long oddKey = evenKey + 1;

        if (choice < 30)
        {
            out.writeFind(evenKey);
        }
        else if (choice < 45)
        {
            out.writeFind(oddKey);
        }
        else if (choice < 65)
        {
            out.writeAdd(evenKey, count + i);
        }
        else if (choice < 75)
        {
            out.writeAdd(oddKey, count + i);
        }
        else if (choice < 90)
        {
            out.writeDelete(evenKey);
        }
        else
        {
            out.writeDelete(oddKey);
        }
    }

    bool writeSuccess = out.flush() && !out.hasError();

    if (std::fclose(file) != 0)
        writeSuccess = false;

    if (!writeSuccess)
    {
        std::fprintf(stderr, "Write error\n");
        return 1;
    }

    return 0;
}