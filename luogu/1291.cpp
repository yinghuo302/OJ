/*
 * @Author: zanilia
 * @Date: 2022-10-24 22:14:44
 * @LastEditTime: 2022-11-13 16:21:12
 * @Descripttion: 
 */
#include <iostream>
typedef long long ll;
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
ll gcd(ll a,ll b){
	while(a!=0){
		ll tem = a;
		a = b % a;
		b = tem;
	}
	return b;
}
long long ws(long long x){	
	long long ans=0;
	while(x!=0){	
		ans++;
		x/=10;
	}
	return ans;
}
ll n;
int main(){
	cin >> n;
	ll numerator = 0,denominator = 1;
	f_2(i,1ll,n+1){
		numerator = numerator * i + denominator;
		denominator *= i;
		ll f = gcd(numerator,denominator);
		numerator /= f;
		denominator /= f;
	}
	// numerator *= n;
	ll f = gcd(numerator,denominator);
	numerator /= f;
	denominator /= f;
	ll quotient = numerator / denominator; 
	ll remainder = numerator % denominator;
	cout << quotient << '\n';
	if(remainder==0){
		cout << quotient;
		return 0;
	}
	ll w = ws(quotient);
	cout << string(w,' ') << remainder << '\n';
	cout << quotient << string(ws(denominator),'-') << '\n';
	cout << string(w,' ') << denominator;
	return 0;
}