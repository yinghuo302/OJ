/*
 * @Author: zanilia
 * @Date: 2022-09-10 14:58:52
 * @LastEditTime: 2023-02-27 22:11:17
 * @Descripttion: 
 */
#include <iostream>
#include <vector>
#include <set>
using namespace std;
int n;
const int mod = 1e9+7;
int a[1001];
long long dp[1001];
vector<int> f[100005];
set<int> st;
void init(){
	int m = a[n-1] / 2+1;
	for(int i=1;i<m;++i){
		for(int j=i*2;j<=a[n-1];j+=i){
			f[j].push_back(i);
		}
	}
}
int calculate(int l,int r){
	int x = a[r] - a[l];
	st.emplace(x);
	int ans = 0;
	for(auto &fac:f[x]){
		if(st.count(fac))
			continue;
		st.emplace(fac);
		ans++;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin >> n;
	for(int i=1;i<n;++i){
		cin >> a[i];
	}
	dp[0] = 1;
	init();
	for(int i=1;i<n;++i){
		st.clear();
		long long sum = 0;
		for(int j=i-1;j>=0;--j){
			int t =  calculate(j,i);
			sum = (sum +  dp[j] *t )%mod;
		}
		dp[i] = sum %mod;
	}
	cout << dp[n-1];
	return 0;
}