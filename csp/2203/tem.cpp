/*
 * @Author: zanilia
 * @Date: 2023-03-11 16:35:29
 * @LastEditTime: 2023-03-15 22:10:27
 * @Descripttion: 
 */
#include <bits/stdc++.h>

typedef long long ll;
const int maxn = 100010;
const int inf = ~(1u << 31u);
const ll linf = ~(1llu << 63u);
using namespace std;

struct node{
	ll value;
	int to;
	node(ll value, int to) : value(value), to(to) {}
	bool operator < (const node &d) const {
		return value == d.value ? to < d.to : value > d.value;
	}
};

struct info{
	int u, v, x;
	info(int u, int v, int x) : u(u), v(v), x(x) {}
};

set <node> d[maxn];
unordered_map<long long, ll> save;
inline long long mypair(long long u,long long v){
	return (u<<30)|v;
}

vector <info> deActive[maxn];
int p_value, q_value;

inline int check_p(int x){
	return d[x].begin() == d[x].end() || d[x].begin()->value == 0;
}

inline int check_q(int x){
	if(check_p(x)) return 0;
	int y = d[x].begin()->to;
	return !check_p(y) && d[y].begin()->to == x;
}

void work(int u, int v, int x){
	p_value -= check_p(u);
	q_value -= check_q(u);
	ll tmp_p = mypair(u,v);
	ll orgValue = save[tmp_p];
	save[tmp_p] += x;
	node org(orgValue, v);
	d[u].erase(org);
	d[u].emplace(save[tmp_p], v);
	p_value += check_p(u);
	q_value += check_q(u);
}

int main(){
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	p_value = n;
	q_value = 0;
	for(int i = 1; i <= m; ++i){
		for(const auto &x : deActive[i]){
			work(x.u, x.v, -x.x);
			work(x.v, x.u, -x.x);
		}
		int k;
		cin >> k;
		for(int j = 1; j <= k; ++j){
			int u, v, x, y;
			cin >> u >> v >> x >> y;
			if(i + y <= m)
				deActive[i + y].emplace_back(u, v, x);
			work(u, v, x);
			work(v, u, x);
		}
		int l;
		cin >> l;
		for(int j = 1; j <= l; ++j){
			int x;
			cin >> x;
			if(check_p(x)) cout << 0 << "\n";
			else cout << d[x].begin()->to << "\n";
		}
		int p, q;
		cin >> p >> q;
		if(p) cout << p_value << "\n";
		if(q) cout << q_value << "\n"; 	
	}
	return 0;
}