/*
 * @Author: zanilia
 * @Date: 2022-09-17 16:21:08
 * @LastEditTime: 2023-02-27 22:12:01
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int n;
long long min_sum = 0,max_sum = 0;
int _prev = 0,b;
int main(){
	std::cin >> n;
	for(int i=0;i<n;++i){
		std::cin >> b;
		max_sum += b;
		min_sum += (b==_prev)? 0 : b;
		_prev = b;
	}
	cout << max_sum << '\n' << min_sum;
	return 0;
}