/*
 * @Author: zanilia
 * @Date: 2023-03-02 18:43:16
 * @LastEditTime: 2023-03-02 19:13:36
 * @Descripttion: 
 */
#include <cstdio>
using namespace std;
long long u_idx[500001];
long long u_val[500001];
long long n,u_n,v_n;
long long tmp_idx,tmp_val;
long long ans = 0;
long long u_ptr = 0;
int main(){
	scanf("%lld%lld%lld",&n,&u_n,&v_n);
	u_idx[u_n] = n+1;
	for(long long i=0;i<u_n;i++)
		scanf("%lld%lld",&u_idx[i],&u_val[i]);
	for(long long i=0;i<v_n;i++){
		scanf("%lld%lld",&tmp_idx,&tmp_val);
		while(u_idx[u_ptr] < tmp_idx)
			u_ptr++;
		if(u_idx[u_ptr] == tmp_idx)
			ans += u_val[u_ptr] * tmp_val;
	}
	printf("%lld",ans);
	return 0;
}