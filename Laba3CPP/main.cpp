#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"
#include "vector.h"
using namespace std;

typedef size_t SubstanceId;
typedef Vector<string> SubstanceNames;
typedef Vector<size_t> Indices;
typedef Vector<bool> Flags;
const size_t noReaction = string::npos;

struct Reaction
{
    SubstanceId to;
    size_t next;
};

typedef Vector<Reaction> Reactions;

template <typename Data>
void append(Vector<Data> &items, Data value)
{
    size_t index = items.size();
    items.resize(index + 1);
    items.set(index, value);
}

SubstanceId substanceId(const string &name, SubstanceNames &names,
                        Indices &firstReaction, Indices &lastReaction)
{
    for (SubstanceId id = 0; id < names.size(); ++id)
    {
        if (names.get(id) == name)
            return id;
    }

    SubstanceId id = names.size();
    append(names, name);
    append(firstReaction, noReaction);
    append(lastReaction, noReaction);
    return id;
}

void addReaction(SubstanceId from, SubstanceId to, Reactions &reactions,
                 Indices &firstReaction, Indices &lastReaction)
{
    size_t index = reactions.size();
    Reaction reaction = {to, noReaction};
    append(reactions, reaction);

    size_t previous = lastReaction.get(from);
    if (previous == noReaction)
        firstReaction.set(from, index);
    else
    {
        Reaction previousReaction = reactions.get(previous);
        previousReaction.next = index;
        reactions.set(previous, previousReaction);
    }
    lastReaction.set(from, index);
}

void printObtained(SubstanceId initial, const SubstanceNames &names,
                   const Indices &firstReaction, const Reactions &reactions)
{
    Queue<SubstanceId> queue;
    Flags visited;
    Flags obtained;
    visited.resize(names.size());
    obtained.resize(names.size());
    queue.insert(initial);
    visited.set(initial, true);

    while (!queue.empty())
    {
        SubstanceId current = queue.get();
        queue.remove();

        for (size_t i = firstReaction.get(current); i != noReaction; i = reactions.get(i).next)
        {
            SubstanceId product = reactions.get(i).to;
            if (!obtained.get(product))
            {
                cout << names.get(product) << '\n';
                obtained.set(product, true);
            }

            if (!visited.get(product))
            {
                visited.set(product, true);
                queue.insert(product);
            }
        }
    }
}

string trim(const string &text)
{
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        cerr << "Expected one input file\n";
        return 1;
    }

    ifstream file;
    istream *input = &cin;
    if (argc == 2)
    {
        file.open(argv[1]);
        if (!file)
        {
            cerr << "Cannot open input file\n";
            return 1;
        }
        input = &file;
    }

    string start;
    if (!getline(*input, start) || trim(start).empty())
    {
        cerr << "Missing initial substance\n";
        return 1;
    }
    start = trim(start);

    SubstanceNames names;
    Indices firstReaction;
    Indices lastReaction;
    Reactions reactions;
    SubstanceId initial = substanceId(start, names, firstReaction, lastReaction);
    string line;
    while (getline(*input, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        size_t arrow = line.find("->");
        if (arrow == string::npos || line.find("->", arrow + 2) != string::npos)
        {
            cerr << "Invalid reaction: " << line << '\n';
            return 1;
        }

        string from = trim(line.substr(0, arrow));
        string to = trim(line.substr(arrow + 2));
        if (from.empty() || to.empty())
        {
            cerr << "Invalid reaction: " << line << '\n';
            return 1;
        }
        SubstanceId fromId = substanceId(from, names, firstReaction, lastReaction);
        SubstanceId toId = substanceId(to, names, firstReaction, lastReaction);
        addReaction(fromId, toId, reactions, firstReaction, lastReaction);
    }

    printObtained(initial, names, firstReaction, reactions);
}
