#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <memory>

#include "../utils.cpp"
#include "../grid.cpp"

enum Direction {
	Upp = 0,
	Right = 1,
	Down = 2,
	Left = 3
	};

int getCost(Direction from, Direction to) {
	if (from == to) {
		return 0;
	} else if ( (from + 1)%4 == to ) {
		return 1000;
	} else if ( (from + 3)%4 == to ) {
		// +4 -1 = +3
		return 1000;
	} else {
		return 2000;
	}


}

//using node = std::pair<std::pair<int, int>, std::pair<int, Direction>>;
struct node {
	int x;
	int y;
	int cost;
	Direction dir;
	std::shared_ptr<node> n;
};

bool inHistory(node n) {
	int x = n.x, y = n.y;

	std::shared_ptr<node> pre = n.n;
	while (pre)
	{
		if (pre->x == x && pre->y == y) {
			return true;
		}
		pre = pre->n;
	}
	return false;
}

void preProcess(std::string &in, aoc::grid &grid) {
	grid.append_line(in);
}

static int gx{0}, gy{0};

int hyristics(node n) {
	return (n.x-gx)*(n.x-gx) + (n.y-gy)*(n.y-gy);
}

class Compare
{
public:
    bool operator() (node f, node s)
    {
        return f.cost > s.cost;
    }
};

aoc::ull calculateResult(aoc::grid &grid) {

	int x, y;
	grid.find('S', [&](int fx, int fy) {
		x = fx;
		y = fy;
	});
	grid.find('E', [](int fx, int fy) {
		gx = fx;
		gy = fy;
	});

	//grid.set(x,y, '.');

	std::vector<std::vector<int>> costMap;

	for (int y{0}; y < grid.higth(); ++y) {
		costMap.push_back({});
		for (int x{0}; x < grid.with(); ++x) {
			costMap.at(y).push_back(-1);
		}
	}

	std::priority_queue<node, std::vector<node>, Compare> pq;
	pq.push({x, y, 0, Direction::Right});
	std::string printdir = "^>v<";
	std::vector<node> goals;
	int finalCost = -1;

	while(!pq.empty()) {
		node top = pq.top();
		x = top.x;
		y = top.y;
		int cost = top.cost;
		Direction dir = top.dir;
		pq.pop();

		if(grid.at(x, y) == 'E') {
			std::cout << cost << std::endl;
			if (finalCost == -1) {
				finalCost = cost;
			}
			if(cost == finalCost) {
				goals.push_back(top);
			}
			continue;
		} else if (inHistory(top) || (finalCost < cost && finalCost != -1)) {
			continue;
		} else if(costMap.at(y).at(x) != -1 && costMap.at(y).at(x) + 1000 < cost) {
			//std::cout << " " << top.x << " " << top.y << " " << top.cost << " " << printdir.at(top.dir) << std::endl;
			//std::cout << "Cost map: " << costMap.at(y).at(x) << " " << cost << std::endl;
			continue;
		}

		costMap.at(y).at(x) = cost;

		std::shared_ptr<node> n = std::make_shared<node>(top);

		grid.set(x,y, printdir.at(dir));
		int moveCost = 1+getCost(dir,Direction::Left);
		if(grid.at(x-1, y) != '#' && moveCost != 2001) {
			pq.push({x-1, y, moveCost+cost, Direction::Left, n});
		}
		moveCost = 1+getCost(dir,Direction::Down);
		if(grid.at(x, y+1) != '#' && moveCost != 2001) {
			pq.push({x, y+1, moveCost+cost, Direction::Down, n});
		}
		moveCost = 1+getCost(dir,Direction::Right);
		if(grid.at(x+1, y) != '#' && moveCost != 2001) {
			pq.push({x+1, y, moveCost+cost, Direction::Right, n});
		}
		moveCost = 1+getCost(dir,Direction::Upp);
		if(grid.at(x, y-1) != '#' && moveCost != 2001) {
			pq.push({x, y-1, moveCost+cost, Direction::Upp, n});
		}

		//grid.print();
		//std::cout << " " << top.x << " " << top.y << " " << top.cost << " " << printdir.at(top.dir) << std::endl;
	}

	std::cout << goals.size() << std::endl;

	std::set<std::pair<int,int>> tiles;
	for(node n : goals) {
		tiles.emplace(n.x, n.y);

		std::shared_ptr<node> pre = n.n;
		while (pre) {
			tiles.emplace(pre->x,pre->y);
			pre = pre->n;
		}
	}

	std::cout << tiles.size() << std::endl;

	return finalCost;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::grid grid;
	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		while(getline(file_in, line)) {
			if (!line.empty()) {
				preProcess(line, grid);
			}
		}
		file_in.close();
	}

	std::cout << calculateResult(grid) << std::endl;
	return 0;
}
