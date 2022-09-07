package main

import "testing"

func TestFoundTheFastest(t *testing.T) {
	firstInput := []int{1, 2, 3, 4}
	firstIndex := len(firstInput) - 1

	firstResp := FoundTheFastest(firstInput)
	if firstResp.FirstIndex != firstIndex {
		t.Errorf("Unexpected value. Got %v want %v\n", firstResp.FirstIndex, firstIndex)
	}

	secondInput := []int{0, 0, 100, 100}
	secondResp := FoundTheFastest(secondInput)
	expFirst := 2
	expSecond := 3

	if secondResp.FirstIndex != expFirst && secondResp.SecondIndex != expSecond {
		t.Errorf("Unexpected values. Got %v Want %v Got %v Want %v\n", secondResp.FirstIndex, expFirst, secondResp.SecondIndex, expSecond)
	}
}
