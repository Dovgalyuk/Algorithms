package main

import (
	"C"
	"fmt"
	"math/rand"
	"time"
	"unsafe"
)

/*
// create array
Array *array_create(size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
   // return (Data)0;
    if (index < 0 || index >= array_size(arr))
        return 0;
    else
        return arr->_arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < 0 || index >= array_size(arr))
        return;
    else
        arr->_arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    //return 0;
    return arr->_n;
}
*/

type Resp struct {
	FirstSpeed  int
	FirstIndex  int
	SecondSpeed int
	SecondIndex int
}

func FoundTheFastest(arr []*Array) Resp {
	var temp, firstLargest, firstIndex, secondLargest, secondIndex int
	var flag bool

	for idx, val := range arr {
		if val > temp {
			temp = val
			firstLargest = temp
			firstIndex = idx
		} else if val >= temp {
			temp = val
			secondLargest = temp
			secondIndex = idx
			flag = true
		}
	}

	if flag {
		fmt.Printf("Первая встреченная машина с макс скоростью и ее номер: %v\n", firstIndex)
		fmt.Printf("Номер последней машины с макс скоростью: %v\n", secondIndex)
		return Resp{
			FirstSpeed:  firstLargest,
			FirstIndex:  firstIndex,
			SecondSpeed: secondLargest,
			SecondIndex: secondIndex,
		}
	} else {
		fmt.Printf("Номер машины с макс скоростью: %v\n", firstIndex)
		return Resp{
			FirstSpeed: firstLargest,
			FirstIndex: firstIndex,
		}
	}

}

func main() {
	var length int
	fmt.Printf("Enter Length Of The Array: ")
	fmt.Scanln(&length)

	arr := C.array_create(uint32(length), func(p unsafe.Pointer) {})

	rand.Seed(time.Now().UnixNano())

	for i := 0; i < length; i++ {
		C.array_set(arr, uint32(i), rand.Intn(100))
	}
	fmt.Println(arr)
	FoundTheFastest(arr)
}
