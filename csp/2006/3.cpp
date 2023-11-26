/*
 * @Author: zanilia
 * @Date: 2023-03-07 21:44:44
 * @LastEditTime: 2023-03-08 10:17:52
 * @Descripttion: 
 */
#include <iostream>
#define EMPTY 0
#define COMMON 1
#define PARAGRAPH 2
#define NEW_PROJECT 3
#define CON_PROJECT 4
#define EMP_PROJECT 5
using namespace std;
int w;
string str,pre;
int cnt = 0, ans = 0;
int flag = 0;
int begin,end,size,new_flag;
inline int getEnd(const string& s){
	int i = s.size()-1;
	for(;i>=0;i--)
		if(s[i]!=' ')
			break;
	return i+1;
}
inline int getBegin(const string& s){
	int i=0,size = s.size();
	for(int i=0;i<size;i++)
		if(s[i]!=' ')
			break;
	return i;
}
void format(){
	if(flag==EMPTY&&new_flag==EMPTY)
		return ;
	// if()
}
int main(){
	cin.sync_with_stdio(false);
	while(getline(cin,str)){
		int begin = getBegin(str),end = getEnd(str),size = str.size();
		int new_flag = 0;
		if(begin==end)
			flag = 0;
		else if(size>2&&str.substr(0,2)=="* ")
			new_flag = NEW_PROJECT;
		else if(size==2&&str.substr(0,2)=="* ")
			new_flag = EMP_PROJECT;
		else if(size>=2&&str.substr(0,2)==" ")
			new_flag = CON_PROJECT;
		else
			new_flag = COMMON;
		
	}
}