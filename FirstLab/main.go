package main

import (
	"fmt"
	"math/rand"
	"time"
)

type Resp struct {
	FirstSpeed  int
	FirstIndex  int
	SecondSpeed int
	SecondIndex int
}

func FoundTheFastest(arr []int) Resp {
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

	arr := make([]int, length)

	rand.Seed(time.Now().UnixNano())

	for i := range arr {
		arr[i] = rand.Intn(100)
	}
	fmt.Println(arr)
	FoundTheFastest(arr)
}
