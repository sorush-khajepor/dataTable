using Row = std::vector<std::variant<int, double, std::string>>;

template<class T>
auto dropFirstItem(const std::vector<T>& v) {
	std::vector<T> result;
	result.insert(result.begin(), v.begin() + 1, v.end());
	return result;
}

bool less_comp(const Row& row1, const Row& row2) {
	auto s1 = std::get<std::string>(row1[0]);
	auto s2 = std::get<std::string>(row2[0]);
	return s1.compare(s2) < 0;
}