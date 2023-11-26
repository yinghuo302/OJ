#include <bits/stdc++.h>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
#define MAX_N 50001
unordered_map<char,int> hex_mp = {
    {'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},
    {'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15},{':',16}
};
const string _hex = "0123456789abcdef";
struct OP{
	char op;
	string l;
	string r;
	int id;	
}ops[MAX_N];
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
string ips[MAX_N*4];
unordered_map<string,int> mp;
int cnt = 0;
class ODT{
public:
    struct Node{
        int right;
        int id;
		Node() = default;
		Node(int right,int id):right(right),id(id){}
    };
    map<int,Node> mp;
	ODT(){
		mp.emplace(-1,Node(MAX_N*8,0));
	}
    map<int,Node>::iterator split(int mid){
        auto iter = mp.lower_bound(mid);
        if(iter!=mp.end()&&iter->first==mid)
            return iter;
        --iter;
        auto node = iter->second;
        iter->second.right = mid-1;
        return mp.emplace(mid,node).first;
    }
}odt;
bool apply(int l,int r,int id){
    auto it_r = odt.split(r+1), it_l = odt.split(l);
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
int queryAddress(int l){
    auto iter = odt.mp.upper_bound(l);iter--;
    return iter->second.id;
}
int queryRange(int l,int r){
    auto it_r = odt.split(r+1), it_l = odt.split(l);
    unordered_set<int> users;
    f_2(it,it_l,it_r){
        users.emplace(it->second.id);
    }
    return users.size()==1? *users.begin() : 0;
}
int main(){
    int n,q; char op;
    cin >> n >> q;
    f_2(i,0,q){
        cin >> ops[i].op;
        switch (ops[i].op){
            case '1': cin  >> ops[i].id >> ops[i].l >> ops[i].r; ips[cnt++] = ops[i].l; ips[cnt++] = ops[i].r; break;
            case '2': cin >> ops[i].l; ips[cnt++] = ops[i].l;break;
            case '3': cin  >> ops[i].l >> ops[i].r;  ips[cnt++] = ops[i].l; ips[cnt++] = ops[i].r;  break;
        }
    }
	sort(ips,ips+cnt,[&](const string& a,const string& b){
		int size = a.size();
        for(int i = 0;i<size;i++){
            int num1 = hex_mp[a[i]],num2 = hex_mp[b[i]];
            if(num1==num2) continue;
            return num1 < num2; 
        }
        return false;
	});
	f_2(i,0,cnt)
		mp[ips[i]] = i*3;
	f_2(i,0,q){
		switch (ops[i].op){
            case '1': cout << (apply(mp[ops[i].l],mp[ops[i].r],ops[i].id)? "YES":"NO") << '\n'; break;
            case '2': cout << queryAddress(mp[ops[i].l]) << '\n' ;break;
            case '3': cout << queryRange(mp[ops[i].l],mp[ops[i].r]) << '\n';  break;
        }
	}
    return 0;
}