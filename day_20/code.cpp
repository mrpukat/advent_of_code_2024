#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <memory>
#include <set>

#include "../utils.cpp"
#include "../grid.cpp"


struct node {
	int x;
	int y;
	int cost;
	std::shared_ptr<node> n;
};


void preProcess(std::string &in, aoc::grid &grid) {
	grid.append_line(in);
}

aoc::ull process(aoc::grid grid) {

	int x, y;
	grid.find('E', [&](int sx, int sy){
		x = sx;
		y = sy;
	});
	grid.set(x, y, '.');

	std::shared_ptr<node> path;

	std::vector<std::vector<int>> costMap;

	for (int y{0}; y < grid.higth(); ++y) {
		costMap.push_back({});
		for (int x{0}; x < grid.with(); ++x) {
			costMap.at(y).push_back(-1);
		}
	}

	std::queue<node> q;
	q.push({x, y, 0});

	while(!q.empty()) {
		node top = q.front();
		x = top.x;
		y = top.y;
		int cost = top.cost;
		q.pop();

		if(grid.at(x,y) == 'S') {
			grid.set(x,y, 'O');
			if(!path) {
				path = std::make_shared<node>(top);
				costMap.at(y).at(x) = cost;
			}
			continue;
		} else if(grid.at(x, y) != '.') {
			continue;
		} else if(costMap.at(y).at(x) != -1 && costMap.at(y).at(x) <= cost) {
			continue;
		}

		costMap.at(y).at(x) = cost;
		std::shared_ptr<node> n = std::make_shared<node>(top);

		grid.set(x,y, 'O');
		grid.for_node_neighbour(x, y, false, [&](char c, int nx, int ny){
			if (c != '#') {
				q.push({nx, ny, cost+1, n});
			}
		});

		//grid.print();
		//std::cout << top.x << " " << top.y << " " << top.cost << std::endl;
	}

	std::vector<node> tiles;

	while(path) {
		tiles.push_back({path->x, path->y, path->cost});
		path = path->n;
	}

	int cheatSteps{20};
	int compareCost = 100;
	std::set<std::pair<std::pair<int,int>,std::pair<int,int> > > cheats;


	for (int i{0}; i < tiles.size(); ++i) {
		x = tiles.at(i).x;
		y = tiles.at(i).y;
		int cost = tiles.at(i).cost;

		std::vector<std::vector<bool>> visited;
		for (int vy{0}; vy < grid.higth(); ++vy) {
			visited.push_back({});
			for (int vx{0}; vx < grid.with(); ++vx) {
				visited.at(vy).push_back(false);
			}
		}

		std::queue<node> q;
		q.push({x, y, 0});

		while(!q.empty()) {
			node top = q.front();
			int nx = top.x;
			int ny = top.y;
			int steps = top.cost;
			q.pop();

			if (steps > cheatSteps || visited.at(ny).at(nx)) {
				continue;
			}
			if(costMap.at(ny).at(nx) != -1 && costMap.at(ny).at(nx) - (cost + steps) >= compareCost) {
				cheats.insert({{x,y},{nx,ny}});
			}


			visited.at(ny).at(nx) = true;

			grid.for_node_neighbour(nx, ny, false, [&](char c, int nnx, int nny){
				q.push({nnx, nny, steps+1});
			});


		}

	}

	std::cout << "--------------------------" << std::endl;
	return cheats.size();
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::grid grid;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			preProcess(line, grid);
		}

		file_in.close();
	}

	std::cout << process(grid) << std::endl;
	return 0;
}
