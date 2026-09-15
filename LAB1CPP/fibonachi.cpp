#include <iostream>
#include <fstream>
#include <array.h>


int main(int argc, char *argv[]){
	std::ifstream file(argv[1]);
	
	int a;
	file >> a;
	Array *arr = array_create(a);
	
	if(a > 0)
		array_set(arr, 0, 0);
		
	if(a > 1)
		array_set(arr, 1, 1);
		
	for(int i =2; i < a; i++ ){
		int b = array_get(arr, i-1);
		int c = array_get(arr, i-2);
		
		array_set(arr, i, b+c);
	}
	
	for(int i = 0; i < a; i++){
			std::cout << array_get(arr, i);
			if(i < a -1)
				std::cout << " ";
	}
	
	std::cout << std::endl;
	
	array_delete(arr);
	
	return 0;

}
