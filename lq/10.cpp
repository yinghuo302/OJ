/*
 * @Author: zanilia
 * @Date: 2022-11-13 15:27:33
 * @LastEditTime: 2022-11-13 16:07:10
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_set>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;++i)
string str;
int _size;
bool _less(int c,int d){
	int a = c, b = d;
	unordered_set<int> st1,st2;
	while(1){
		if(str[a]!=str[b])
			return str[a] < str[b];
		bool flag1 = st1.count(a), flag2 = st2.count(b);
		st1.emplace(a);st2.emplace(b);
		if(flag1&&flag2) break;
		a = (a + str[a] - 'A' + 1);
		b = (b + str[b] - 'A' + 1);
	}
	return c < d;
}
int main(){
	cin >> str;
	_size = str.size();
	int min_pos = 0;
	f_2(i,1,_size){
		if(_less(i,min_pos))
			min_pos = i;
	}
	cout << min_pos;
	return 0;
}