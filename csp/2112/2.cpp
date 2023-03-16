/*
 * @Author: zanilia
 * @Date: 2022-09-07 22:06:14
 * @LastEditTime: 2022-09-08 10:44:29
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
typedef long long ll;
ll n,N,pre = 0,num,r,ans= 0;
inline ll myabs(ll a){
	return a>0? a : -a;
}
inline void calculate(ll begin,ll end,ll i){   // [begin,end)
	ll left = begin / r, right = end / r;
	if(left==right){
		ans += (end-begin)*myabs(i-left); 
	}else{
		ans += (r-begin%r)*myabs(i-left);
		ans += (end%r)*myabs(i-right);
	}
	for(ll j=left+1;j<right;++j){
		ans += r * myabs(j-i);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> N;
	r = N/(n+1);
	for(ll i=0;i<n;++i){
		cin >> num;
		calculate(pre,num,i);		
		pre = num;
	}
	calculate(pre,N,n);
	cout << ans;
	return 0;
}