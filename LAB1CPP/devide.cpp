#include <fstream>
#include <iostream>
#include <array.h>

int main(int argc, char *argv[]){
	
	std::ifstream file(argv[1]);
	
	int a;
	file >> a;
	
	Array *arr = array_create(a);
	bool first = true;
	
	for(int i = 0; i < a; i++){
		int x;
		file >> x;
		array_set(arr, i, x);
	}	
	
	for(int i = 0; i < a; i++){
		bool ok = true;
		
		for(int j = 0; j < a; j++){
			if(j == i)
				continue;
			int b = array_get(arr, i);
			int c = array_get(arr, j);
			
			if(c != 0 && b%c == 0){
				ok = false;
				break;
			}
		}
		
		
		
		if(ok){
			if(!first)
				std::cout << " ";

			std::cout << array_get(arr, i);
			first = false;
		}
	}
	
	std::cout << std::endl;
	
	array_delete(arr);	
	return 0;
		
}
