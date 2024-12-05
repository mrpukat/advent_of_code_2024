#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <utility>

#include "../utils.cpp"

void pre_process(std::map<int, std::set<int>> &roles, std::string &in) {

	int first{0};
	int second{0};
	bool read{false};
	aoc::for_all_numbers<int>(in, [&](int nr, int len, int){
		if (!read) {
			read = true;
			first = nr;
		} else {
			second = nr;
		}
	});

	if (roles.contains(first)) {
		roles[first].insert(second);
	} else {
		roles[first] = {second};
	}


}

int process(std::map<int, std::set<int>> &roles, std::string &in) {

	std::vector<int> numbers;
	bool works{true};

	aoc::for_all_numbers<int>(in, [&](int nr, int len, int){
		numbers.push_back(nr);
		if (!roles.contains(nr)) {
			return;
		}

		std::set<int> &roulset = roles.at(nr);
		for(auto it = numbers.begin(); it != numbers.end(); it++) {
			int current = *it;
			if (roulset.contains(current)) {
				works = false;
				std::iter_swap(it, --numbers.end());
			}
		}
	});


	int res{0};
	if (!works) {
		res = numbers.at(numbers.size()/2);
	}

	return res;
}

int main() {
	std::string line{};
	std::map<int, std::set<int>> roles{};
	std::ifstream file_in;

	bool setup{true};
	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			if (line.empty()) {
				setup = false;
				continue;
			}

			if (setup) {
				pre_process(roles,line);
			} else {
				sum += process(roles, line);
			}

		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}