#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
	explicit Array(size_t size)
	{
		if (size > 0)
		{
			length = size;
			arr = new Data[length];
		}
		else
			throw std::invalid_argument("array size is specified incorrectly");
	}

	Array(const Array &a)
	{
		length = a.length;
		arr = new Data[length];
		for (size_t i = 0; i < length; i++)
		{
			arr[i] = a.arr[i];
		}
	}

	Array &operator=(const Array &a)
	{
		if (this != &a)
		{
			length = a.length;
			arr = new Data[length];
			delete[] arr;
			for (size_t i = 0; i < length; i++)
			{
				arr[i] = a.arr[i];
			}
		}
		return *this;
	}

	~Array()
	{
		delete[] arr;
	}

	Data get(size_t index) const
	{
		if (index < length)
		{
			return arr[index];
		}
		else
			throw std::out_of_range("array subscript out of range");
	}

	void set(size_t index, Data value)
	{
		if (index < length)
		{
			arr[index] = value;
		}
		else
			throw std::out_of_range("array subscript out of range");
	}

	size_t size() const
	{
		return length;
	}

private:
	Data *arr;
	size_t length;
};

#endif
