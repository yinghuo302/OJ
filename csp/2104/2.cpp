/*
 * @Author: zanilia
 * @Date: 2022-09-10 13:19:22
 * @LastEditTime: 2022-09-10 16:36:29
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
#define range(i,n) for(int i=0;i<n;++i)
#define from_to(i,begin,end) for(int i=begin;i<end;++i)
int n,L,r,t;
int image[600][600];
long long pre_sum[601][601] = {0};
bool isDark(int x,int y){
	int x_begin = max(x-r,0);
	int y_begin = max(y-r,0);
	int x_end = min(x+r+1,n);
	int y_end = min(y+r+1,n);
	long long sum = pre_sum[x_end][y_end] - pre_sum[x_end][y_begin] - pre_sum[x_begin][y_end] + pre_sum[x_begin][y_begin];
	long long cnt = (x_end-x_begin)*(y_end-y_begin);
	return sum <= cnt*t;
}
int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin >> n >> L >> r >> t;
	range(i,n){
		range(j,n){
			cin >> image[i][j];
		}
	}
	from_to(i,1,n+1){
		from_to(j,1,n+1){
			pre_sum[i][j] = pre_sum[i-1][j] + pre_sum[i][j-1] - pre_sum[i-1][j-1] + image[i-1][j-1];
		}
	}
	int cnt = 0;
	range(i,n){
		range(j,n){
			if(isDark(i,j))
				++cnt;
		}
	}
	cout << cnt;
	return 0;
}