#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

#include "../utils.cpp"

void preProcess(std::string &in, std::vector<int> &fit) {

	assert(in.length() == fit.size());

	for(int i{0}; i < in.length(); ++i) {
		if (in.at(i) == '#') {
			fit.at(i)++;
		}
	}

}

aoc::ull process(const std::vector<std::vector<int>> &keys, const std::vector<std::vector<int>> &locks) {

	aoc::ull sum{0};
	bool fits{true};
	for(const auto &key : keys) {
		for(const auto &lock : locks) {
			for(int i{0}; i < 5; ++i) {
				if(key.at(i) + lock.at(i) > 7) {
					fits = false;
					break;
				}
			}
			if(fits) {
				/*
				std::copy(key.begin(), key.end(), std::ostream_iterator<int>(std::cout, " "));
				std::cout << std::endl;
				std::copy(lock.begin(), lock.end(), std::ostream_iterator<int>(std::cout, " "));
				std::cout << std::endl;
				*/
				++sum;
			}
			fits = true;
		}
	}

	return sum;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	std::vector<std::vector<int>> keys;
	std::vector<std::vector<int>> locks;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		bool first{true}, key{false};
		while(getline(file_in, line)) {
				if(line.empty()) {
					first = true;
				} else {
					if(first) {
						if(line.at(0) != '#') {
							keys.push_back({0,0,0,0,0});
							key = true;
						} else {
							locks.push_back({0,0,0,0,0});
							key = false;
						}
					}
					if (key) {
						preProcess(line, keys.back());
					} else {
						preProcess(line, locks.back());
					}
					first = false;
				}
		}

		file_in.close();
	}

	std::cout << keys.size() << std::endl;
	std::cout << locks.size() << std::endl;

	std::cout << "----------------" << std::endl;
	std::cout << process(keys, locks) << std::endl;
	return 0;
}
