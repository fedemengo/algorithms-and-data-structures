#include <iostream>
#include <chrono>
#include <vector>
#include "heap_sort/heap_sort.hpp"
#include "insertion_sort/insertion_sort.hpp"
#include "merge_sort/merge_sort.hpp"
#include "quick_sort/quick_sort.hpp"
#include "selection_sort/selection_sort.hpp"

int main() {
	const int SIZE = 50000;
	std::vector<int> v;

	for(int i=0; i<SIZE; ++i)
		v.push_back(rand() % (SIZE * 100));

	std::vector<int> v1(v), v2(v), v3(v), v4(v), v5(v);
	auto start = std::chrono::high_resolution_clock::now();
	selection_sort(v5);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << "\tSELECTION SORT" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	insertion_sort(v2);
	end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << "\tINSERTION SORT" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	merge_sort(v3);
	end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << "\tMERGE SORT" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	heap_sort(v1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << "\tHEAP SORT" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	quick_sort(v4);
	end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << "\tQUICK SORT" << std::endl;
}
