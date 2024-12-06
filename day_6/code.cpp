#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

#include "../utils.cpp"
#include "../grid.cpp"

typedef unsigned int Uint;

char hex_to_char(Uint hex) {
	std::string val{"0123456789ABCDEF"};
	return val.at(hex);
}

Uint char_to_hex(char hex) {
	std::string val{"0123456789ABCDEF"};
	return std::strchr(val.c_str(), hex) - val.c_str();
}

inline Uint bit_set(Uint number, Uint n) {
    return number | ((Uint)1 << n);
}

inline bool bit_check(Uint number, Uint n) {
    return (number >> n) & (Uint)1;
}

int process(aoc::grid &grid) {

	int sum{0};
	int x, y;
	grid.find('^', [&](int fx, int fy){
		x = fx;
		y = fy;
	});

	grid.set(x, y, '.');

	int dx{0}, dy{-1};
	int pos{0};
	bool simulation{false};
	bool start{true};
	int rx{0}, ry{0}, rdx{0}, rdy{0}, rpos{0};
	aoc::grid old_grid = grid;
	while (grid.inside(x, y) || simulation) {
		std::cout << "---------------------------------\n";
		if (!grid.inside(x, y)) {
			grid = old_grid;
			x = rx; y = ry;
			dx = rdx; dy = rdy;
			pos = rpos;
			simulation = false;
		} else if (!simulation && grid.at(x, y) == '.' && !start) {
			old_grid = grid;
			simulation = true;
			rx = x; ry = y;
			rdx = dx; rdy = dy;
			rpos = pos;
			grid.set(x,y,'#');
		}


		if(grid.at(x, y) == '#') {
			x -= dx;
			y -= dy;

			if (++pos > 3) pos = 0;

			if (dx != 0) {
				dy = dx; dx = 0;
			} else {
				dx = -1*dy; dy = 0;
			}
		} else {
			if (grid.at(x,y) == '.') {
				grid.set(x,y, hex_to_char(0x0));
			}

			if (bit_check(char_to_hex(grid.at(x,y)), pos)) {
				grid.print();
				grid = old_grid;
				x = rx; y = ry;
				dx = rdx; dy = rdy;
				pos = rpos;
				simulation = false;
				sum++;
				start = true;
				continue;
			}

			Uint hex = char_to_hex(grid.at(x,y));
			grid.set(x, y, hex_to_char(bit_set(hex, pos)));
		}


		x += dx;
		y += dy;
		grid.print();
		start = false;
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
