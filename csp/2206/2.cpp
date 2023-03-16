/*
 * @Author: zanilia
 * @Date: 2022-08-29 10:56:17
 * @LastEditTime: 2022-08-29 11:25:19
 * @Descripttion: 
 */
#include <unordered_set>
#include <iostream>
using namespace std;
struct Hash{
	size_t operator()(const pair<int,int>& a) const {
		return hash<int>()(a.first)^hash<int>()(a.second)+hash<int>()(a.first);
	}
};
int x,y;
int n,s,l;
bool B[51][51];
unordered_set<pair<int,int>,Hash> st;
int main(){
	std::cin >> n >> l >> s;
	for(int i=0;i<n;++i) {
		cin >> x >> y;
		st.emplace(make_pair(x,y));
	}
	for(int i=s;i>=0;--i){
		for(int j=0;j<=s;++j){
			std::cin >> B[i][j];
		}
	}
	int ans = 0;
	for(auto &location: st){
		if(location.first+s>l||location.second+s>l)
			continue;
		for(int i=0;i<=s;++i){
			for(int j=0;j<=s;++j){
				if(B[i][j]!=st.count(make_pair(location.first+i,location.second+j))){
					goto go_next;
				}
			}
		}
		++ans;
		go_next:continue;
	}
	cout << ans;
	return 0;
}