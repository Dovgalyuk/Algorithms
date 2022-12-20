#ifndef BINARYHEAP_H
#define BINARYHEAP_H


#include <vector>
using namespace std;

template<typename T>
struct Heap
{
public:

    vector<T> tree;

    void Insert(T x)
    {
        tree.push_back(x);
        sift_up(GetSize() - 1);
    }

    T GetMax()
    {
        if (GetSize() > 0)
        {
            return tree[0];
        }
        else 
        { 
            return T();
        }
    }

    void RemoveMax()
    {
        if (GetSize() > 0)
        {
            tree[0] = tree.back();
            tree.pop_back();
            sift_down(0);
        }

    }

    bool Empty()
    {
        if (GetSize() != 0)
        {
            return false;
        }
        else { return true; }
    }

private:

    void sift_up(int v)
    {
        int p = (v - 1) / 2;
        T temp = tree[v];

        while (v > 0)
        {
            if (temp <= tree[p])
            {
                break;
            }
            else
            {
                tree[v] = tree[p];
                v = p;
                p = (p - 1) / 2;
            }
        }
        tree[v] = temp;
    }

    void sift_down(int v)
    {
       

        if (!Empty())
        {
            int l = 2 * v + 1;
            T temp = tree[v];
            while (l <= GetSize() - 1)
            {
                if (l < GetSize() - 1 && tree[l] < tree[l + 1])
                    l++;
                if (temp >= tree[l])
                    break;
                else
                {
                    tree[v] = tree[l];
                    v = l;
                    l = 2 * l + 1;
                }
            }
            tree[v] = temp;
        }
    }

    int GetSize()
    {
        return tree.size();
    }
};
#endif
