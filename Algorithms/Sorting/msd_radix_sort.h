#pragma once
#include "Algorithms/Sorting/insertion_sort.h"
#include <iostream>
#include <vector>
#include <map>
#include <vector>

/// <summary>
/// Helper function - puts values from bucket into other buckets depending on their n-th character (ch)
/// </summary>
/// <param name="bucket">Bucket to be sorted</param>
/// <param name="bucket_size">Size of bucket</param>
/// <param name="ch">n-th character to sort by</param>
void sort_buckets(std::string* bucket, const size_t& bucket_size, int ch) {

	if (bucket_size <= 1) return;
	else if (bucket_size <= 10) {
		insertion_sort(bucket, bucket_size);
		return;
	}

	std::map<char, std::vector<std::string>> buckets;
	for (int x = 0; x < bucket_size; x++) { //put value
		char key = (bucket[x].size() > ch) ? bucket[x][ch] : 0; // 0 carries strings that are too short
		buckets[key].push_back(bucket[x]);
	}

	int bucket_iter = 0;
	for (auto& b : buckets) {
		auto& vec = b.second;
		sort_buckets(vec.data(),vec.size(), ch + 1);
		for (int x = 0; x < vec.size(); x++)
			bucket[bucket_iter++] = vec[x];
	}
}

/// <summary>
/// Most Significant Digit radix sort algorithm specially designed to sort strings
/// </summary>
/// <param name="arr">Array of strings to sort</param>
/// <param name="arr_size">Array size</param>
void msd_radix_sort_string(std::string* arr, const size_t& arr_size) {
	int ch = 0; //actual character
	std::map<char, std::vector<std::string>> buckets;
	for (int x = 0; x < arr_size; x++) { //puts strings into proper buckets
		char key = (arr[x].size() > ch) ? arr[x][ch] : 0; // 0 carries strings that are too short
		buckets[key].push_back(arr[x]);
	}

	int arr_iter = 0;
	for (auto& bucket : buckets) {
		auto& vec = bucket.second;
		sort_buckets(vec.data(),vec.size(), ch + 1); //sort values inside buckets

		for (int x = 0; x < vec.size(); x++)
			arr[arr_iter++] = vec[x]; //put values from sorted buckets into output array
	}
}