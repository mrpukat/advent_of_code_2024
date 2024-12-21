#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

#include "../utils.cpp"

int preProcess(std::string &in) {
	int res;
	aoc::for_all_numbers<int>(in, [&](int nr, int, int){
		res = nr;
	});
	return res;
}

struct node {
	int x;
	int y;
	int depth;
	char command;

	auto operator<=>(const node&) const = default;
};

/*
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/
aoc::ull terminal(char c, int &x, int &y, int depth, std::map<node, aoc::ull> &memory) {

	if ( depth == 0) {
		return 1;
	}

	int gx, gy;
	switch (c)
	{
	case '^':
		gx = 1;
		gy = 0;
		break;
	case 'A':
		gx = 2;
		gy = 0;
		break;
	case '<':
		gx = 0;
		gy = 1;
		break;
	case 'v':
		gx = 1;
		gy = 1;
		break;
	case '>':
		gx = 2;
		gy = 1;
		break;
	
	default:
		assert(false);
	}

	node saveStae{x, y, depth, c};
	if (memory.contains(saveStae)) {
		x = gx;
		y = gy;
		return memory[saveStae];
	}

	aoc::ull sum{0};
	std::string movement;
	int nx{2}, ny{0};
	for (;x > gx; --x) {
		if(y == 0 && gx == 0) {
			sum += terminal('v', nx, ny, depth-1, memory);
			++y;
		}
		sum += terminal('<', nx, ny, depth-1, memory);
	}
	for (;y > gy; --y) {
		if(x == 0 && y == 1) {
			for (;x < gx; ++x) {
				sum += terminal('>', nx, ny, depth-1, memory);
			}
		}
		sum += terminal('^', nx, ny, depth-1, memory);
	}
	for (;y < gy; ++y) {
		sum += terminal('v', nx, ny, depth-1, memory);
	}
	for (;x < gx; ++x) {
		sum += terminal('>', nx, ny, depth-1, memory);
	}

	sum += terminal('A', nx, ny, depth-1, memory);
	assert(nx==2 && ny == 0);

	memory[saveStae] = sum;

	//std::cout << movement << " " << c << " (" << 1 << ")" << " (" << x1 << "," << y1 << ")" << std::endl;
	return sum;
}

/*
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+
*/
aoc::ull mainTerminal(char c, int &x, int &y, int depth, std::map<node, aoc::ull> &memory) {

	int gx, gy;
	switch (c)
	{
	case '9':
		gx = 2;
		gy = 0;
		break;
	case '8':
		gx = 1;
		gy = 0;
		break;
	case '7':
		gx = 0;
		gy = 0;
		break;
	case '6':
		gx = 2;
		gy = 1;
		break;
	case '5':
		gx = 1;
		gy = 1;
		break;
	case '4':
		gx = 0;
		gy = 1;
		break;
	case '3':
		gx = 2;
		gy = 2;
		break;
	case '2':
		gx = 1;
		gy = 2;
		break;
	case '1':
		gx = 0;
		gy = 2;
		break;
	case 'A':
		gx = 2;
		gy = 3;
		break;
	case '0':
		gx = 1;
		gy = 3;
		break;
	
	default:
		assert(false);
	}

	node saveStae{x, y, depth, c};
	if (memory.contains(saveStae)) {
		x = gx;
		y = gy;
		return memory[saveStae];
	}

	aoc::ull sum{0};
	std::string movement;
	int nx{2}, ny{0};

	for (;x > gx; --x) {
		if( y == 3 && gx == 0) {
			for (;y > gy; --y) {
				sum += terminal('^', nx, ny, depth-1, memory);
			}
		}
		sum += terminal('<', nx, ny, depth-1, memory);
	}
	for (;y > gy; --y) {
		sum += terminal('^', nx, ny, depth-1, memory);
	}
	for (;y < gy; ++y) {
		if(x == 0 && gy == 3) {
			for (;x < gx; ++x) {
				sum += terminal('>', nx, ny, depth-1, memory);
			}
		}
		sum += terminal('v', nx, ny, depth-1, memory);
	}
	for (;x < gx; ++x) {
		sum += terminal('>', nx, ny, depth-1, memory);
	}

	sum += terminal('A', nx, ny, depth-1, memory);

	//std::cout << movement << " " << c << " (" << 0 << ")" << " (" << x << "," << y << ")" << std::endl;
	memory[saveStae] = sum;

	return sum;
}

aoc::ull process(std::string &in, std::map<node, aoc::ull> &memory) {

	std::string res;
	aoc::ull sum{0};
	int x{2}, y{3};
	int depth{27}; // Part 1: 4 // Part 2: 4 + 23 = 27
	for (char c : in) {
		sum += mainTerminal(c, x, y, depth-1, memory);
	}
	return sum;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::ull sum{0};
	std::map<node, aoc::ull> memory;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			int tmp = preProcess(line);
			sum += tmp * process(line, memory);
		}

		file_in.close();
	}

	std::cout << "----------------" << std::endl;
	std::cout << sum << std::endl;
	return 0;
}
