#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"

int check_coners(aoc::grid &grid, std::set<std::pair<int,int>> &s, std::pair<int, int> node, char match) {
	
	int x = node.first;
	int y = node.second;
	int perimeter{0};

	if (!grid.inside(x-1,y) || (grid.at(x-1,y) != match && !s.contains({x-1,y}))) {
		if (!grid.inside(x,y-1) || (grid.at(x,y-1) != match && !s.contains({x,y-1}))) {
			perimeter++;
		}
		if (!grid.inside(x,y+1) || (grid.at(x,y+1) != match && !s.contains({x,y+1}))) {
			perimeter++;
		}
	}

	if (!grid.inside(x+1,y) || (grid.at(x+1,y) != match && !s.contains({x+1,y}))) {
		if (!grid.inside(x,y-1) || (grid.at(x,y-1) != match && !s.contains({x,y-1}))) {
			perimeter++;
		}
		if (!grid.inside(x,y+1) || (grid.at(x,y+1) != match && !s.contains({x,y+1}))) {
			perimeter++;
		}
	}

	return perimeter;
}


int check_coners2(aoc::grid &grid, std::set<std::pair<int,int>> &s, std::pair<int, int> node, char match) {
	
	int x = node.first;
	int y = node.second;
	int perimeter{0};

	if (grid.inside(x-1,y) && (grid.at(x-1,y) == match || s.contains({x-1,y}))) {
		if (grid.inside(x,y-1) && (grid.at(x,y-1) == match || s.contains({x,y-1}))) {
			if (grid.at(x-1,y-1) != match && !s.contains({x-1,y-1})) {
				perimeter++;
			}
		}
		if (grid.inside(x,y+1) && (grid.at(x,y+1) == match || s.contains({x,y+1}))) {
			if (grid.at(x-1,y+1) != match && !s.contains({x-1,y+1})) {
				perimeter++;
			}
		}
	}

	if (grid.inside(x+1,y) && (grid.at(x+1,y) == match || s.contains({x+1,y}))) {
		if (grid.inside(x,y-1) && (grid.at(x,y-1) == match || s.contains({x,y-1}))) {
			if (grid.at(x+1,y-1) != match && !s.contains({x+1,y-1})) {
				perimeter++;
			}
		}
		if (grid.inside(x,y+1) && (grid.at(x,y+1) == match || s.contains({x,y+1}))) {
			if (grid.at(x+1,y+1) != match && !s.contains({x+1,y+1})) {
				perimeter++;
			}
		}
	}


	return perimeter;
}

unsigned long long process(aoc::grid &grid) {

	aoc::ull sum{0};

	//grid.print();
	//std::cout << "---------------------------" << std::endl;

	for (int y{0}; y < grid.with(); ++y) {
		for (int x{0}; x < grid.higth(); ++x) { 
			char match = grid.at(x, y);

			if (match == '.') {
				continue;
			}

			int area{0}, perimeter{0};

			std::queue<std::pair<int, int>> q;
			q.emplace(x, y);
			grid.set(x, y, '.');
			std::set<std::pair<int,int>> s;
			s.emplace(x, y);

			while(!q.empty()) {

				++area;
				std::pair<int, int> node = q.front();
				q.pop();

				perimeter += check_coners(grid, s, node, match);
				perimeter += check_coners2(grid, s, node, match);

				grid.for_node_neighbour(node.first, node.second, false, [&](char cmp, int nx, int ny){
					bool xIn = node.second != ny;

					if (cmp == match) {
						q.emplace(nx, ny);
						grid.set(nx, ny, '.');
						s.emplace(nx, ny);
					}
				});
			}

			aoc::ull tmp = area*perimeter;
			sum += tmp;
			std::cout << match << " " << area << " * " << perimeter << " = " << tmp << " (" << sum << ")" << std::endl;
			//grid.print();
			//std::cout << "---------------------------" << std::endl;

		}
	}

	return sum;
}

int main() {

	std::string line{};
	std::ifstream file_in;
	aoc::grid grid;

	unsigned long long sum{0};

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
