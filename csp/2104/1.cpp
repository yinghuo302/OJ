/*
 * @Author: zanilia
 * @Date: 2022-09-10 13:12:36
 * @LastEditTime: 2022-09-10 13:18:19
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
#define range(i,n) for(int i=0;i<n;++i)
int n,m,L,tem;
int cnt[300] = {0};
int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin >> n >> m >> L;
	range(i,n){
		range(j,m){
			cin >> tem;
			cnt[tem]++;
		}
	}
	range(i,L){
		cout << cnt[i] << ' ';
	}
}