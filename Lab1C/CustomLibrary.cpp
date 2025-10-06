#include "CustomLibrary.h"
#include "Array.h"

template<cl::concepts::primitiveType T>
void firstTask(std::fstream& file) {
	StaticSizeArray array = cl::createArrayFromFile<T>(file);

	auto [min, max] = cl::algorithms::findMinMaxIndex<T>(array.begin(), array.end());
	if (max < min) std::swap(max, min);
	auto result = cl::algorithms::sum<T>(array.begin() + min, array.begin() + max);

	std::cout << result << std::endl;
}

template<cl::concepts::primitiveType T>
void secondTask(std::fstream& file) {
	StaticSizeArray array = cl::createArrayFromFile<T>(file);

	auto [direction, moveStep] = cl::readDirectionFromFile(file);

	cl::algorithms::moveElements<T>(array.begin(), array.end(), direction, moveStep);
	std::cout << array << std::endl;
}

int main(int argc, char* argv[])
{
	auto currentPath = std::filesystem::current_path();
	
	if (argc < 2) {
		throw std::runtime_error("File path is required");
	}

	auto firstTaskFile = currentPath / argv[1];

	std::fstream file(firstTaskFile.c_str());
	
	firstTask<int>(file);
	secondTask<int>(file);

	return 0;
}
