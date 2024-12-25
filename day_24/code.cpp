#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

#include "../utils.cpp"

void preProcess(std::string &in, std::map<std::string, bool> &inputs) {

	std::string value{""};
	bool input;

	aoc::for_all_substrings(in, ":", [&](std::string &&sub){
		if (value.empty()) {
			value = sub;
		} else {
			if(sub.at(1) == '1') {
				input = true;
			} else {
				input = false;
			}
		}
	});

	inputs.insert({value, input});

}

bool gridPass(bool one, bool two, const std::string &grid) {
	if (grid == "AND") {
		return one && two;
	}

	if (grid == "OR") {
		return one || two;
	}

	return one != two;
}

std::pair<std::string, bool> processGrid(std::string in, const std::map<std::string, bool> &maping) {

	std::string iOne, op, iTwo, out;
	int i{0};
	aoc::for_all_substrings(in, " ", [&](std::string sub){
		switch (i)
		{
		case 0:
			iOne = sub;
			break;
		case 1:
			op = sub;
			break;
		case 2:
			iTwo = sub;
			break;
		case 4:
			out = sub;
			break;
		
		default:
			break;
		}

		++i;
	});

	//std::cout << "Read: " << iOne << " " << op << " " << iTwo << " -> " << out << std::endl;

	if(!maping.contains(iOne)) {
		return {{},{}};
	}
	if(!maping.contains(iTwo)) {
		return {{},{}};
	}

	return {out, gridPass(maping.at(iOne), maping.at(iTwo), op)};

}

aoc::ull process(std::vector<std::string> &grids, std::map<std::string, bool> &inputs) {

	bool process{false};
	auto it = grids.begin();
	while(it != grids.end()) {
		//std::cout << *it << std::endl;

		auto thing = processGrid(*it, inputs);
		if(!thing.first.empty()) {
			//std::cout << "Process" << std::endl;
			inputs.insert(thing);
			it = grids.erase(it);
			process = true;
		} else {
			++it;
		}

		if(it == grids.end() && !grids.empty() && process) {
			//std::cout << "Repeate" << std::endl;
			it = grids.begin();
		}
	}

	std::set<std::string> tmp;
	auto mit = inputs.begin();
	for(;mit != inputs.end(); ++mit) {
		//std::cout << mit->first << " " << mit->second << std::endl;
		if (mit->first.at(0) == 'z') {
			tmp.insert(mit->first);
		}
	}

	aoc::ull res{0};
	int i{0};
	for(auto str : tmp) {
		std::cout << inputs.at(str);
		if (inputs.at(str)) {
			res += std::pow(2,i);
		}
		++i;
	}
	std::cout << std::endl;
	return res;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	std::vector<std::string> grids;
	std::map<std::string, bool> inputs; 
	//std::map<std::string, bool> outputs; 

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		bool input{true};
		while(getline(file_in, line)) {
			if (line.empty()) {
				input = false;
				continue;
			}

			if(input) {
				preProcess(line, inputs);
			} else {
				grids.push_back(line);
			}
		}

		file_in.close();
	}

	std::cout << "----------------" << std::endl;
	std::cout << process(grids, inputs) << std::endl;
	return 0;
}
