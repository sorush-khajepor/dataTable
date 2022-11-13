#include <iostream>
#include <vector>
#include <array>
#include <any>
#include<variant>
#include<algorithm>
#include<tuple>


/*  Returns permutations needed to sort a vector<string>. 
    It doesn't sort the vector. For example for 
    v = {"c","a","b"}, we get  {2, 0, 1}:
    so "c" must go to position 2, "a" to 0 and so on.*/
auto GetSortPermutation(const std::vector<std::string>& data){
    std::vector<size_t> perm(data.size());
    for (size_t i = 0 ; i < perm.size() ; ++i) 
        perm[i] = i;

    std::sort(perm.begin(), perm.end(),
        [&](const size_t& a, const size_t& b) {
            return (data[a].compare(data[b])<0);
        }
    );
    return perm;
}

/* Applies a permutation vector, p, to an arbitrary vector, v, and
    a new rearranged vector as returned.*/
template<class T>
auto ApplyPermutation(const std::vector<T>& v, const std::vector<size_t>& p) {
    std::vector<T> result(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        result[i] = v[p[i]];
    return result;
}

/*  Sort a vector<string> and returns a the permutation vector
    that is used for the sort.*/
auto Sort(std::vector<std::string>& v){
    auto perm = GetSortPermutation(v);
    v=ApplyPermutation(v, perm);
    return perm;
}

/*  Returns a permutation vector that makes a union of two vector<string>.
    The vectors need to be sorted.
    The permutatoin vector includes indexes of both data1 and data2. 
    But, there, indexes of of data2 start from data1.size(). */
auto GetUnionPermutation(const std::vector<std::string>& data1, const std::vector<std::string>& data2){
    std::vector<size_t> index(data1.size()+data2.size());
    std::vector<size_t> perm;
    for (size_t i = 0 ; i < index.size() ; ++i) {
        index[i] = i;
    }
    std::set_union(index.begin(),index.begin()+data1.size(),
              index.begin()+data1.size(),index.end(),
            std::back_inserter(perm),
        [&](const size_t& a, const size_t& b) {
            std::string sa, sb;
            a<data1.size()? sa=data1[a]: sa=data2[a-data1.size()];
            b<data1.size()? sb=data1[b]: sb=data2[b-data1.size()];
            return (sa.compare(sb)<0);
        }
    );
    return perm;
}


/* Receives two vectors, v1 and v2, and their union permutation, and
   returns a new union vector of v1 and v2. */
template<class T>
auto SetFromPermutation(const std::vector<T>& v1, const std::vector<T>& v2, const std::vector<size_t>& p){
    std::vector<T> result(p.size());
    for (size_t i=0; i<p.size();++i){
        p[i]<v1.size()? result[i]=v1[p[i]]: 
                        result[i]=v2[p[i]-v1.size()];
    }
    return result;
}

/* Finds union of two vector<string>, v1 and v2, and 
    returns a tuple of the union and permutations used.
    v1 and v2 need to be sorted.*/
auto SetUnion(const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
    auto perm=GetUnionPermutation(v1, v2);
    auto unions = SetFromPermutation(v1, v2, perm);
    return std::make_tuple(unions, perm);
}
