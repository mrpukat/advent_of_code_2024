#include <map>

namespace aoc {

template <typename T, typename Q>
void for_all_keys(const std::multimap<T, Q> &mmp, std::function< void( T ) >&& f) {

	for(auto it = mmp.begin(); it != mmp.end(); it = mmp.upper_bound(it->first)) {
		f(it->first);
	}

}

template <typename T, typename Q>
void for_all_values(const std::multimap<T, Q> &mmp, const T& key, std::function< void( Q ) >&& f) {

	for (auto [it, end] = mmp.equal_range(key); it != end; ++it) {
		f(it->second);
	}

}

template <typename T, typename Q>
bool contains_value(const std::multimap<T, Q> &mmp, const T& key, const Q& value) {

	for (auto [it, end] = mmp.equal_range(key); it != end; ++it) {
		if (it->second == value) {
			return true;
		}
	}

	return false;
}

}
