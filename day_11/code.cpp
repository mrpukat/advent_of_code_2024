#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <queue>

#include "../utils.cpp"


std::vector<unsigned long long> pre_process(std::string &in) {
	std::vector<unsigned long long> stones;
	aoc::for_all_numbers<unsigned long long>(in, [&](unsigned long long nr, int, int){
		stones.push_back(nr);
	});

	return stones;
}


void process(unsigned long long stone, int depth, unsigned long long &sum) {
		//std::cout << depth << std::endl;
		if (depth == 0) {
			//std::cout << stone << std::endl;
			++sum;
			return;
		}

		--depth;
		std::string tmp = std::to_string(stone);
		if (stone == 0) {
			process(1, depth, sum);
		} else if ( tmp.length() % 2 == 0) {
			//std::cout << "increase" << std::endl;
			process(stoull(tmp.substr(0, tmp.length()/2)),depth, sum);
			process(stoull(tmp.substr(tmp.length()/2, tmp.length())),depth, sum);
		} else {
			process(stone*2024, depth, sum);
		}
}

int main() {

	std::string line{};
	std::vector<unsigned long long> stones;
	std::ifstream file_in;

	unsigned long long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			stones = pre_process(line);
		}
		file_in.close();
	}

	for(auto s : stones) {
		process(s, 25, sum);
		std::cout << "------------------- (" << sum << ")" << std::endl;
	}

	std::cout << "================" << std::endl;
	std::cout << sum << std::endl;
	return 0;
}
