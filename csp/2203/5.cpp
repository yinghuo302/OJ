/*
 * @Author: zanilia
 * @Date: 2022-09-06 11:47:48
 * @LastEditTime: 2023-03-11 15:47:56
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int nums[100001];
int n,k;
int func1(){
	int tmp = 0,ans, m = n/2;
	for(int i=0;i<=m;i++)
		tmp += nums[i];
	ans = tmp;
	for(int i=m+1;i<n;i++){
		tmp += nums[i] - nums[i-m-1];
		ans = min(tmp,ans);
	}
	return ans;
}
template<class RAIterator,class Function>
RAIterator upperBound(RAIterator begin,RAIterator end,Function f){
	RAIterator ret = end;
	if(f(--end)<=0)
		return ret;
	while(begin<end){
		RAIterator mid = (end-begin)/2+begin;
		int t = f(mid);
		if(t>0)
			end = mid;
		else
			begin = mid+1;
	}
	return begin;
}
int func2(){
	auto check = [&](int x){
		int sum = 0,cnt = 0;
		for(int i=0;i<n;i++){
			sum += nums[i];
			if(sum>=x){
				cnt++;
				sum = 0;
			}
		}
		return cnt <= n/2;
	};
	return upperBound(0,int(1e9),check)-1;
}
// n为偶数， c先手 k=0 c: n/2,z:n-1/2; z先手 k=1 c: n-1/2, z:n/2;
// n为奇数， 两个都是 n/2
int main(){
	cin >> n >> k;
	for(int i=0;i<n;i++)
		cin >> nums[i];
	if(((n%2==0)&&k==1)||(n%2==1)&&k==0) cout << func1();
	else cout << func2();
	return 0;
}