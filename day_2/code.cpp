#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

int pre_process(std::string &in) {

	std::vector<int> list;

	aoc::for_all_numbers<int>(in, [&](int nr, int len, int){
		list.push_back(nr);
	});

	for (int j{0}; j < list.size(); ++j) {
		int last{0};
		bool works{true};
		bool overide{true};
		bool increase{false};
		bool first{true};
		bool second{true};
		std::cout << "Skips: " << j << std::endl;
		for (int i{0}; i < list.size(); ++i) {
			if (!works || j==i){continue;}
			int nr = list.at(i);
			if (first) {
				first = false;
				last = nr;
			} else {
				if (second) {
					second = false;
					increase = last < nr;
				}

				std::cout << "nr " << nr << " last " << last << std::endl;
				if (increase && (nr - last > 3 || nr - last < 1)) {
					std::cout << "falise" << std::endl;
					works = false;
					continue;
				}
				else if (!increase) {
					if (nr - last < -3 || nr - last > -1) {
						std::cout << "falise" << std::endl;
						works = false;
						continue;
					}
				}

				last = nr;
			}
		}
		if (works) {
			return 1;
		}
	}

	return 0;
}


int main() {
	std::string line;
	std::ifstream file_in;

	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += pre_process(line);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}


// 612 bad