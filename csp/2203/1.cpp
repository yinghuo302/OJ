/*
 * @Author: zanilia
 * @Date: 2022-09-03 15:22:30
 * @LastEditTime: 2022-09-03 15:53:07
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int n,k,x,y;
bool initialized[100001] = {1,0};
int main(){
	int ans = 0;
	std::cin >> n >> k;
	for(int i=0;i<k;++i){
		std::cin >> x >> y;
		if(!initialized[y])
			++ans;
		initialized[x] = true;
	}
	std::cout << ans;
	return 0;
}