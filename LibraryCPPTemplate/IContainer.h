template <typename T>
struct IContainer
{
	virtual T Add(T key, T value) = 0;
	virtual T Remove(T key) = 0;
	virtual T Find(T key) = 0;
};