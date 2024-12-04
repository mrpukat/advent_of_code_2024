#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "../utils.cpp"

void pre_process(std::string &in, std::vector<int> &l, std::vector<int> &r) {

	aoc::for_all_numbers<int>(in, [&](int nr, int len, int){
		if (len == 0){
			l.push_back(nr);
		} else {
			r.push_back(nr);
		}
	});

}

int process(std::vector<int> &l, std::vector<int> &r) {

	int sum{0};

	for (int el : l) {
		int sim{0};
		for (int cop : r) {
			if (cop > el) {
				break;
			}
			if (el == cop) {
				sim++;
			}
		}
		sum += el*sim;
	}

	return sum;
}


int main() {
	std::string line;
	std::ifstream file_in;

	std::vector<int> left;
	std::vector<int> right;

	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			pre_process(line, left, right);
		}
		file_in.close();
	}

	if (left.size() != right.size()) {
		throw "bad";
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	std::cout << process(left, right) << std::endl;

	return 0;
}
