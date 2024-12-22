#include <iostream>
#include <fstream>
#include <algorithm>

#include "../utils.cpp"

aoc::ull prune(aoc::ull nr) {
	return nr % 16777216; // 2^24
}

aoc::ull mix(aoc::ull next, aoc::ull nr) {
	return next ^ nr;
}

aoc::ull step(aoc::ull nr) {

	aoc::ull next{nr}; // Max size 2^64 (Not a size issue as we only care about the first 24 bits)

	// Step 1
	next *= 64; // 2^6 Left shift 6 times
	// Bitvise XOR for bits position 7-12
	nr = mix(next, nr); // Keep first 6 bits + mix after 7-12 + keep 12+ bits
	nr = prune(nr); // keep the first 24 bits

	next = nr; // Update

	// Step 2
	next /= 32; // 2^5 Rigth shift 5 times
	nr = mix(next, nr); // Keep first 5 bits + mix after 6-10 + keep 10+ bits
	nr = prune(nr); // keep the first 24 bits

	next = nr; // Update

	// Step 3
	next *= 2048; // 2^11 Left shift 11 times
	nr = mix(next, nr); // Keep first 11 bits + mix after 12-24 + keep 24+ bits
	nr = prune(nr); // keep the first 24 bits

	return nr;
}

aoc::ull process(std::string &in) {

	aoc::ull secreatNumber{0};
	aoc::for_all_numbers<aoc::ull>(in, [&](aoc::ull nr, int, int){
		secreatNumber = nr;
	});

	int steps{2000};
	for(int i{0}; i < steps; ++i) {
		secreatNumber = step(secreatNumber);
	}
	std::cout << in << ": " << secreatNumber << std::endl;
	return secreatNumber;
}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::ull sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line);
		}

		file_in.close();
	}

	std::cout << "----------------" << std::endl;
	std::cout << sum << std::endl;
	return 0;
}
