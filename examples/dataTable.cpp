
#include "../src/dataTable.h"

using namespace std;

int main() {
    using Row = std::vector<std::variant<int, double, std::string>>;
    DataTable dt1;
    dt1.AddColumn("Molecule", CellType::stringType);
    dt1.AddColumn("Molecular Weight", CellType::intType);
    dt1.AddColumn("Solubility", CellType::doubleType); 

    dt1.AddRow(Row{ "Cxx",1, 1.1 });
    dt1.AddRow(Row{ "Axx",2, 2.2 });
    dt1.AddRow(Row{ "Bxx",3, 3.3 });


    DataTable dt2=dt1;
    dt2.AddRow(Row{ "Fxx",4, 4.4 });
    dt2.AddRow(Row{ "Gxx",5, 5.5 });
    dt2.AddRow(Row{ "Dxx",6, 6.6 });

    DataTable dt3;
    dt3.AddColumn("Molecule", CellType::stringType);
    dt3.AddColumn("Molecular Weight", CellType::intType);
    dt3.AddColumn("Color", CellType::stringType);

    dt3.AddRow(Row{ "Axx",2, "red  "});
    dt3.AddRow(Row{ "Cxx",1, "blue " });
    dt3.AddRow(Row{ "Bxx",3, "white"});
    
    
    cout << "Input Tables:\ndt1:\n";
    dt1.Print();
    cout << "dt2:\n";
    dt2.Print();
    cout << "dt3:\n";
    dt3.Print();

    {
        auto dt = dt1;
        dt.SortRowsByMolecules();
        cout << "dt1 sorted by molecules:\n";
        dt.Print();
    }
    {
        auto dt10 = dt1;
        dt10.SortRowsByMolecules();

        auto dt20 = dt2;
        dt20.SortRowsByMolecules();

        cout << "Union dt1 and dt2 (different molecules, same properties):\n";
        dt10.UnionRowsByMolecules(dt20).Print();

        cout << "Difference dt2 - dt1:\n";
        dt20.DifferenceRowsByMolecules(dt10).Print();
        
        cout << "Intersection dt1 and dt2:\n";
        dt10.IntersectionRowsByMolecules(dt20).Print();
    }
    {
        auto dt10 = dt1;
        auto dt30 = dt3;
        dt10.SortRowsByMolecules();
        dt30.SortRowsByMolecules();
        
        cout << "Union dt1 and dt3 (same molecules, different/common properties):\n";
        dt10.UnionColumnsByProperties(dt30).Print();
    }

    return 0;
}