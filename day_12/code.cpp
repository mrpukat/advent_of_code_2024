#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"


unsigned long long process(aoc::grid &grid) {

	unsigned long long sum{0};

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
			// (x,y), X^ = nr
			std::map<std::pair<std::pair<int, int>, bool>, int> p;

			while(!q.empty()) {

				++area;
				std::pair<int, int> node = q.front();
				q.pop();

				if (node.first == 0) {
					++perimeter;
					p[{{-1,node.second}, false}] = 1;
				} else if (node.first == grid.higth()-1) {
					++perimeter;
					p[{{grid.higth(),node.second}, false}] = 1;
				}
				if (node.second == 0) {
					++perimeter;
					p[{{node.first,-1}, true}] = 1;
				} else if (node.second == grid.with()-1) {
					++perimeter;
					p[{{node.first,grid.with()}, true}] = 1;
				}
//				std::cout << "-----" << std::endl;
				grid.for_node_neighbour(node.first, node.second, false, [&](char cmp, int nx, int ny){
					bool xIn = node.second != ny;

					if (cmp == match) {
						q.emplace(nx, ny);
						grid.set(nx, ny, '.');
						s.emplace(nx, ny);
					} else {
//						std::cout << "(" << nx << "," << ny << ") " << ny << " " << xIn << std::endl;
						if (!s.contains({nx,ny})) {
							++perimeter;
							if (p.contains({{nx,ny}, xIn})) {
								p[{{nx,ny}, xIn}]++;
							} else {
								p[{{nx,ny}, xIn}] = 1;
							}
						}
					}
				});
				// std::cout << node.first << " " << node.second << std::endl;
				// std::cout << area << " " << perimeter << std::endl;
				// std::cout << "----" << std::endl;
			}

			perimeter = 0;
			while(!p.empty()) {
//				std::cout << "---" << std::endl;
				++perimeter;

				auto it = p.begin();
				int x = it->first.first.first;
				int y = it->first.first.second;
				bool xIn = it->first.second;
//				std::cout << "Found: " << x << " " << y << " " << xIn << std::endl;
				if (it->second == 1) {
					p.erase(it);
				} else {
					--it->second;
				}
				// Explore X
				int sx = x, sy = y;
				int dx{0}, dy{0};
				if (xIn) {
					dx++;
				} else {
					dy++;
				}
				while(true) {
					x += dx, y += dy;
					std::pair<int, int> node = {x,y};
					if (!p.contains({node, xIn})) {
						if (dx == 1) {
							dx = -1;
							x = sx;
						} else if (dy == 1) {						
							dy = -1;
							y = sy;
						} else {
							break;
						}
					} else {
//						std::cout << "Found: " << node.first << " " << node.second << " " << xIn << std::endl;
						if (p[{node, xIn}] == 1) {
							p.erase({node, xIn});
						} else {
							--p[{node, xIn}];
						}
					}
				}
			}

			unsigned long long tmp = area*perimeter;
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


// Too low 781543
// Too low 784847


// Missed edgecase
// BCA
// ADE
// If aa are connected then the fens can travel throw