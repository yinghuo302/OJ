/*
 * @Author: zanilia
 * @Date: 2023-03-04 14:32:29
 * @LastEditTime: 2023-03-04 17:39:44
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
#define MOD 998244353
// vector<int> pre[14] = {
// 	{2},{0},{1,3},{2,3},{2},{}
// };
vector<int> pre[14] = {
	{4},{1},{2,6},{4,6},{4},{16},{64},{61},{62},{26,66},{44},{41},{6,42},{46}
};
unordered_map<int,int> mp = {
	{1,0},{2,1},{4,2},{6,3},{16,4},{26,5},{41,6},
	{42,7},{44,8},{46,9},{61,10},{62,11},{64,12},{66,13}
};
typedef long long ll;
ll dp[2][14] = {{1},{0}};
ll n; char str[100001]; 
ll calculate(int c){
	for(int i=1;i<=n;i++){
		int curr = i&1, prev = curr^1;
		for(int j=0;j<14;j++){
			ll tmp = 0;
			for(auto p:pre[j])
				tmp += dp[prev][p];
			dp[curr][j] = tmp%MOD;
		}
	}
	return dp[n&1][mp[c]];
}
int main(){
	cin >> n >> str;
	if(str[2]!='\0')
		cout << 0;
	else if(str[1]=='\0')
		cout << calculate(*str-'0');
	else
		cout << calculate((*str-'0')*10+(str[1]-'0'));
	return 0;
}