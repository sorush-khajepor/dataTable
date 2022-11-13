#include <iostream>
#include <vector>
#include <array>
#include <any>
#include<variant>
#include<algorithm>



using namespace std;

int main() {

    vector<int> Data = { 4, 9, 7, 3 }; // data[posId]
    vector<int>  PosOfValue(Data.size());
    vector<int>  ValueOfPos(Data.size());
    vector<int> FinalValueOfPos = { 3, 0, 2, 1 }; // sort them with data[x], data[y], data[z]

    for (int i = 0; i < Data.size(); ++i) {
        PosOfValue[i] = i;
        ValueOfPos[i] = i;
    }

    // -1 because last item will be sorted after second last one.
    for (int i = 0; i < Data.size() - 1; ++i) {

        auto p1 = PosOfValue[FinalValueOfPos[i]];
        auto p2 = i;
        auto v1 = ValueOfPos[p1]; // or FinalValueOfPos[i]
        auto v2 = ValueOfPos[p2];

        swap(Data[p1], Data[p2]);
        swap(ValueOfPos[p1], ValueOfPos[p2]);
        swap(PosOfValue[v1], PosOfValue[v2]);

        for (int i = 0; i < Data.size(); ++i) {
            cout << Data[i];
        }
        cout << "  ";
        for (int i = 0; i < Data.size(); ++i) {
            cout << PosOfValue[i];
        }
        cout << "  ";
        for (int i = 0; i < Data.size(); ++i) {
            cout << ValueOfPos[i];
        }
        cout << "\n";
    }



}