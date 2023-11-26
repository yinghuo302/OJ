/*
 * @Author: zanilia
 * @Date: 2023-03-13 18:20:01
 * @LastEditTime: 2023-03-13 20:31:16
 * @Descripttion: 
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long dp[100001],pre_v[100001];
int v[100001],m[100001],idx[100001],queue[100001],idx_t[100001];
int n,L,head,tail;
inline long long X(int j){return pre_v[j];}
inline long long K(int i){return 2ll*pre_v[i];}
inline long long Y(int j){return dp[j]+pre_v[j]*(pre_v[j]+2*L);}
inline double slope(int i,int j) {if(i==j) return 0; return (Y(i)-Y(j))/(double)(X(i)-X(j));}
inline void update(int i,int j){
	dp[i] = min(dp[j]+(L-pre_v[i]+pre_v[j])*(L-pre_v[i]+pre_v[j]),dp[i]);
}
void solve(int l,int r){
	if(l>=r) { update(idx[l],0); return ; }
	int mid = l + (r-l)/2;
	solve(l,mid);
	head = 0; tail = -1;
	for(int i=l;i<=mid;i++) idx_t[i] = idx[i];
	for(int i=mid+1;i<=r;i++) idx_t[i] = idx[i];
	int j=l;
	sort(idx_t+l,idx_t+mid+1);
	sort(idx_t+mid+1,idx_t+r+1);
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&idx_t[j]<idx_t[i]){
			while(head<tail&&slope(queue[tail],queue[tail-1])>slope(j,queue[tail]))
				--tail;
			queue[++tail] = idx_t[j++];
		}
		while(head<tail&&slope(queue[head],queue[head+1])<K(i))
			++head;
		update(idx_t[i],queue[head]);
	}
	solve(mid+1,r);
}
int main(){
	cin >> n >> L;
	v[0] = m[0] = pre_v[0] = dp[0] = idx[0] = 0;
	for(int i=1;i<=n;i++){
		cin >> v[i];
		pre_v[i] = pre_v[i-1] + v[i];
		idx[i] = i;
		dp[i] = INT64_MAX/2;
	}
	for(int i=1;i<=n;i++)
		cin >> m[i];
	sort(idx+1,idx+n+1,[&](int a,int b){
		return m[a] < m[b];
	});
	solve(1,n);
	cout << dp[n];
	return 0;
}