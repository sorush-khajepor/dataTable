#include<iostream>
#include<vector>
#include<array>
#include<any>
#include<variant>
#include<algorithm>
#include<string>
#include"setPermutation.h"
#include"cellType.h"
#include"helpers.h"


class DataTable {
	using Cell = std::variant<int, double, std::string>;
	using Row = std::vector<Cell>;
	std::vector<Row> rows;
	std::vector<std::string> properties;
	std::vector<CellType::Type> columnTypes;

public:
	auto AddColumn(std::string header, CellType::Type type) {
		properties.push_back(header);
		columnTypes.push_back(type);
		for (auto& row : rows) {
			row.push_back(GetInitialValue(type));
		}
	}

	auto GetColumnsSize() const {
		return properties.size();
	}
	auto GetRowsSize() const {
		return rows.size();
	}
	auto AddEmptyRow() {
		Row row;
		for (auto& type : columnTypes) {
			row.push_back(GetInitialValue(type));
		}
		rows.push_back(row);
	}
	auto IsValidRow(const Row& row) {

		if (row.size() != GetColumnsSize())
			return false;

		std::vector<CellType::Type> types;
		for (auto& item : row)
			types.push_back(std::visit(GetCellType(), item));

		for (size_t i = 0; i < row.size(); ++i) {
			if (types[i] != columnTypes[i])
				return false;
		}

		return true;
	}
	auto AddRow(const Row& row) {
		if (!IsValidRow(row))
			throw "Invalid row passed to AddRow().";
		rows.push_back(row);
	}


	void SortRowsByMolecules() {
		std::sort(rows.begin(), rows.end(), less_comp);
	}

	/* Finds the union of this table and another one.
	*  Returns the outcome in new table.
	*  Assumes both tables are sorted by molecules.
	*  Assumes both tables have same properties.
	*/
	auto UnionRowsByMolecules(const DataTable& other) {
		DataTable r;
		r.properties = properties;
		r.columnTypes = columnTypes;
		std::set_union(rows.begin(), rows.end(),
			other.rows.begin(), other.rows.end(),
			std::back_inserter(r.rows), less_comp);
		return r;
	}

	/* Finds the difference of this table with another one.
	* Returns the outcome in new table.
	* Assumes both tables are sorted by molecules.
	* Assumes both tables have same properties.
	*/
	auto DifferenceRowsByMolecules(const DataTable& other) {
		DataTable r;
		r.properties = properties;
		r.columnTypes = columnTypes;
		std::set_difference(rows.begin(), rows.end(),
			other.rows.begin(), other.rows.end(),
			std::back_inserter(r.rows), less_comp);
		return r;
	}
	/* Finds the Intersection of this table with another one.
	* Returns the outcome in new table.
	* Assumes both tables are sorted by molecules.
	* Assumes both tables have same properties.
	*/
	auto IntersectionRowsByMolecules(const DataTable& other) {
		DataTable r;
		r.properties = properties;
		r.columnTypes = columnTypes;
		std::set_intersection(rows.begin(), rows.end(),
			other.rows.begin(), other.rows.end(),
			std::back_inserter(r.rows), less_comp);
		return r;
	}


	/* Finds the union of two rows.
	* The sort permutations of both rows and the union
	* permutations are needed.
	*/
	template<class T>
	auto UnionRows(const std::vector<T>& row1, const std::vector<T>& row2, std::vector<size_t> sortPerm1, std::vector<size_t> sortPerm2, std::vector<size_t> unionPerm) {
		// first column of each row is a molecule name which is not touched.
		auto v1 = dropFirstItem(row1);
		auto v2 = dropFirstItem(row2);
		v1 = ApplyPermutation(v1, sortPerm1);
		v2 = ApplyPermutation(v2, sortPerm2);
		auto unions = SetFromPermutation(v1, v2, unionPerm);
		unions.insert(unions.begin(), row1[0]);
		return unions;
	}

	/*  Returns a new DataTable which is the union of this table and
		another one. This union assumes both tables have same molecules
		but different/common properties.
	*/
	auto UnionColumnsByProperties(const DataTable& other) {
		// Stage 1: union and corresponding permutations for peroperties 
		// of two tables are found.

		// First column of each row is a molecule name which is not touched.
		auto properties1 = dropFirstItem(properties);
		auto properties2 = dropFirstItem(other.properties);

		// sort is necessary before union
		auto sortPerm1 = Sort(properties1);
		auto sortPerm2 = Sort(properties2);

		auto [unionProperties, unionPerm] = SetUnion(properties1, properties2);

		// Insert back molecule header
		unionProperties.insert(unionProperties.begin(), properties[0]);

		// Stage 2: the permutations of stage 1 is applied to the rows 
		// of two tables to find the union row of the outcome.
		DataTable dt;
		dt.properties = unionProperties;
		dt.columnTypes = UnionRows(columnTypes, other.columnTypes, sortPerm1, sortPerm2, unionPerm);
		dt.rows.resize(rows.size());
		for (size_t i = 0; i < rows.size(); ++i)
			dt.rows[i] = UnionRows(rows[i], other.rows[i], sortPerm1, sortPerm2, unionPerm);

		return dt;
	}

	/* Print this table on screen.*/
	auto Print() {
		for (auto& row : rows) {
			for (auto& item : row)
				std::cout << std::visit(CellToString(), item) << " ";
			std::cout << "\n";
		}
		std::cout << "===\n\n";
	}



};
