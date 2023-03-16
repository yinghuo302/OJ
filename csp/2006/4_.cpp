/*
 * @Author: zanilia
 * @Date: 2023-03-04 15:43:30
 * @LastEditTime: 2023-03-04 17:25:18
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
ll matrix[4][4] = {{0,1,0,0},{0,0,1,0},{1,0,0,1},{0,0,1,1}};
ll I[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
ll ans[4][4];
ll tem1[4][4],tem2[4][4];
ll begin[4] = {1,0,0,0};
ll end[4];
int n;char str[100001];
// unordered_map<int,int> mp1 = {{1,0},{2,1},{4,2},{6,3}};
unordered_map<int,int> mp = {
	{1,0},{2,1},{4,2},{6,3},{16,4},{26,5},{41,6},
	{42,7},{44,8},{46,9},{61,10},{62,11},{64,12},{66,31}
};
#define MOD 998244353
inline void copyTo(ll src[4][4],ll dst[4][4]){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			dst[i][j] = src[i][j];
}
inline void matrixMul(ll a[4][4],ll b[4][4]){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			ll tmp = 0;
			for(int k=0;k<4;k++)
				tmp += (a[i][k] * b[k][j])% MOD;
			tem2[i][j] = tmp%MOD;
		}
}
inline void matrixMul(ll a[4][4],ll b[4][4],ll c[4][4]){
	matrixMul(a,b); copyTo(tem2,c);
}
void fastPow(int n){
	copyTo(I,ans);
	copyTo(matrix,tem1);
	while(n){
		if(n&1)
			matrixMul(ans,tem1,ans);
		matrixMul(tem1,tem1,tem1);
		n >>= 1;
	}
}
ll calculate(int n,int c){
	fastPow(n);
	return ans[0][mp[c]];
}
int main(){
	cin >> n >> str;
	if(str[2]!='\0')
		cout << 0;
	else if(str[1]=='\0')
		cout << calculate(n,*str-'0');
	else
		cout << calculate(n,(*str-'0')*10+(str[1]-'0'));
	return 0;
}