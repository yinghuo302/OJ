// #include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
char strs[100][101];
int m,n;
#define f_2(i,begin,end) for(auto i=begin;i!=end;++i)
#define ROW false
#define COL true
bool check(int a,int b,int c,bool dir){
	int mn = min(b,c),mx = max(b,c);
	if(dir){
		f_2(i,mn+1,mx+1){
			if(strs[a][i]!=strs[a][mn])
				return false;
		}
		return true;
	}else{
		f_2(i,mn+1,mx+1){
			if(strs[i][a]!=strs[mn][a])
				return false;
		}
		return true;
	}
}
int func(int a,int b,int c,int d){
	// (a,b) (c,d)
	// (a,d) (c,b)
	return (check(a,b,d,COL)&&check(d,a,c,ROW))+(check(b,a,c,ROW)&&check(c,d,b,COL));
}
int main(){
	scanf("%d%d",&m,&n);
	f_2(i,0,m){
		scanf("%s",strs[i]);
	}
	int cnt = 0;
	f_2(z,0,200){
		f_2(i,0,m){
			if(z-i<0||z-i>=n)
				continue;
			f_2(j,i+1,m){
				if(z-j<0||z-j>=n||strs[i][z-i]!=strs[j][z-j])
					break;
				cnt += func(i,z-i,j,z-j);
			}
		}
	}
	f_2(z,-100,100){
		f_2(i,0,m){
			if(z+i<0||z+i>=n)
				continue;
			f_2(j,i+1,m){
				if(z+j<0||z+j>=n||strs[i][z+i]!=strs[j][z+j])
					break;
				cnt += func(i,z+i,j,z+j);
			}
		}
	}
	printf("%d",cnt);
	return 0;
}