#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#include "../utils.cpp"
#include "../grid.cpp"


struct node {
	int x;
	int y;
	int cost;
};

void createGrid(aoc::grid &grid) {
	// TODO 7 -> 71
	for (int i{0}; i < 71; ++i) {
		std::string line(71, '.');
		grid.append_line(line);
	}
}

void preProcess(std::string &in, aoc::grid &grid) {
	bool first{true};
	int x, y;
	aoc::for_all_numbers<int>(in, [&](int nr, int, int){
		if (first) {
			first = false;
			x = nr;
		} else {
			y = nr;
		}
	});
	grid.set(x,y, '#');
}

aoc::ull process(aoc::grid grid) {

	int gx{70}, gy{70}; // TODO

	std::queue<node> q;
	q.push({0, 0, 0});

	while(!q.empty()) {
		node top = q.front();
		int x = top.x;
		int y = top.y;
		//std::cout << "At: "<< x << " " << x << std::endl;
		int cost = top.cost;
		q.pop();

		if(x == gx && y == gy) {
			//std::cout << "Found! " << x << " " << x << std::endl;
			return cost;
		} else if(grid.at(x, y) != '.') {
			//std::cout << "Wall: " << x << " " << x << std::endl;
			continue;
		}


		//std::cout << "Set: " << x << " " << x << std::endl;
		grid.set(x,y, 'O');
		grid.for_node_neighbour(x, y, false, '.', [&](int nx, int ny){
			//std::cout << "Next: " << nx << " " << ny << std::endl;
			q.push({nx, ny, cost+1});
		});

		//grid.print();
		//std::cout << top.x << " " << top.y << " " << top.cost << std::endl;
	}

	return 0;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::grid grid;

	createGrid(grid);

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			preProcess(line, grid);
			if (process(grid) == 0) {
				std::cout << line << std::endl;
				return 0;
			}
		}

		file_in.close();
	}

//	std::cout << process(grid) << std::endl;
	return 0;
}
