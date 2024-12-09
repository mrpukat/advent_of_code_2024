#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "../utils.cpp"
#include "../grid.cpp"

unsigned long long process(std::string &in) {

	unsigned long long sum{0}, m{0};
	unsigned long long size = in.size();
	for (unsigned long long i{0}, j{size-1}; i <= j; ) {
		//std::cout << i << " (" << in.at(i) << ") " << j << " (" << in.at(j) << ")" <<  std::endl;

		if (i % 2 == 0) {
			// Go throw normaly on the left
			//std::cout << "Left: " << in.at(i) << " index: " << i << " id: " << i/2 << " m: " << m << std::endl;
			for (int k{0}; k < in.at(i) - '0'; ++k) {
				unsigned long long tmp = m*(i/2);
				sum += tmp;
				std::cout << m << " * " << i/2 << " = " << tmp << " (" << sum << ")" << std::endl;
				++m; // Next setp (expanded)
			}
		} else if (j != i) {
			//std::cout << "Rigth: " << in.at(j) << " index: " << j << " id: " << j/2 << " m: " << m << std::endl;
			int k{0};
			for (; k < in.at(i) - '0';) {
				unsigned long long tmp = m*(j/2);
				sum += tmp;
				std::cout << m << " * " << j/2 << " = " << tmp << " (" << sum << ")" << std::endl;
				++m; // next setp (expanded)
				++k;

				if(k == in.at(j) - '0') {
					int need = in.at(i) - '0';
					in[i] = (need - k) + '0'; // If negativ bugg
					--i;
					break;
				}
			}
			int need = in.at(j) - '0';
			in[j] = (need - k) + '0'; // If negativ bugg
		}

		++i; // Next step (encoded)

		// Setup for next loop
		if (j % 2 != 0) {
			--j; // is this used?
		}

		while (in.at(j) == '0') {
			j -= 2;
		}


		//std::cout << "--------------------" << std::endl;

		//std::cout << in << std::endl;

		//std::cout << "--------------------" << std::endl;
	}

	return sum;
}

int main() {

	std::string line{};
	std::string compleat;
	std::ifstream file_in;

	aoc::grid grid{};

	unsigned long long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;
	return 0;
}
