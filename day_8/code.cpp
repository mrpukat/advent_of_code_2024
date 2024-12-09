#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"

int process(aoc::grid &grid) {

	aoc::grid saved = grid;

	std::map<char, std::vector<std::pair<int, int>>> coords;

	for (int y{0}; y < grid.higth(); ++y) {
		for (int x{0}; x < grid.with(); ++x) {
			char c = grid.at(x, y);
			if (c != '.') {
				if (coords.contains(c)) {
					coords.at(c).push_back({x,y});
				} else {
					coords[c] = {{x,y}};
				}
			}
		}		
	}

	for (auto it = coords.begin(); it != coords.end(); it++)
	{

		// Main logic
		// Need to compair all points with all other


		for (auto fpair : it->second) {
			for (auto spair : it->second) {
				if (fpair != spair) {
					int dx = fpair.first - spair.first;
					int dy = fpair.second - spair.second;
					int x = fpair.first;
					int y = fpair.second;
					while (saved.inside(x,y)) {
						saved.set(x,y,'#');
						x += dx;
						y += dy;
					}
				}
			}
		}
		



	}


	//grid.print();
	std::cout << "----------\n";
	//saved.print();
	int sum{0};
	saved.find('#', [&](int, int){
		++sum;
	});
	return sum;
}

int main() {

	std::string line{};
	std::string compleat;
	std::ifstream file_in;

	aoc::grid grid{};

	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			grid.append_line(line);
		}
		file_in.close();
	}

	std::cout << process(grid) << std::endl;
	return 0;
}
