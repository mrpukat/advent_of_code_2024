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

std::set<std::string> step(std::multimap<std::string, std::string> &connections, std::set<std::string> &visited, std::set<std::string> path, std::string key) {
	visited.insert(key);

	for (const auto &node : path) {
		if(!aoc::contains_value<std::string, std::string>(connections, key, node)) {
			return path;
		}
	}

	path.insert(key);
	std::set<std::string> longestPaths = path;

	aoc::for_all_values<std::string, std::string>(connections, key, [&](std::string value){

		if(visited.contains(value)) {
			return;
		}

		std::set<std::string> tmpPath = step(connections, visited, path, value);
		if (longestPaths.size() < tmpPath.size()) {
			longestPaths = std::move(tmpPath);
		}
	});

	return longestPaths;
} 

std::set<std::string> process(std::multimap<std::string, std::string> &connections) {

	std::set<std::string> longestPaths{};

	aoc::for_all_keys<std::string, std::string>(connections, [&](std::string key){

		std::set<std::string> visited;
		std::set<std::string> tmpPath = step(connections, visited, {}, key);
		if (longestPaths.size() < tmpPath.size()) {
			longestPaths = std::move(tmpPath);
		}
	});

	return longestPaths;
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
	std::set<std::string> path = process(connections);
	for (const auto &computer : path) {
		std::cout << computer << ",";
	}
	std::cout << std::endl;
	return 0;
}
