/*
 * @Author: zanilia
 * @Date: 2022-11-13 14:54:22
 * @LastEditTime: 2022-11-13 17:28:13
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;++i)
#define f_2_dec(i,begin,end) for(auto i=begin;i!=end;--i)
int arr[100][100];
bool check(int i,int j,int k,int l){
	int sum = 0;
	f_2(a,i,k+1){
		f_2(b,j,l+1){
			sum += arr[a][b];
			if(sum > 2022)
				return false;
		}
	}
	return sum == 2022;
}
int main(){
	f_2(i,0,100){
		arr[i][0] = i+1;
	}
	f_2(i,0,100){
		f_2(j,1,100){
			arr[i][j] = arr[i][j-1]+ 2;
			if(arr[i][j]==337)
				cout << i << ' ' << j;
		}
	}
	int _min = INT32_MAX;
	f_2(i,0,100){
		f_2(j,0,100){
			f_2(k,i,100){
				f_2(l,j,100){
					if(check(i,j,k,l)){
						cout << i << ' ' << j << ' '<< k << ' ' << l << '\n';
						_min = min(_min,(k-i+1)*(l-j+1));
					}
				}
			}
		}
	}
	cout << _min;
	return 0;
}
