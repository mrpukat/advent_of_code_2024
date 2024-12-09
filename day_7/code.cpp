#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

#include "../utils.cpp"


const std::vector<char> operators = {'+', '*', '|'};


void all_results(const std::vector<unsigned long long> &values, int index, unsigned long long res, unsigned long long goal, std::function< void() > f, std::string debug) {

	//std::cout << index << " : " << res << " : " << goal << std::endl;

	if(index == values.size()) {
		debug.push_back('=');
		debug += std::to_string(res);
		//std::cout << debug << std::endl;
		if (res == goal) {
			f();
		}
		return;
	}


	for (char c : operators) {
		//std::cout << index << " - " << c << " - " << res << std::endl;
		unsigned long long now_res{res};
		std::string new_debug {debug};
		new_debug.push_back(c);
		new_debug += std::to_string(values.at(index));
		if (c == '+') {
			now_res += values.at(index);
		} else if (c == '*') {
			now_res *= values.at(index);
		} else {
			now_res = stoull(std::to_string(now_res) + std::to_string(values.at(index)));
		}

		all_results(values, index + 1, now_res, goal, f, new_debug);
	}

}

unsigned long long process(std::string &in) {


	bool first{true};
	bool works{false};
	unsigned long long sum{0};
	std::vector<unsigned long long> values;
	aoc::for_all_numbers<unsigned long long>(in, [&](unsigned long long nr, int, int){
		if (first) {
			first = false;
			sum = nr;
		} else {
			values.push_back(nr);
		}
	});

	unsigned long long res{values.at(0)};
	values.erase(values.begin());
	std::cout << "start: " << sum << std::endl;
	all_results(values, 0, res, sum, [&](){
		works = true;
		//std::cout << "Works!" << std::endl;
	}, std::to_string(res));

	return works ? sum : 0;
}

int main() {
	std::string line{};
	std::ifstream file_in;

	unsigned long long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line);
			std::cout << "=====================\n";
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}