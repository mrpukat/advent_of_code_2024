#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"


bool canMoveY(aoc::grid &grid, int x, int y, int dy) {
	char next = grid.at(x, y + dy);

	bool result{next != '#'};

	if (next == '[') {
		result = result && canMoveY(grid, x, y + dy, dy);
		result = result && canMoveY(grid, x + 1, y + dy, dy);
	} else if (next == ']') {
		result = result && canMoveY(grid, x, y + dy, dy);
		result = result && canMoveY(grid, x - 1, y + dy, dy);
	}
	return result;
}

bool move(aoc::grid &grid, int x, int y, int dx, int dy) {
	char next = grid.at(x + dx, y + dy);
	if (next == '#') {
		return false;
	}


	bool moved{true};
	if (next == '[' || next == ']') {

		if (dx != 0) {
			moved = move(grid, x + dx, y, dx, 0);
		} else {
			bool first{false};
			if (next == '[') {
				first = move(grid, x, y + dy, 0, dy);
				moved = moved && move(grid, x+1, y + dy, 0, dy) && first;
			} else {
				first = move(grid, x, y + dy, 0, dy);
				moved = moved && move(grid, x-1, y + dy, 0, dy) && first;
			}
			
//			if (first && !moved) {
//				grid.set(x,y, grid.at(x, y + dy));
//				grid.set(x,y + dy, '.');
//			}
		}
	}


	next = grid.at(x + dx, y + dy);
	if (moved) {
		grid.set(x + dx, y + dy, grid.at(x, y));
		grid.set(x, y, '.');
		return true;
	}
	return false;
}

aoc::ll process(std::string &in, aoc::grid &grid) {

	int x, y;
	grid.find('@', [&](int fx, int fy) {
		x = fx;
		y = fy;
	});

	int dx{0}, dy{0};
	for(char c : in) {
		//std::cout << "-----------------" << std::endl;
		//std::cout << c << " " << x << " " << y << std::endl;
		if (c == 'v') {
			dy = 1;
		}
		if (c == '^') {
			dy = -1;
		}
		if (c == '<') {
			dx = -1;
		}
		if (c == '>') {
			dx = 1;
		}

		bool canMove{true};
		if(dy != 0) {
			canMove = canMoveY(grid, x, y, dy);
		}

		if (canMove && move(grid, x, y, dx, dy)) {
			x += dx;
			y += dy;
		}

		//grid.print();
		dy = 0; dx = 0;
	}

	return 0;
}

void preProcess(std::string &in, aoc::grid &grid) {

	std::string line;
	for (char c : in) {
		if (c == '#') {
			line.append("##");
		}
		if (c == '@') {
			line.append("@.");
		} 
		if (c == '.') {
			line.append("..");
		}
		if (c == 'O') {
			line.append("[]");
		}
	}
	grid.append_line(line);

}

aoc::ull calculateResult(aoc::grid &grid) {

	aoc::ull sum{0};

	grid.find('[', [&](int x, int y){
		sum += y*100 +x;
	});

	return sum;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::grid grid;
	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		bool gridInput{true};
		while(getline(file_in, line)) {
			if (!line.empty()) {
				if (gridInput) {
					preProcess(line, grid);
				} else {
					process(line, grid);
				}
			} else {
				gridInput = false;
				grid.print();
			}
		}


		file_in.close();
	}

	std::cout << calculateResult(grid) << std::endl;
	return 0;
}
