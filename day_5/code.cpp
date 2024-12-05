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

		std::cout << "----------" << nr << "---------------" << std::endl;
		std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
		std::set<int> &roulset = roles.at(nr);
		for(auto it = numbers.begin(); it != numbers.end(); it++) {
			int current = *it;
			std::cout << "is in " << current;
			if (roulset.contains(current)) {
				std::cout << " --- yes" << std::endl;
				works = false;
				//auto tmp = numbers.end() - 1;
				//std::swap(it, tmp);
				//*it = nr;
				//numbers.pop_back();
				//numbers.push_back(current);
				it = std::rotate(it, it+1, numbers.end());
				std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
				std::cout << " --- moved back " << current << std::endl;
			} else {
				std::cout << " --- no" << std::endl;
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


// to low 4018