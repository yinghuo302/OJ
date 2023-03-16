/*
 * @Author: zanilia
 * @Date: 2023-03-10 16:33:59
 * @LastEditTime: 2023-03-15 20:57:16
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
using namespace std;
struct Node{
	int u;
	long long traffic;
	Node() = default;
	Node(int u,long long traffic):traffic(traffic),u(u){}
	bool operator<(const Node& other) const {
		if(traffic==other.traffic) return u > other.u;
		return traffic < other.traffic;
	}
};
struct Apply{
	int u,v;
	long long traffic;
	Apply() = default;
	Apply(int u,int v,long long traffic):u(u),v(v),traffic(traffic){}
};
struct Pair{
	int u,v;
	Pair() = default;
	Pair(int u,int v):u(max(u,v)),v(min(u,v)){}
};
struct MyHash{
	size_t operator()(const Pair& p) const {
		return hash<int>()(p.u) ^ hash<int>()(p.v);
	}
};
struct Equal{
	bool operator()(const Pair& p1,const Pair& p2) const {
		return p1.u==p2.u && p1.v == p2.v;
	}
};
vector<Apply> expire[100001];
unordered_map<int,set<Node>> traffic_mp;
unordered_map<Pair,int,MyHash,Equal> pair_mp;
Pair tmp_p; Apply tmp_a;
unordered_set<int> not_island;
int master_obj[100001] = {0};
int n,m,k,y,l,query,master_cnt;
bool p,q;
void updateState(int u){
	int now_master = 0;
	if(traffic_mp[u].empty())
		not_island.erase(u);
	else{
		not_island.insert(u);
		now_master = traffic_mp[u].rbegin()->u;
	}
	int pre_master = master_obj[u];
	if(pre_master!=now_master){
		if(master_obj[pre_master]==u)
			--master_cnt;
		if(now_master!=0&&master_obj[now_master]==u)
			++master_cnt;
		master_obj[u] = now_master;
	}
}
void updateTraffic(Apply& ap){
	tmp_p = Pair(ap.u,ap.v);
	long long old_traffic = 0;
	if(pair_mp.count(tmp_p))
		old_traffic = pair_mp[tmp_p];
	long long now_traffic = old_traffic + ap.traffic;
	pair_mp.erase(tmp_p);
	traffic_mp[ap.u].erase(Node(ap.v,old_traffic));
	traffic_mp[ap.v].erase(Node(ap.u,old_traffic));
	if(now_traffic!=0){
		traffic_mp[ap.u].insert(Node(ap.v,now_traffic));
		traffic_mp[ap.v].insert(Node(ap.u,now_traffic));
		pair_mp[tmp_p] = now_traffic;
	}
	updateState(tmp_p.u);
	updateState(tmp_p.v);	
}
int main(){
	cin >> n >> m;
	for(int i=1;i<=m;++i){
		for(auto& ap:expire[i])
			updateTraffic(ap);
		expire[i].clear();
		cin >> k;
		for(int j=0;j<k;++j){
			cin >> tmp_a.u >> tmp_a.v >> tmp_a.traffic >> y;
			updateTraffic(tmp_a);
			tmp_a.traffic = -tmp_a.traffic;
			if(i+y<=m)
				expire[i+y].emplace_back(tmp_a);
		}
		cin >> l;
		for(int j=0;j<l;++j){
			cin >> query;
			cout << master_obj[query] << '\n';
		}
		cin >> p >> q;
		if(p)
			cout << n - not_island.size() << '\n';
		if(q)
			cout << master_cnt << '\n';
	}
}