#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
#define N 14 // 只可能出现1,2,4,6,16,26,41,42,44,46,61,62,64,66共14种情况
#define MOD 998244353
unordered_map<int,vector<int>> _next = {
	{1,{2}}, {2,{4}},{4,{1,6,16}},{6,{4,6,64}},{16,{26}},{26,{46}},
	{41,{62}}, {42,{64}}, {44,{61}}, {46,{66}},{61,{42}},{62,{44}},{64,{41}},{66,{46}}
};  // 记录每一个数下一次会变成哪个数
unordered_map<int,int> idx = {
	{1,0}, {2,1},{4,2},{6,3},{16,4},{26,5},
	{41,6}, {42,7}, {44,8}, {46,9},{61,10},{62,11},{64,12},{66,13}
}; // 记录每一个数在变换矩阵中的下标
int n;string str;
int dp[N][N] = {0};  //原始的dp递推矩阵
int dp_n[N][N] = {0}; // 记录dp的n次幂
int tem[N][N]; // 矩阵计算的中间结果
int origin[N] = {1,0}; //第0秒的初始状态
void init(){
	for(auto &p:idx){
		for(auto& nx:_next[p.first]){
			dp[p.second][idx[nx]]++;
		}
	}
	for(int i=0;i<N;i++) // 初始为单位矩阵
		dp_n[i][i] = 1;
}
inline void matrixMul(int a[N][N],int b[N][N],int c[N][N]){
	static int tmp_arr[N][N];
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++){
			ll tmp = 0;
			for(int k=0;k<N;k++)
				tmp += (1ll* a[i][k] * b[k][j]) % MOD;
			tmp_arr[i][j] = tmp%MOD;
		}
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			c[i][j] = tmp_arr[i][j];
}
void fastPow(int n){
	while(n){
		if(n&1)
			matrixMul(dp_n,dp,dp_n); // dp_n = dp_n * dp
		matrixMul(dp,dp,dp); // dp = dp * dp
		n >>= 1;
	}
}
int main(){
	cin >> n >> str;
	if(str.size()>2)
		return -1;
	init();
	fastPow(n);
	int query = stoi(str);
	if(!idx.count(query)) cout << 0;
	int index = idx[query];
	ll ans = 0;
	for(int i=0;i<N;i++)
		ans += origin[i] * dp_n[i][index];
	cout << ans%MOD;
	return 0;
}