#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

#include "../utils.cpp"
#include "aocMultimap.cpp"

void preProcess(std::string &in, std::multimap<std::string, std::string> &connections) {

	std::string comp1{""}, comp2{""};

	aoc::for_all_substrings(in, "-", [&](std::string &&computer){
		if (comp1.empty()) {
			comp1 = computer;
		} else {
			comp2 = computer;
		}
	});

	connections.insert({{comp1, comp2},{comp2,comp1}});

}

aoc::ull process(std::multimap<std::string, std::string> &connections) {

	std::set<std::set<std::string>> solutions;

	// Loop throw all keys (1)
	aoc::for_all_keys<std::string, std::string>(connections, [&](std::string key){

		if(key.at(0) != 't' || connections.count(key) < 2) {
			return;
		}

		// Loop trow all it connections (2)
		aoc::for_all_values<std::string, std::string>(connections, key,  [&](std::string value){

			if (key == value) {
				// dont connect back to origin
				std::cout << "?" << std::endl;
				return;
			}

			// Loop trow all it connections (3)
			aoc::for_all_values<std::string, std::string>(connections, value,  [&](std::string innerValue){

				if (key == innerValue) {
					return;
				}

				// find begining
				if(aoc::contains_value<std::string, std::string>(connections, innerValue, key)) {
						std::cout << key << "," << value << "," << innerValue << std::endl;
						solutions.insert({{key, value, innerValue}});
				}
			});
		});
	});

	return solutions.size();
}

int main() {

	std::string line{};
	std::ifstream file_in;

	std::multimap<std::string, std::string> connections; 

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			preProcess(line, connections);
		}

		file_in.close();
	}

	std::cout << "----------------" << std::endl;
	std::cout << process(connections) << std::endl;
	return 0;
}
