#include <bits/stdc++.h>
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
typedef long long ll;
using namespace std;
string expre;
unordered_set<int> all_st;
unordered_map<ll,unordered_set<int>> equal_st;
unordered_map<int,unordered_set<int>> has_st;
inline ll mypair(ll attr,ll value){
    return (attr << 32) | value;
}
//  assert 符合 BNF 语法 BASE_EXPR。
inline unordered_set<int> singleCheck(int left,int right){
    stringstream ss(expre.substr(left,right-left+1));
    ll attr,value; char op;
    ss >> attr >> op >> value;
    auto& st = equal_st[mypair(attr,value)];
    if(op==':')
        return st;
    unordered_set<int> ret = has_st[attr];
    for(auto& user:st)
        ret.erase(user);
    return ret;
}
inline unordered_set<int> resultMerge(char logic,unordered_set<int>& left_st,unordered_set<int>& right_st){
    unordered_set<int> ret;
    if(logic=='|'){
        for(auto& user:left_st)
            ret.emplace(user);
        for(auto& user:right_st)
            ret.emplace(user);
    }else{
        for(auto& user:left_st)
            if(right_st.count(user))
                ret.emplace(user);
    }
    return ret;
}

unordered_set<int> expreCheck(int left,int right){
    if(expre[left]!='|'&&expre[left]!='&')
        return singleCheck(left,right);
    int bra = 0;
    int split;  //  LOGIC (EXPR_L)(EXPR_R) left wei LOGIC split wei you kuohao
    for(int i=left+1;i<=right;i++){
        if(expre[i]=='(')
            ++bra;
        if(expre[i]==')')
            --bra;
        if(bra==0) { split = i;break; }
    }
    unordered_set<int> left_st = expreCheck(left+2,split-1);
    unordered_set<int> right_st = expreCheck(split+2,right-1);
    return resultMerge(expre[left],left_st,right_st);
}
inline vector<int> toSortedVector(unordered_set<int> st){
    vector<int> ret;
    ret.reserve(st.size());
    for(auto &dn:st)
        ret.emplace_back(dn);
    sort(ret.begin(),ret.end());
    return ret;
    
}
int main(){
    int n,m;
    cin >> n;
    f_2(i,0,n){
        ll dn,n_attr,attr,value;
        cin >> dn >> n_attr;
        // all_st.emplace(dn);
        f_2(j,0,n_attr){
            cin >> attr >> value;
            equal_st[mypair(attr,value)].emplace(dn);
            has_st[attr].emplace(dn);
        }
    }
    cin >> m;
    f_2(i,0,m){
        cin >> expre;
        auto ans = toSortedVector(expreCheck(0,expre.size()-1));
        for(auto &dn:ans)
            cout << dn << ' ';
        cout << '\n';
    }
    return 0;
}