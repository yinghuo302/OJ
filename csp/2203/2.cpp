/*
 * @Author: zanilia
 * @Date: 2022-09-03 19:30:24
 * @LastEditTime: 2022-09-03 21:38:08
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int pre_sum[300005] = {0};
int n,m,k,t,c;
int main(){
	cin >> n >> m >> k;
	for(int i=0;i<n;++i){
		cin >> t >> c;
		pre_sum[t+1]--;
		if(t-c-k<0)
			pre_sum[1]++;
		else
			pre_sum[t-c+1]++;
	}
	for(int i=0;i<300004;++i)
		pre_sum[i+1] += pre_sum[i];
	for(int i=0;i<m;++i){
		cin >> t;
		cout << pre_sum[t+k] << '\n';
	}
	return 0;
}