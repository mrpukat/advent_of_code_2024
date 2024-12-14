#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#include "../utils.cpp"


void pre_process(std::string &in, std::vector<std::pair<int,int>> &pos, std::vector<std::pair<int,int>> &vel) {

	bool x{true}, v{false};
	std::pair<int, int> nodeP, nodeV;
	aoc::for_all_numbers<int>(in, [&](int nr, int, int){
		if (!v) {
			if (x) {
				nodeP.first = nr;
				x = false;
			} else {
				nodeP.second = nr;
				x = true;
				v = true;
			}
		} else {
			if (x) {
				nodeV.first = nr;
				x = false;
			} else {
				nodeV.second = nr;
			}
		}
 	});

	pos.push_back(nodeP);
	vel.push_back(nodeV);
}

aoc::ll process(std::vector<std::pair<int,int>> &pos, std::vector<std::pair<int,int>> &vel) {

	int with{101};
	int higth{103};

	aoc::ll seconds{100};

	int higth_middel = higth / 2;
	int with_middel = with / 2;

	std::cout << "With: " << with << " Higth: " << higth << " Middel With: " << with_middel << " Middel Higth " << higth_middel << std::endl;

	aoc::ll upperLeft{0}, upperRigth{0};
	aoc::ll lowerLeft{0}, lowerRigth{0};


	for (int i{0}; i < pos.size(); ++i) {
		std::cout << i << " p= " << pos.at(i).first << " , " << pos.at(i).second << " v= " << vel.at(i).first << " , " << vel.at(i).second << std::endl;

		aoc::ll x = ((aoc::ll)pos.at(i).first  + seconds * (aoc::ll)vel.at(i).first)  % with;
		std::cout << x << " = (" << pos.at(i).first << " + " << seconds << " * " << vel.at(i).first << ") % " << with << std::endl;
		aoc::ll y = ((aoc::ll)pos.at(i).second + seconds * (aoc::ll)vel.at(i).second) % higth;
		std::cout << y << " = (" << pos.at(i).second << " + " << seconds << " * " << vel.at(i).second << ") % " << higth << std::endl;

		if (x < 0) {
			x += with;
		}
		if (y < 0) {
			y += higth;
		}

		std::cout << x << " " << y << std::endl;

		if (x > with_middel) {
			if (y > higth_middel) {
				std::cout << "Lower Rigth: " << x << " " << y << std::endl;
				lowerRigth++;
			} else if (y < higth_middel) {
				upperRigth++;
				std::cout << "Upper Rigth: " << x << " " << y << std::endl;
			}
		} else if (x < with_middel) {
			if (y > higth_middel) {
				std::cout << "Lower Left: " << x << " " << y << std::endl;
				lowerLeft++;
			} else if (y < higth_middel) {
				std::cout << "Upper Left: " << x << " " << y << std::endl;
				upperLeft++;
			}
		}

	}

		std::cout << upperLeft << " " << upperRigth << " " << lowerLeft << " " << lowerRigth << std::endl;


	return upperLeft*upperRigth*lowerLeft*lowerRigth;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	std::vector<std::pair<int,int>> pos;
	std::vector<std::pair<int,int>> vel;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		while(getline(file_in, line)) {
			pre_process(line, pos, vel);
		}


		file_in.close();
	}

	std::cout << process(pos, vel) << std::endl;
	return 0;
}
