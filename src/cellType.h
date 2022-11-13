namespace CellType {
	enum Type { intType, doubleType, stringType };
}

struct CellToString {
	auto operator()(std::string x) const { return x; }
	auto operator()(double x) const { return std::to_string(x); }
	auto operator()(int x) const { return std::to_string(x); }
};
struct GetCellType {
	CellType::Type operator()(std::string x) const { return CellType::stringType; }
	CellType::Type operator()(double x) const { return CellType::doubleType; }
	CellType::Type operator()(int x) const { return CellType::intType; }
};

std::variant<int, double, std::string> GetInitialValue(CellType::Type type) {
	if (type == CellType::intType)
		return 0;
	else if (type == CellType::doubleType)
		return 0.0;
	else if (type == CellType::stringType)
		return std::string{};
	else
		throw "Wrong type is supplied.";

};