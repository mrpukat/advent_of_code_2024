#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <algorithm>

#include "../utils.cpp"

int price(aoc::ull nr) {
	return nr % 10;
}

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

aoc::ull process(aoc::ull secreatNumber, std::map<std::queue<int>, int> &prices) {

	std::queue<int> priceChanges;

	int oldPrice{price(secreatNumber)};
	int steps{2000}; // change 2000
	for(int i{0}; i < steps; ++i) {
		secreatNumber = step(secreatNumber);
		int newPrice{price(secreatNumber)};
		int priceDiff = newPrice - oldPrice;

		if(priceChanges.size() == 4) {

			priceChanges.pop();
			priceChanges.push(priceDiff);

			if(!prices.contains(priceChanges)) {
				prices[priceChanges] = newPrice;
			}

		} else {
			priceChanges.push(priceDiff);
		}

		//std::cout << secreatNumber << ": " << newPrice << " (" << priceDiff << ")" << std::endl;
		oldPrice = newPrice;
	}
	
	return secreatNumber;
}

aoc::ull preProcess(std::string &in) {
	aoc::ull secreatNumber{0};
	aoc::for_all_numbers<aoc::ull>(in, [&](aoc::ull nr, int, int){
		secreatNumber = nr;
	});
	return secreatNumber;
}

void mergeMapsInto(std::vector<std::map<std::queue<int>, int>> &pricesList, std::map<std::queue<int>, int> &finalList) {
	assert(finalList.empty());

	for (const auto &prices : pricesList) {
		for (auto it = prices.begin(); it != prices.end(); it++)
		{
			if(finalList.contains(it->first)) {
				finalList[it->first] += it->second;
			} else {
				finalList[it->first] = it->second;
			}
		}
	}

}

int main() {

	std::string line{};
	std::ifstream file_in;

	aoc::ull sum{0};
	std::vector<std::map<std::queue<int>, int>> pricesList;

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			aoc::ull start{preProcess(line)};
			std::map<std::queue<int>, int> prices;
			aoc::ull tmp = process(start, prices);
			pricesList.push_back(prices);
			sum += tmp;
			//std::cout << line << ": " << sum << " (" << sum << ")" <<  std::endl;
		}

		file_in.close();
	}

	std::map<std::queue<int>, int> finalList;
	mergeMapsInto(pricesList, finalList);

	// Get Max (comparitor)
	auto pr = std::max_element(std::begin(finalList), std::end(finalList),
		[] (const auto & p1, const auto & p2) {
			return p1.second < p2.second;
		}
	);

	// Find best sequance
	std::queue<int> optimalPriceChanges = pr->first;
	while(!optimalPriceChanges.empty()) {
		std::cout << optimalPriceChanges.front() << ",";
		optimalPriceChanges.pop();
	}
	std::cout << " (" << pr->second << ")" << std::endl;


	std::cout << "----------------" << std::endl;
	std::cout << sum << std::endl;
	return 0;
}
