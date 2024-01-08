/*
 Name: Nolan McKivergan
 Email: npmckivergan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 1
 Instructions to compile the program: g++ p1.cpp
 Instructions to execute the program: ./a.exe
*/

//Source for information on c++ std::sort: https://www.geeksforgeeks.org/internal-details-of-stdsort-in-c/

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

template <class RandomIt > constexpr void max_heapify (RandomIt first, int i, int size) {
    //Copied procedure from textbook, adapted for iterators
    int l = (2*i)+1;//Left child index
    int r = (2*i)+2;//Right child index
    int largest;
    //Find largest among parent, left, or right child
    if (l < size && *(first+l) > *(first+i)) {
       largest = l;
    } 
    else {
        largest = i;
    }
    if (r < size && *(first+r) > *(first+largest)) {
        largest = r;
    }
    //If the largest is a child, swap and continue to sift down
    if (largest != i) {
        std::iter_swap(first+i, first+largest);
        max_heapify(first, largest, size);
    }
}

template <class RandomIt > constexpr void build_max_heap (RandomIt first, RandomIt last) {
    //Copied procedure from textbook, adapted for iterators
    int heap_size = std::distance(first, last);
    for (int i = (heap_size / 2) - 1; i > -1; i--) {
        max_heapify(first, i, heap_size);
    }
}

template <class RandomIt > constexpr void heapsort (RandomIt first, RandomIt last) {
    //Copied procedure from textbook, adapted for iterators
    build_max_heap(first, last);//Create max heap
    //Repeatedly remove max element and sift down last element
    for (int i = std::distance(first, last) - 1; i > 0; i--) {
        std::iter_swap(first, first+i);
        max_heapify(first, 0, i);
    }
}

template<class RandomIt > constexpr auto partition (RandomIt first, RandomIt last) {
    //Copied procedure from textbook, adapted for iterators
    int r = std::distance(first, last) - 1;//Index of last element
    std::iter_swap(first+((r+1)/2), last-1);//Swap middle element into last space to use value of middle element as pivot
    int x = r;//Index of pivot value (i.e. now at the end)
    int i = -1;//i begins one behind first
    //Partition array
    for (int j = 0; j < r; j++) {
        if (*(first + j) <= *(first + x)) {
            i++;
            std::iter_swap(first+i, first+j);
        }
    }
    //Swap pivot into place
    std::iter_swap(first+i+1, first+r);
    //Return new location of pivot
    return i + 1;
}

template<class RandomIt > constexpr void quicksort (RandomIt first, RandomIt last) {
    //Copied procedure from textbook, adapted for iterators
    if (first < last - 1) {
        int q = partition(first, last);//Partition and return index.  q is now in its correct location.
        quicksort(first, first+q);//Quicksort lower half
        quicksort(first+q+1, last);//Quicksort upper half
    }
}


//Main copied from perftest file
int main(int argc, char *argv[]) {

    //Replace std::sort with heapsort or quicksort to test

	std::chrono::duration<double> timetaken[3][3];
	std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
	std::cout << "\t\tCase 1\tCase 2\tCase 3" << std::endl;
	for (int size = 10; size <= 100000000; size *= 10) {
	
		int *a = new int[size];

		// repeat each case for three times 
		for (int i = 0; i < 3; i++) {
			std::generate(a, a+size, std::rand);

			/* Case 1: sorting random values */
			auto starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			auto endtime = std::chrono::steady_clock::now();
			timetaken[i][0] = endtime - starttime;

			/* Case 2: sorting data that is already sorted */
			starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][1] = endtime - starttime;

			/* Case 3: sorting data that is in reverse sorted order */
			std::reverse(a, a+size);
			starttime = std::chrono::steady_clock::now();
			std::sort(a, a+size);
			endtime = std::chrono::steady_clock::now();
			timetaken[i][2] = endtime - starttime;
		}

		// print the average time of three runs
		std::cout << size << "\t\t";
		std::cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count())/3.0 << "\t";
		std::cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count())/3.0 << "\t";
		std::cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count())/3.0 << std::endl;

		delete[] a;
	}

	return 0;
}
