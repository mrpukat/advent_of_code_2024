#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "../utils.cpp"

aoc::ull preProcess(std::string &in) {
	aoc::ull res{0};
	aoc::for_all_numbers<aoc::ull>(in, [&](aoc::ull nr, int, int){
		res = nr;
	});
	return res;
}

void getIntructions(std::string &in, std::vector<int> &inst) {
	aoc::for_all_numbers<int>(in, [&](int nr, int, int){
		inst.push_back(nr);
	});
}

class regestry{

public:
	aoc::ull getCombo(int i) {
		switch (i)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			return i;
			break;
		case 4:
			return A;
			break;
		case 5:
			return B;
			break;
		case 6:
			return C;
			break;
		
		}
		assert(false);
	}

	aoc::ull A, B, C;
	std::vector<int> intructions;

};

std::vector<int> process(regestry &R) {
	int p{0};
	std::vector<int> output;

	// --- Values --- (Combo)
	// Value 0-3 Real value
	// Value 4 is Value in A
	// Value 5 is Value in B
	// Value 6 is Value in C
	// Value 7 is Invalid (not occur)

	// --- Instructions ---
	// 0 is A = A / 2^(Combo)
	// 1 is B = B XOR (Value)
	// 2 is B = (Combo) & 8 (keep last 3 bits?)
	// 3 is Noting if A == 0
	//	Else p = (Value)
	// 4 is B = B XOR C
	// 5 is (Combo) % 8 => output
	// 6 is B = A / 2^(Combo)
	// 7 is C = A / 2^(Combo)

	while(R.intructions.size() > p) {

		// Get operation
		int operation = R.intructions.at(p);

		// Get value
		aoc::ull value = R.intructions.at((++p)++);
		//std::cout << "Operation Nr: " << operation << " Value: " << value << std::endl;
		//std::cout << "A: " << R.A << " B: " << R.B << " C: " << R.C << std::endl;

		// Perform operation
		switch (operation)
		{
		case 0:
			R.A /= std::pow(2, R.getCombo(value));
			break;
		case 1:
			R.B ^= value;
			break;
		case 2:
			R.B = R.getCombo(value) % 8;
			break;
		case 3:
			if (R.A != 0) {
				p = value;
			}
			break;
		case 4:
			R.B ^= R.C;
			break;
		case 5:
			output.push_back(R.getCombo(value) % 8);
			break;
		case 6:
			R.B = R.A / std::pow(2, R.getCombo(value));
			break;
		case 7:
			R.C = R.A / std::pow(2, R.getCombo(value));
			break;		
		}

	}

	//std::cout << "A: " << R.A << " B: " << R.B << " C: " << R.C << std::endl;
	//std::cout << "Results: ";
	//std::copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, ","));
	//std::cout << std::endl;

	return output;
}

aoc::ull calculateA(std::vector<int> &nrV) {
	assert(nrV.size() == 16);
	aoc::ull sum{0}, mult{1};
	for(int i{15}; i >= 0; --i) {
		sum += mult * nrV.at(i);
		mult *= 8;
	}
	return sum;
}

aoc::ull findBit(regestry r, aoc::ull A, int i){
	std::cout << A << "    " << i << std::endl;
	if(i == -1) {
		return A;
	}

	for (int j{0}; j < 8; ++j) {

		r.A = A;
		r.A += j*std::pow(8,i);
		aoc::ull ACopy = r.A;
		std::vector<int> res = process(r);
		//std::cout << res.size() << " " << r.intructions.size() << std::endl;
		if (res.size() == r.intructions.size()) {
			std::cout << "Iteration: " << j << " " << res.at(i) << " " << r.intructions.at(i) << std::endl;
		}
		if (res.size() == r.intructions.size() && res.at(i) == r.intructions.at(i)) {
			std::cout << "Fund: " << i << " " << j << " " << res.at(i) << std::endl;
			aoc::ull res = findBit(r, ACopy, i-1);
			if(res != 0) {
				return res;
			}
		}
	}

	//std::cout << "Gave up at: " << i << std::endl;
	return 0;
}


int main() {

	std::string line{};
	std::ifstream file_in;

	regestry r;

	std::vector<int> intructions;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{

		getline(file_in, line);
		//std::cout << line << std::endl;
		r.A = preProcess(line);
		getline(file_in, line);
		r.B = preProcess(line);
		getline(file_in, line);
		r.C = preProcess(line);
		getline(file_in, line);

		getline(file_in, line);
		getIntructions(line, intructions);
		r.intructions = std::move(intructions);

		file_in.close();
	}


// Algirithm
// From 0 to 7
// Find that works -> move down
// Dont find -> move upp

	/*
	std::vector<int> AV;
	AV.push_back(6); // 6 (110)
	AV.push_back(1); // 1 or 5 (?01)
	AV.push_back(1); // IF 5: 1, 5, 6 (???) IF 1: 1, 5 (?01)
	AV.push_back(1);
	AV.push_back(7); // Dead end
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	AV.push_back(0);
	r.A = calculateA(AV);
	std::cout << "Pegister A: " << r.A << std::endl;
	*/
	// Alorrith to set A in register

	/*
	std::vector<int> output = process(r);

	std::cout << "Results: ";
	std::copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
	*/
	std::cout << line << std::endl;

	std::cout << findBit(r, 0, 15) << std::endl;

	return 0;
}
