/*
 * @Author: zanilia
 * @Date: 2022-09-21 21:57:30
 * @LastEditTime: 2022-09-21 23:44:09
 * @Descripttion: 
 */
#include <iostream>
#include <algorithm>
#define f_2(i,begin,end) for(auto i=begin;i!=end;++i)
using namespace std;
int n;
struct Player{
	string name;
	int position;
	int level;
	int tribute;
	int i;
};
const string _pos[7] = {"BangZhu","FuBangZhu","HuFa","ZhangLao","TangZhu","JingYing","BangZhong"};
inline int getPosState(string pos){
	f_2(i,0,7){
		if(pos==_pos[i])
			return i;
	}
}
string tem;
Player players[200];
int p[200];
int main(){
	cin >> n;
	f_2(i,0,n){
		cin >> players[i].name >> tem >> players[i].tribute >> players[i].level;
		players[i].position = getPosState(tem);
		players[i].i = i;
	}
	f_2(i,0,n)
		p[i] = i;
	sort(p+3,p+n,[](const int& i,const int& j){
		if(players[i].tribute==players[j].tribute) return players[i].i < players[j].i;
		return players[i].tribute > players[j].tribute;
	});
	f_2(i,3,n){
		int j = p[i];
		if (i==3||i==4) players[j].position = 2;
		else if (i>=5&&i<=8) players[j].position = 3;
		else if (i>=9&&i<=15) players[j].position = 4;
		else if (i>=16&&i<=40) players[j].position = 5;
		else players[j].position = 6;
	}
	sort(p,p+n,[](const int& i,const int& j){
		if(players[i].position==players[j].position){
			if(players[i].level == players[j].level)
				return players[i].i < players[j].i;
			return players[i].level>players[j].level;
		}
		return players[i].position<players[j].position;
	});
	f_2(i,0,n){
		int j = p[i];
		cout << players[j].name << ' ' << _pos[players[j].position] << ' ' << players[j].level << '\n';
	}
	return 0;
}