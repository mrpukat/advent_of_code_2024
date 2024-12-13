#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

#include "../utils.cpp"


std::map<unsigned long long, unsigned long long> pre_process(std::string &in) {
	std::map<unsigned long long, unsigned long long> stones;
	aoc::for_all_numbers<unsigned long long>(in, [&](unsigned long long nr, int, int){
		if (stones.contains(nr)) {
			stones[nr]++;
		} else {
			stones[nr] = 1;
		}
	});

	return stones;
}


void process(std::map<unsigned long long, unsigned long long> &stoneMap) {

		std::map<unsigned long long, unsigned long long> newStoneMap;

		for (auto it = stoneMap.begin(); it != stoneMap.end(); ++it) {

			std::string tmp = std::to_string(it->first);
			if (it->first == 0) {
				if (newStoneMap.contains(1)) {
					newStoneMap[1] += it->second;
				} else {
					newStoneMap[1] = it->second;
				}
			} else if ( tmp.length() % 2 == 0) {
				unsigned long long first = stoull(tmp.substr(0, tmp.length()/2));
				if (newStoneMap.contains(first)) {
					newStoneMap[first] += it->second;
				} else {
					newStoneMap[first] = it->second;
				}
				unsigned long long second = stoull(tmp.substr(tmp.length()/2, tmp.length()));
				if (newStoneMap.contains(second)) {
					newStoneMap[second] += it->second;
				} else {
					newStoneMap[second] = it->second;
				}
			} else {
				if (newStoneMap.contains(it->first*2024)) {
					newStoneMap[it->first*2024] += it->second;
				} else {
					newStoneMap[it->first*2024] = it->second;
				}
				
			}
		}

	stoneMap = std::move(newStoneMap);
}

int main() {

	std::string line{};
	std::map<unsigned long long, unsigned long long> stoneMap;
	std::ifstream file_in;

	unsigned long long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			stoneMap = pre_process(line);
		}
		file_in.close();
	}

	for(int i{0}; i < 75; ++i) {
		process(stoneMap);
	}

	for (auto it = stoneMap.begin(); it != stoneMap.end(); ++it) {
		sum += it->second;
	}

	std::cout << "================" << std::endl;
	std::cout << sum << std::endl;
	return 0;
}
