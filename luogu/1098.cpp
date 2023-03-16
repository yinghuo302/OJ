/*
 * @Author: zanilia
 * @Date: 2022-09-21 17:23:04
 * @LastEditTime: 2022-09-21 18:14:52
 * @Descripttion: 
 */
#include <stdio.h>
#include <string.h>
#define f_2(i,begin,end) for(int i=begin;i!=end;++i)
#define f_2_dec(i,begin,end) for(int i=begin;i!=end;--i)
char src[105];
char ans[20005];
int p1,p2,p3;
inline bool isNum(char ch){
	return ch >= '0' && ch <= '9';
}
inline bool isLetter(char ch){
	return ch >= 'a' && ch <= 'z';
}
int fill = 0;
int pos = 1;
inline char getCh(char ch){
	return (fill == 0)? '*' : ((fill==1)? ch:ch-32);
}
int main(){
	scanf("%d%d%d",&p1,&p2,&p3);
	scanf("%s",src);
	int size = strlen(src);
	if(size<=2){
		printf("%s",src);
		return 0;
	}
	ans[0] = src[0];
	f_2(i,1,size-1){
		if(src[i]=='-'){
			if((isNum(src[i-1])&&isNum(src[i+1])||
			isLetter(src[i-1])&&isLetter(src[i+1]))&&src[i-1]<src[i+1]){
				if(src[i-1]+1==src[i+1])
					continue;
				if(p1==3)
					fill = 0;
				else if(isLetter(src[i-1])&&p1==2)
					fill = 2;
				else
					fill = 1;
				if(p3==1){
					f_2(j,src[i-1]+1,src[i+1]){
						f_2(k,0,p2){
							ans[pos++] = getCh(j);
						}
					}
				}else{
					f_2_dec(j,src[i+1]-1,src[i-1]){
						f_2(k,0,p2){
							ans[pos++] = getCh(j);
						}
					}
				}
				continue;
			}
		}
		ans[pos++] = src[i];
	}
	ans[pos++] = src[size-1];
	ans[pos] = '\0';
	printf("%s",ans);
	return 0;
}