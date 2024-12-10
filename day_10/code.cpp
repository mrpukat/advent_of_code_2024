#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <queue>

#include "../utils.cpp"
#include "../grid.cpp"

int process(aoc::grid &grid) {

	int sum{0};

	grid.find('0', [&](int x, int y){
		//std::cout << "Start:" << x << " " << y << std::endl;
		std::vector<std::pair<int, int>> goals;

		std::queue<std::pair<int, int>> q;  
		q.emplace(x,y);

		while (!q.empty()) {
			std::pair<int, int> coord = q.front();
			q.pop();
			char elevation = grid.at(coord.first, coord.second);
			if (elevation == '9') {
				goals.emplace_back(coord);
			} else {
				grid.for_node_neighbour(coord.first, coord.second, false, elevation+1, [&](int nx, int ny){
					//std::cout << nx << " " << ny << std::endl;
					q.emplace(nx, ny);
				});
			}
		}
		//std::cout << goals.size() << std::endl;
		sum += goals.size();
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
