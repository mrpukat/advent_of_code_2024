#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

#include "../utils.cpp"

void pre_process(std::string &in) {
	in += "do()";
	in = std::regex_replace(in, std::regex("don't\\(\\).*?do\\(\\)"), "do()");
}

int process(std::string &in) {

	std::regex words_regex("mul\\(\\d+,\\d+\\)");

    auto words_begin = std::sregex_iterator(in.begin(), in.end(), words_regex);
    auto words_end = std::sregex_iterator();
 
	int resout{0};
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();
		
		int j{0};
		int res{0};
		aoc::for_all_numbers<int>(match_str, [&](int nr, int len, int){
			if (j == 0) {
				res = nr;
			} else {
				res *= nr;
			}
			j++;
		});
		resout += res;
		
		
    }

	return resout;
}

int main() {
	std::string line{};
	std::string compleat;
	std::ifstream file_in;

	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			compleat += line;
		}
		file_in.close();
	}


	pre_process(compleat);
	sum += process(compleat);
	std::cout << sum << std::endl;

	return 0;
}
