/*
 * @Author: zanilia
 * @Date: 2022-06-21 22:54:23
 * @LastEditTime: 2022-06-21 23:12:59
 * @Descripttion: 
 */

#include <stdio.h>
#include <string.h>
#define N 500010
char s[60];
int n, m, ch[N][26], tag[N], tot = 1;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%s",s);
		int len = strlen(s);
		int u = 1;
		for(int i=0;i<len;++i){
			char c = s[i] -'a';
			if(!ch[u][c])
				ch[u][c] = ++tot;
			u = ch[u][c];
		}
		tag[u] = 1;
	}
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		scanf("%s",s);
		int len = strlen(s);
		int u = 1;
		for(int i=0;i<len;++i){
			char c = s[i] -'a';
			u = ch[u][c];
			if(!u)
				break;
		}
		if(tag[u]==0)
			printf("WRONG\n");
		else if(tag[u]==2)
			printf("REPEAT\n");
		else{
			printf("OK\n");
			tag[u] = 2;
		}
	}
	return 0;
}