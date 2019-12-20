#include <functional>

template <typename T>
class Pair
{
public:
	Pair(T key);
	const T& get_key();
	size_t get_hash();
private:
	T key;
	size_t hashCode;
};

template<typename T>
inline Pair<T>::Pair(T key)
{
	this->key = key;
	this->hashCode = std::hash<T>{}(key);
}

template<typename T>
inline const T& Pair<T>::get_key()
{
	return key;
}

template<typename T>
inline size_t Pair<T>::get_hash()
{
	return hashCode;
}