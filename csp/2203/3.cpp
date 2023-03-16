/*
 * @Author: zanilia
 * @Date: 2022-09-04 23:17:07
 * @LastEditTime: 2023-03-01 19:59:20
 * @Descripttion: 
 */
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
struct Node{
	unordered_set<int> tasks;
	int area;
};
struct Area{
	vector<int> nodes;
	unordered_set<int> tasks;
};
Node nodes[1001];
Area areas[1001];
int cnt[1001] = {0};
int n,m,g,f,a,na,pa,paa,paar;
vector<int> affinity;
vector<int> antiaffinity;
int main(){
	affinity.reserve(1001);
	antiaffinity.reserve(1001);
	cin >> n >> m;
	for(int i=1;i<=n;++i){
		int tmp;
		cin >> tmp;
		nodes[i].area = tmp;
		areas[tmp].nodes.push_back(i);
		areas[0].nodes.push_back(i);
	}
	cin >> g;
	for(int i=0;i<g;++i){
		cin >> f >> a >> na >> pa >> paa >> paar;
		for(int j=0;j<f;j++){
			affinity.clear();
			antiaffinity.clear();
			copy_if(areas[na].nodes.begin(),areas[na].nodes.end(),back_inserter(affinity),[&](int node){
				return pa==0 || areas[nodes[node].area].tasks.count(pa);
			});
			copy_if(affinity.begin(),affinity.end(),back_inserter(antiaffinity),[&](int node){
				return paa==0 || (nodes[node].tasks.count(paa)==0);
			});
			vector<int>* available;
			if(antiaffinity.empty()&&paar==0){
				available = &affinity;
			}else{
				available = &antiaffinity;
			}
			if(available->empty()){
				cout << "0 ";
			}else{
				int ans = (*available)[0];
				for(auto& node:(*available)){
					if(cnt[node]<cnt[ans])
						ans = node;
				}
				cout << ans << ' ';
				cnt[ans]++;
				nodes[ans].tasks.emplace(a);
				areas[nodes[ans].area].tasks.emplace(a);
			}
		}
		cout << '\n';
	}
	return 0;
}