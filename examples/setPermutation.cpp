#include "../src/setPermutation.h"
#include<string>
using namespace std;

template<class T>
void print(string message, const vector<T>& v) {
    cout << message+"\n";
    for (auto& m : v)
        cout << m << " ";
    cout << "\n\n";
}

int main(){

    vector<string> s1{"b", "a", "n", "m"};
    vector<string> s2{"a", "b", "c", "d","e"};

    print("s1:", s1);

    {
        auto s10 = s1;
        auto perm = Sort(s10);
        
        print("s1 sorted:", s10);
        print("Permutations for the sort was:", perm);
    }
    
    {
        auto s10 = s1;
        auto s20 = s2;
        Sort(s10);
        Sort(s20);
        auto [unions, perm]=SetUnion(s10, s20);
        
        print("s1 sorted:", s10);
        print("s2 sorted:", s20);
        print("union is:", unions);
        print("permutations for unions was: \nindexes of s2 start from "+to_string(s1.size()), perm);

    }

    return 0;
}
