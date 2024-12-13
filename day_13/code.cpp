#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#include "../utils.cpp"
#include "../grid.cpp"

// B const 3
// A const 1

struct values {
	aoc::ll x{0}, xa{0}, xb{0};
	aoc::ll y{0}, ya{0}, yb{0};
};

long process(values n) {

	std::cout << n.xa << " XA|YA " << n.ya << std::endl;
	std::cout << n.xb << " XB|YB " << n.yb << std::endl;
	std::cout << n.x << " X|Y " << n.y << std::endl;

	aoc::ll a = n.x*n.yb - n.y*n.xb;
	aoc::ll div = n.xa*n.yb - n.xb*n.ya;
	if (a % div != 0) {
		return 0;
	} 
	a /= div;

	aoc::ll b = n.x - a*n.xa;
	if (b % n.xb != 0) {
		return 0;
	}
	b /= n.xb;

	std::cout << "B: " << b << " A: " << a << std::endl;

	std::cout << n.x << " = " << a << " * " << n.xa << " + " << b << " * "  << n.xb << std::endl;
	std::cout << n.y << " = " << a << " * " << n.ya << " + " << b << " * "  << n.yb << std::endl;
	assert(n.x == a*n.xa + b*n.xb);
	assert(n.y == a*n.ya + b*n.yb);

	/*
	if (b > 100 || a > 100) {
		return 0;
	}
	*/


	return b + 3*a; // Swithced why
}

void set_both(std::string &in, aoc::ll &a, aoc::ll &b) {
	bool first{true};
	aoc::for_all_numbers<aoc::ll>(in, [&](aoc::ll nr, int i, int){
		if (first) {
			first = false;
			a = nr;
		} else {
			b = nr;
		}
	});
}


int main() {

	std::string line{};
	std::ifstream file_in;
	aoc::grid grid;

	aoc::ll sum{0};

	aoc::ll add{10000000000000};

	aoc::ll x{0}, xa{0}, xb{0};
	aoc::ll y{0}, ya{0}, yb{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		do {
			std::cout << "----------------" << std::endl;
			getline(file_in, line);
			set_both(line, xa, ya);
			getline(file_in, line);
			set_both(line, xb, yb);
			getline(file_in, line);
			set_both(line, x, y);

			aoc::ll tmp = process({x+add, xa, xb, y+add, ya, yb});
			sum += tmp;
			std::cout << "(" << tmp << ") " << sum << std::endl;

		} while(getline(file_in, line));


		file_in.close();
	}

	std::cout << sum << std::endl;
	return 0;
}
