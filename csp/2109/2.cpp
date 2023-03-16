/*
 * @Author: zanilia
 * @Date: 2022-09-17 16:30:03
 * @LastEditTime: 2023-02-27 22:12:28
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int diff[10001] = {0};
int pre = 0,num,n;
int sum = 0,ans = 0;
int main(){
	cin >> n;
	for(int i=0;i<n;++i){
		cin >> num;
		if(num>pre){
			diff[pre+1]++;
			diff[num+1]--;
		}
		pre = num;
	}
	for(int i=0;i<10001;++i){
		sum += diff[i];
		ans = max(sum,ans);
	}
	cout << ans;
	return 0;
}