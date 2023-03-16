/*
 * @Author: zanilia
 * @Date: 2023-03-10 16:33:59
 * @LastEditTime: 2023-03-15 21:06:24
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <cassert>
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
vector<Apply> expire[100001];
set<Node> traffic_mp[100001];
unordered_map<long long,int> pair_mp;
// unordered_set<long long> master_st;
long long tmp_p; Apply tmp_a;
// unordered_set<int> not_island;
int master_obj[100001] = {0};
int n,m,k,y,l,query,island_cnt,master_cnt;
bool p,q;
inline long long mypair(long long u,long long v){
	return (u>v)? (u<<20)|v : (v << 20) | u ;
}

inline bool check_island(int u){
	return master_obj[u] == 0;
}
inline bool check_pair(int u){
	if(check_island(u)) return false;
	int to = master_obj[u];
	return master_obj[to] == u;
}
void updateState(int u){
	master_cnt -= check_pair(u);
	island_cnt -= check_island(u);
	master_obj[u] = traffic_mp[u].empty()? 0:traffic_mp[u].rbegin()->u;
	master_cnt += check_pair(u);
	island_cnt += check_island(u);
}
void updateTraffic(Apply& ap){
	tmp_p = mypair(ap.u,ap.v);
	long long old_traffic = pair_mp[tmp_p];
	long long now_traffic = old_traffic + ap.traffic;
	pair_mp.erase(tmp_p);
	traffic_mp[ap.u].erase(Node(ap.v,old_traffic));
	traffic_mp[ap.v].erase(Node(ap.u,old_traffic));
	if(now_traffic!=0){
		traffic_mp[ap.u].insert(Node(ap.v,now_traffic));
		traffic_mp[ap.v].insert(Node(ap.u,now_traffic));
		pair_mp[tmp_p] = now_traffic;
	}
	updateState(ap.u);
	updateState(ap.v);
}

int main(){
	cin >> n >> m;
	island_cnt = n; master_cnt = 0;
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
			cout << island_cnt << '\n';
		if(q)
			cout << master_cnt << '\n';
	}
}