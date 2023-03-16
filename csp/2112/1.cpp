/*
 * @Author: zanilia
 * @Date: 2022-09-07 21:43:23
 * @LastEditTime: 2022-09-07 22:02:44
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
long long n,N,num,pre = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> N;
	long long ans;
	for(long long i=0;i<n;++i){
		cin >> num;
		if (num>pre)
			ans += i*(num-pre);
		pre = num;
	}
	if (N>pre)
		ans += n*(N-pre);
	cout << ans;
	return 0;
}