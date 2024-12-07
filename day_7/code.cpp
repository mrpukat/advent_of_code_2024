#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

#include "../utils.cpp"

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

	
	//std::copy(values.begin(), values.end(), std::ostream_iterator<unsigned long long>(std::cout, " "));
	//std::cout << std::endl;


	for (int i{0}; i < values.size(); ++i) {
		std::vector<char> operations;
		for (int j{1}; j < values.size(); ++j) {
			for (int k{1}; k < values.size(); ++k) { 
				if (i < j) {
					operations.push_back('+');
				} else {
					operations.push_back('*');
				}

			}
		}
		std::cout << "------------------------------\n";
		
		//std::copy(operations.begin(), operations.end(), std::ostream_iterator<char>(std::cout, " "));
		//std::cout << std::endl;

		do {
			std::cout << sum << " ?=? " << values.at(0);
			unsigned long long res{values.at(0)}; // Move
			for(int k{1}; k < values.size(); ++k) {
				if (operations.at(k-1) == '+') {
					std::cout << " + " << values.at(k);
					res += values.at(k);
				} else {
					std::cout << " * " << values.at(k);
					res *= values.at(k);
				}
			}
			std::cout << " == " << res << "\n";

			if (res == sum) {
				works = true;
				std::cout << "Works" << std::endl;
				break;
			}
			//std::copy(operations.begin(), operations.end(), std::ostream_iterator<char>(std::cout, " "));
			//std::cout << std::endl;
		} while (std::next_permutation(operations.begin(), operations.end()));

		if (works) {
			break;
		}
	}

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



// TO low 1320637061