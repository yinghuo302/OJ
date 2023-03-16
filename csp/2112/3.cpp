/*
 * @Author: zanilia
 * @Date: 2022-09-06 16:22:17
 * @LastEditTime: 2022-09-07 20:21:09
 * @Descripttion: 
 */
#include <iostream>
#define MAX_CH_NUM 929
#define UPPER 1
#define LOWER 2
#define NUM 4
#define MOD 929
using namespace std;
int g[1000];   // 多项式g(x)系数，下标为0是最高位，k是最低位
int r[1000];
int d[1000];  // 多项式d(x)系数，下标为0是最高位，ptr是最低位
char str[1000];
char tem = -1;
int w,s,k;
int ptr = 1;
inline int getType(char c){
	if('A'<=c&&c<='Z')
		return UPPER;
	else if('a'<=c&&c<='z')
		return LOWER;
	else
		return NUM;
}
inline void addNum(char ch){
	if(tem==-1){
		tem = ch;
	}else{
		d[ptr++] = tem*30+ch;
		tem = -1;
	}
}
inline void changeType(int pre,int cur){
	switch(cur){
		case NUM:addNum(28);break;
		case LOWER:addNum(27);break;
		case UPPER:if(pre==LOWER) addNum(28); addNum(28);break;
	}
}
inline void addCh(int type,char ch){
	switch (type){
		case NUM:addNum(ch-'0');break;
		case UPPER:addNum(ch-'A');break;
		case LOWER:addNum(ch-'a');break;
	}
}
// d(x) * x^k / g(x) 
void divide(){
	for(int i=0;i<ptr;++i){
		for(int j=1;j<=k;++j){
			d[i+j] = (d[i+j] - d[i]*g[j])% MOD;
		}
	}
	for(int i=ptr;i<ptr+k;++i)
		cout << (-d[i]+MOD)%MOD << '\n';
}
void calculateG(){
	g[0] = 1;
	int a = -3;
	for(int i=1;i<=k;++i){
		for(int j=i;j>0;--j){
			g[j] = (g[j] + g[j-1]*a)%MOD;
		}
		a = (a*3)%MOD;
	}
}
void calculateCode(){
	int pre = UPPER;
	for(int i=0;i<MAX_CH_NUM;++i){
		if(str[i]=='\0')
			break;
		int cur = getType(str[i]);
		if(pre!=cur){
			changeType(pre,cur);
			pre = cur;
		}
		addCh(cur,str[i]);
	}
	if(tem!=-1)
		addNum(29);
}
void fill(){
	int num = w-(ptr+k)%w;
	for (int i=0;i<num;++i){
		d[ptr++] = 900;
	}
	d[0] = ptr;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> w >> s;
	k = s==-1? 0: 1 << (s+1);
	cin >> str;
	calculateCode();
	fill();
	for(int i=0;i<ptr;++i){
		cout << d[i] << '\n';
	}
	calculateG();
	divide();
	return 0;
}