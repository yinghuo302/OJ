#include <bits/stdc++.h>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
unordered_map<char,int> hex_mp = {
    {'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},
    {'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15}
};
const string _hex = "0123456789abcdef";
string addressDec(const string& s){
    auto str = s;
    int i = str.size()-1;
    for(;i>=0;i--){
        if(str[i]==':') continue;
        if(str[i]=='0') {str[i] = 'f'; continue;}
        int num = hex_mp[str[i]];
        str[i] = _hex[num-1];
        break;
    }
    if(i==-1)
        str[0] = '-';
    return str;
}
string addressInc(const string& s){
    auto str = s;
    int i = str.size()-1;
    for(;i>=0;i--){
        if(str[i]==':') continue;
        if(str[i]=='f') {str[i] = '0'; continue;}
        int num = hex_mp[str[i]];
        str[i] = _hex[num+1];
        break;
    }
    if(i==-1)
        str[0] = '+';
    return str;
}
struct Cmp{
    bool operator()(const string& s,const string& other) const {
        if(s[0]=='-') return true;
        if(s[0]=='+') return false;
        if(other[0]=='+') return true;
        if(other[0]=='-') return false;
        int size = s.size();
        for(int i = 0;i<size;i++){
            int num1 = hex_mp[s[i]],num2 = hex_mp[other[i]];
            if(num1==num2) continue;
            return num1 < num2; 
        }
        return false;
    }
};
bool addressEqual(const string& s,const string& other) {
    if(s[0]=='-'&&other[0]=='-') return true;
    if(s[0]=='+'&&other[0]=='+') return true;
    return s == other;
}
class ODT{
public:
    struct Node{
        int id;
        string right;
        Node() = default;
        Node(string right,int id):id(id),right(right){}
    };
    map<string,Node,Cmp> mp;
    map<string,Node>::iterator split(string mid){
        auto iter = mp.lower_bound(mid);
        if(iter!=mp.end()&&iter->first==mid)
            return iter;
        --iter;
        auto node = iter->second;
        iter->second.right = addressDec(mid);
        return mp.emplace(mid,node).first;
    }
}odt;
string l,r;int id;
bool apply(){
    auto it_r = odt.split(addressInc(r)), it_l = odt.split(l);
    unordered_set<int> users;
    f_2(it,it_l,it_r){
        if(it->second.id!=0&&it->second.id!=id)
            return false;
        users.emplace(it->second.id);
    }
    if(users.size()==1&&*users.begin()==id) return false;
    odt.mp.erase(it_l,it_r);
    odt.mp.emplace(l,ODT::Node(r,id));
    return true;
}
int queryAddress(){
    auto iter = odt.mp.upper_bound(l);iter--;
    return iter->second.id;
}
int queryRange(){
    auto it_r = odt.split(addressInc(r)), it_l = odt.split(l);
    unordered_set<int> users;
    f_2(it,it_l,it_r){
        users.emplace(it->second.id);
    }
    return users.size()==1? *users.begin() : 0;
}
string makeAddress(int n,char c,char first){
    string str;
    for(int i=16;i<n;i+=16){
        str += string(4,c);
        str += ':';
    }
    str += string(4,c);
    str[0] = first;
    return str;
}
int main(){
    int n,q; char op;
    cin >> n >> q;
    // -0000:0000 fu wuqiong +fff:ffff zheng wuqiong
    odt.mp.emplace(makeAddress(n,'0','-'),ODT::Node(makeAddress(n,'f','+'),0));
    for(int i=0;i<q;i++){
        cin >> op;
        switch (op){
            case '1': cin  >> id >> l >> r; cout << (apply() ? "YES":"NO" ) <<'\n'; break;
            case '2': cin >> l; cout << queryAddress() <<'\n';; break;
            case '3': cin >> l >> r; cout << queryRange() <<'\n';; break;
        }
    }
    return 0;
}