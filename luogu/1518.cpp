/*
 * @Author: zanilia
 * @Date: 2022-09-22 19:34:43
 * @LastEditTime: 2022-09-22 21:58:52
 * @Descripttion: 
 */
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
const int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
const int update_dir[4] = {3,0,1,2};
int f_x,f_y,f_dir = 2,c_x,c_y,c_dir = 2;
char forest[12][12];
unordered_set<int> state;
int f_state,c_state;
int _time = 0;
int main(){
	f_2(i,0,12){
		forest[i][0] = '*';
		forest[i][11] = '*';
		forest[0][i] = '*';
		forest[11][i] = '*';
	} 
	f_2(i,1,11){
		f_2(j,1,11){
			cin >> forest[i][j];
			switch(forest[i][j]){
				case 'F':f_x = i;f_y = j;break;
				case 'C':c_x = i;c_y = j;break;
			}
		}
	}
	while(1){
		++_time;
		f_x += dirs[f_dir][0];
		f_y += dirs[f_dir][1];
		c_x += dirs[c_dir][0];
		c_y += dirs[c_dir][1];
		if(f_x<0||f_x>=10||f_y<0||f_y>=10||forest[f_x][f_y]=='*'){
			f_x -= dirs[f_dir][0];
			f_y -= dirs[f_dir][1];
			f_dir = update_dir[f_dir];
		}
		if(c_x<0||c_x>=10||c_y<0||c_y>=10||forest[c_x][c_y]=='*'){
			c_x -= dirs[c_dir][0];
			c_y -= dirs[c_dir][1];
			c_dir = update_dir[c_dir];
		}
		if(f_x==c_x&&f_y==c_y){
			cout << time;
			return 0;
		}
		state.emplace((c_x<<8 )+(c_y << 4) +c_dir);
		if(state.count((f_x<<8)+(f_y<<4)+f_dir)){
			cout << '0';
			return 0;
		}
	}
	return 0;
}