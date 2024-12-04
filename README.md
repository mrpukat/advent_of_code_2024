g++ -std=c++17 code2.cpp

std::copy(pars.begin(), pars.end(), std::ostream_iterator<char>(std::cout, " "));
