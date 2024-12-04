#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

#include "../utils.cpp"
#include "../grid.cpp"

int process(const aoc::grid &grid) {

	int sum{0};

	for (int y{1}; y < grid.with()-1; ++y) {
		for (int x{1}; x < grid.higth()-1; ++x) {
			bool one_diag{false};
			if (grid.at(x,y) == 'A') {
				//std::cout << "A at: " << x << " " << y << std::endl;
				grid.for_node_neighbour(x,y, 'M', [&](int nx, int ny){
					//std::cout << "M at: " << nx << " " << ny << std::endl;
					int dx = nx - x;
					int dy = ny - y;

					if (dx == 0 || dy == 0) {
						return;
					}

					int new_x = x+dx*-1;
					int new_y = y+dy*-1;
					if (!grid.inside(new_x,new_y) || grid.at(new_x,new_y) != 'S') {
						//std::cout << "S not at: " << new_x << " " << new_y << std::endl;
						return;
					}
					//std::cout << "S at: " << new_x << " " << new_y << std::endl;

					if (!one_diag) {
						//std::cout << "one" << std::endl;
						one_diag = true;
					} else {
						//std::cout << "two" << std::endl;
						sum++;
					}
				});
			}
		}
	}

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
