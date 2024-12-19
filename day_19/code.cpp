#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

#include "../utils.cpp"

void preProcess(std::string &in, std::vector<std::string> &towels) {
	aoc::for_all_substrings(in, ", ", [&](std::string &&t){
		towels.push_back(t);
		//std::cout << t << std::endl;
	});
}

aoc::ull process(std::string in, std::vector<std::string> &towels, std::unordered_map<std::string, aoc::ull> &memory) {
	if (in.empty()) {	
		return 1;
	}

	if (memory.contains(in)) {
		return memory[in];
	}

	memory[in] = 0;


	for (const std::string &t : towels) {
		unsigned long len{t.length()};
		if(len > in.length()) {
			continue;
		}

		std::string start = in.substr(0,len);
		std::string rest = in.substr(len, std::string::npos);
		//std::cout << in << " " << len << " " << start << " " << rest << std::endl;

		if (start == t) {
			memory[in] += process(rest, towels, memory);
		}

		//std::cout << in << " " << memory[in] << std::endl;
	}


	return memory[in];
}


int main() {

	std::string line{};
	std::ifstream file_in;

	std::vector<std::string> towels;
	std::unordered_map<std::string, aoc::ull> memory;
	aoc::ull sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		getline(file_in, line);
		preProcess(line, towels);
		getline(file_in, line);
		std::cout << "--------------------------" << std::endl;

		while(getline(file_in, line)) {
			sum += process(line, towels, memory);
		}

		file_in.close();
	}

	std::cout << sum << std::endl;
	return 0;
}
