#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Set {
 public:
  vector<int64_t> MSet;
  explicit Set(const vector<int64_t> &v) {
    for (int i = 0; i < v.size(); i++) {
      if (find(MSet.begin(), MSet.end(), v[i]) == MSet.end()) {
        MSet.push_back(v[i]);
      }
    }
  }
  Set() {}
  Set Union(const Set& st) {
    Set nwst(MSet);
    for (int i = 0; i < st.MSet.size(); i++) {
      if (find(MSet.begin(), MSet.end(), st.MSet[i]) == MSet.end()) {
        nwst.MSet.push_back(st.MSet[i]);
      }
    }
    return nwst;
  }
  Set Intersection(const Set& st) {
    Set nwst;
    for (int i = 0; i < st.MSet.size(); i++) {
      if (find(MSet.begin(), MSet.end(), st.MSet[i]) != MSet.end()) {
        nwst.MSet.push_back(st.MSet[i]);
      }
    }
    return nwst;
  }
  Set Difference(const Set& st) {
    Set nwst(MSet);
    for (int i = 0; i < st.MSet.size(); i++) {
      if (find(MSet.begin(), MSet.end(), st.MSet[i]) != MSet.end()) {
        nwst.MSet.erase(find(nwst.MSet.begin(), nwst.MSet.end(), st.MSet[i]));
      }
    }
    return nwst;
  }
  Set SymmetricDifference(const Set& st) {
    Set nwst, subst1(MSet), subst2(st.MSet);
    nwst = subst1.Difference(st).Union(subst2.Difference(subst1));
    return nwst;
  }
  void Add(int64_t a) {
    if (find(MSet.begin(), MSet.end(), a) == MSet.end()) MSet.push_back(a);
  }
  void Remove(int64_t a) {
    vector<int64_t>::iterator it;
    it = find(MSet.begin(), MSet.end(), a);
    if (it != MSet.end()) MSet.erase(it);
  }
  bool Contains(int64_t a) {
    if (find(MSet.begin(), MSet.end(), a) != MSet.end()) return true;
    else
      return false;
  }
  vector<int64_t> Data() {
    return(MSet);
  }
};
