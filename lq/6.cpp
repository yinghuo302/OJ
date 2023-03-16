/*
 * @Author: zanilia
 * @Date: 2022-11-13 15:17:04
 * @LastEditTime: 2022-11-13 15:22:26
 * @Descripttion: 
 */
#include <stdio.h>
#include <string.h>
#define f_2(i,begin,end) for(int i=begin;i!=end;++i)
char strs[100][101];
int n;
int cnt = 0;
int main(){
	scanf("%d",&n);
	f_2(i,0,n){
		scanf("%s",strs[i]);
	}
	int m = strlen(strs[0]);
	f_2(i,0,n){
		f_2(j,0,m){
			
		}
	}
}