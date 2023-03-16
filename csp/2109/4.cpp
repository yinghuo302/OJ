/*
 * @Author: zanilia
 * @Date: 2022-09-17 19:47:14
 * @LastEditTime: 2022-09-18 10:13:31
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
#define f_2(i,begin,end) for(int i=begin;i<end;++i)
int n,k;
double p[20];
double f[81][1 << 16] = {0};
double calculate(int state,int coin,int cnt,int depth){
	if(f[coin][state]!=0) 
		return f[coin][state];
	if(cnt*k<=coin){
		return depth;
	}
	double s = 0;
	f_2(i,0,n){
		if(state&(i<<i)!=0)
			s += p[i]*calculate(state,coin+1,cnt,depth+1);
		else
			s += p[i]*calculate(state|(1<<i),coin,cnt-1,depth+1);
	}
	return f[coin][state] = s;
}
int main(){
	cin >> n >> k;
    f_2(i,0,n){
        cin >> p[i];
	}
	cout << calculate(0,0,n,0);
	return 0;
}