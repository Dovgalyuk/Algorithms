#ifndef QUEUE_H
#define QUEUE_H
#include "vector.h"

// Queue
// Stores integer values inside
typedef int Data;

struct Queue
{
private:
	Vector* vector;
	unsigned long Head;
	unsigned long Tail;
public:
	Queue()
	{
		vector = new Vector();
		vector->Resize(10);
		Head = 0;
		Tail = 0;
	}
	~Queue()
	{
		delete vector;
	}
	void Insert(Data data)
	{
        if (Tail >= vector->GetCapacity() - 1 && Head == 0)
        {
            vector->Resize(vector->GetCapacity() * 2);
        }
        else if (Tail + 1 == Head)
        {
            Vector* resized_vec = new Vector();
            resized_vec->Resize(vector->GetCapacity() * 2);
            size_t new_index = 0;
            for (int i = Head; i < vector->GetSize(); i++)
            {
                resized_vec->Set(new_index, vector->GetValue(i));
                new_index++;
            }
            for (int i = 0; i <= Tail; i++)
            {
                resized_vec->Set(new_index, vector->GetValue(i));
                new_index++;
            }
            delete vector;
            vector = resized_vec;

            Head = 0;
            Tail = new_index + 1;
        }

        vector->Set(Tail, data);
        if (Tail >= vector->GetCapacity() - 1)
        {
            Tail = 0;
        }
        else
            Tail++;
}
Data Get()
{
	return vector->GetValue(Head);
}

void Remove()
{
	if (!IsEmpty)
	{
		if (Head >= vector->GetSize() - 1)
		{
			Head = 0;
		}
		else Head++;
	}
}

bool IsEmpty()
{
	return Tail == Head;
}
};

#endif
