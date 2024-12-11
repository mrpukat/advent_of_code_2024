#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "../utils.cpp"
#include "../grid.cpp"


std::vector<long long> pre_process(std::string &in) {
	std::vector<long long> decoded;
	//std::string decoded;
	for (int i{0}; i < in.size(); ++i) {
		for (int j{0}; j < in.at(i) -'0'; ++j) {
			if (i % 2 == 0){
				decoded.push_back(i/2);
			} else {
				decoded.push_back(-1);
			}
		}
	}
	//std::cout << decoded << std::endl;
	//std::copy(decoded.begin(), decoded.end(), std::ostream_iterator<long long>(std::cout, " "));
	//std::cout << std::endl;
	return decoded;
}

long long process(std::vector<long long> &in) {

	// ..k..p.....j..i.. 

	//std::cout << in.size() << std::endl;

	for (unsigned long long i{in.size()-1}; i > 0; --i) {
		if (in.at(i) != -1) {
			unsigned long long j{i};
			for (;j > 0 && in.at(j) == in.at(i); --j) {};
			++j;
			//std::cout << "Rigth: " << i << " " <<  j << " : " << in.at(i) << " "<< in.at(j) << std::endl;

			for (unsigned long long k{0}; k < j; ++k) {
				if (in.at(k) == -1){
					unsigned long long p{k};
					for (;p < in.size() && in.at(p) == in.at(k); ++p) {};
					--p;
					//std::cout << "Left: " << k << " " <<  p << " : " << in.at(k) << " "<< in.at(p) << std::endl;
					if (p - k >= i - j) {
						for (unsigned long long a{0}; a <= i - j; ++a) {
							in.at(k + a) = in.at(j + a);
							in.at(j + a) = -1;
						}
						//std::cout << in << std::endl;
						//std::copy(in.begin(), in.end(), std::ostream_iterator<long long>(std::cout, " "));
						//std::cout << std::endl;
						break;
					}
				}
			}
			i = j;
		}
	}

	//std::cout << in << std::endl;
	//std::copy(in.begin(), in.end(), std::ostream_iterator<long long>(std::cout, " "));
	//std::cout << std::endl;

	long long sum{0};
	for (long long i{0}; i < in.size(); ++i) {
		if (in.at(i) != -1) {
			long long tmp = i*(in.at(i));
			sum += tmp;
			std::cout << i << " * " << in.at(i) << " = " << tmp << " (" << sum << ")" << std::endl;
		}
	}

	return sum;
}

int main() {

	std::string line{};
	std::string compleat;
	std::ifstream file_in;

	std::vector<long long> v{};

	long long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			v = pre_process(line);
			sum += process(v);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;
	return 0;
}
