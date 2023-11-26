/*
 * @Author: zanilia
 * @Date: 2023-03-01 22:13:36
 * @LastEditTime: 2023-03-04 19:04:12
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
long long dp[100001],v[100001] = {0},m[100001] = {0},pre_v[100001] = {0};
long long n,L;
int main(){
	cin >> n >> L;
	for(long long i=1;i<=n;i++){
		cin >> v[i];
		pre_v[i] = pre_v[i-1] + v[i];
	}
	for(long long i=1;i<=n;i++)
		cin >> m[i];
	dp[0] = 0;
	for(long long i=1;i<=n;i++){
		dp[i] = INT64_MAX/2;
		for(long long j=i-1;j>=0;j--){
			if(m[i]>m[j])
				dp[i] = min(dp[j]+(L-pre_v[i]+pre_v[j])*(L-pre_v[i]+pre_v[j]),dp[i]);
		}
	}
	cout << dp[n];
	return 0;
}