/*
 * @Author: zanilia
 * @Date: 2022-10-26 17:16:27
 * @LastEditTime: 2022-10-26 17:18:25
 * @Descripttion: 
 */
#include <iostream>
#include <bitset>
using namespace std;
bitset<20> bi;
int main() {
	int n = 0; scanf("%d", &n);
	int m = (1<<n);
	for (int i = 0; i<m; i++) {
		bi = i;
		for (int j = n - 1; j >= 0; j--) 
			cout << (bi[j]^bi[j + 1]? 'X':'O');
		cout << '\n';
	}
	cout << string(n,'O');
	return 0;
}
