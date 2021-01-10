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
	int Head;
	int Tail;
public:
	Queue()
	{
		vector = new Vector();
		vector->Resize(1);
		Head = 0;
		Tail = 0;
	}
	~Queue()
	{
		delete vector;
	}
	void Insert(Data data)
	{
		int vec_size = vector->GetSize();
		if (Tail >= (vec_size - 1))
		{
			vector->Resize(vector->GetSize() * 2);
		}

		vector->Set(Tail, data);

		Tail++;
	}
	Data Get()
	{
		return vector->GetValue(Head);
	}

	void Remove()
	{
		Head++;
	}

	bool IsEmpty()
	{
		return Tail == Head;
	}
};

#endif
