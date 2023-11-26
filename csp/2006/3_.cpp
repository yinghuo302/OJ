/*
 * @Author: zanilia
 * @Date: 2023-03-08 18:35:34
 * @LastEditTime: 2023-03-08 18:42:53
 * @Descripttion: 
 */
#include <iostream>
#include <vector>
using namespace std;
int w;
string str;
vector<string> para;
vector<string> pro;
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
void build_para(){

}
void build_pro(){

}
int main(){
	cin >> w;
	while(getline(cin,str)){
		int begin = getBegin(str),end = getEnd(str),size = str.size();
		if(begin==end){
			build_para();
			build_pro();
		}
		if(size>=2&&str.substr(0,2)=="* ")
			pro.emplace_back(str);
		else if(size>=2&&str.substr(0,2)=="  "&&!pro.empty())
			pro.emplace_back(str);
		else
			para.emplace_back(str);
	}
	build_para();build_pro();
	cout << cnt;
	return 0;
}