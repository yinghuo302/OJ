#include <bits/stdc++.h>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
unordered_map<char,int> hex_mp = {
    {'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},
    {'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15}
};
const string _hex = "0123456789abcdef";
class Address{
public:
    string s;
    Address() =default;
    Address(const string& s):s(s){}
    Address dec(){
        Address ret(s);
        auto& str = ret.s;
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
        return ret;
    }
    Address inc(){
        Address ret(s);
        auto& str = ret.s;
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
        return ret;
    }
    bool operator<(const Address& other) const {
        if(s[0]=='-') return true;
        if(s[0]=='+') return false;
        if(other.s[0]=='+') return true;
        if(other.s[0]=='-') return false;
        int i = s.size()-1;
        for(;i>=0;i--){
            int num1 = hex_mp[s[i]],num2 = hex_mp[other.s[i]];
            if(num1==num2) continue;
            return num1 < num2; 
        }
        return true;
    }
    bool operator==(const Address& other) const {
        if(s[0]=='-'&&other.s[0]=='-') return true;
        if(s[0]=='+'&&other.s[0]=='+') return true;
        return s == other.s;
    }
};
class ODT{
public:
    struct Node{
        int id;
        Address right;
        Node() = default;
        Node(Address right,int id):id(id),right(right){}
    };
    map<Address,Node> mp;
    map<Address,Node>::iterator split(Address mid){
        auto iter = mp.lower_bound(mid);
        if(iter!=mp.end()&&iter->first==mid)
            return iter;
        --iter;
        auto node = iter->second;
        iter->second.right = mid.dec();
        return mp.emplace(mid,node).first;
    }
}odt;
Address l,r;int id;
bool apply(){
    auto it_r = odt.split(r.inc()), it_l = odt.split(l);
    f_2(it,it_l,it_r){
        if(it->second.id!=0&&it->second.id!=id)
            return false;
    }
    odt.mp.erase(it_l,it_r);
    odt.mp.emplace(l,ODT::Node(r,id));
    return true;
}
int queryAddress(){
    return odt.mp.lower_bound(l)->second.id;
}
int queryRange(){
    auto it_r = odt.split(r.inc()), it_l = odt.split(l);
    unordered_set<int> users;
    f_2(it,it_l,it_r){
        users.emplace(it->second.id);
    }
    return users.size()==1? *users.begin() : 0;
}
Address makeAddress(int n,char c,char first){
    Address ret;
    auto& str = ret.s;
    for(int i=0;i<n;i+=4){
        str += string(4,c);
        str += ':';
    }
    str += string(4,c);
    str[0] = first;
    return ret;
}
int main(){
    int n,q; char op;
    cin >> n >> q;
    // -0000:0000 fu wuqiong +fff:ffff zheng wuqiong
    odt.mp.emplace(makeAddress(n,'0','-'),ODT::Node(makeAddress(n,'f','+'),0));
    for(int i=0;i<q;i++){
        cin >> op;
        switch (op){
            case '1': cin  >> id >> l.s >> r.s; cout << (apply() ? "YES":"NO" ); break;
            case '2': cin >> l.s; cout << queryAddress(); break;
            case '3': cin >> l.s >> r.s; cout << queryRange(); break;
        }
    }
    return 0;
}