/*
 * @Author: zanilia
 * @Date: 2022-09-20 11:13:04
 * @LastEditTime: 2022-09-21 23:59:05
 * @Descripttion: 
 */
#include <iostream>
#include <set>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;++i)
int m,n;
int num[4000];
int cnt[21] = {0};
int t[21][21];
int mechain[21][21];
int last[21] = {0};
bool vis[21][10005] = {false};
int tem;
int max_time = 0;
int main(){
	cin >> m >> n;
	f_2(i,0,m*n){
		cin >> num[i];
	}
	f_2(i,1,n+1){
		f_2(j,1,m+1){
			cin >> mechain[i][j];
		}
	}
	f_2(i,1,n+1){
		f_2(j,1,m+1){
			cin >> t[i][j];
		}
	}
	f_2(i,0,m*n){
		int work = num[i],step = ++cnt[work],m = mechain[work][step];
		int all = 0;
		f_2(j,last[work]+1,10005){
			if(vis[m][j]) all = 0;
			else all++;
			if(all==t[work][step]){
				f_2(k,j-t[work][step]+1,j+1){
					vis[m][k] = true;
				}
				last[work] = j;
				max_time = max(max_time,j);
				++num[i];++cnt[work];
				break;
			}
		}
		
	}
	cout << max_time;
	return 0;
}