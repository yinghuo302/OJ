/*
 * @Author: zanilia
 * @Date: 2023-03-01 19:27:06
 * @LastEditTime: 2023-03-01 19:55:45
 * @Descripttion: 
 */
#include <iostream>
using namespace std;
int n,m;
int theta0,theta1,theta2;
char type;
struct Node{
	int x,y,type;
}nodes [1000];
bool check(){
	int flag = 0;
	for(int i=0;i<n;i++){
		int tmp = (theta0 + theta1 * nodes[i].x + theta2 * nodes[i].y)*nodes[i].type;
		if(flag==0) flag = tmp;
		else if((flag^tmp)<0) return false;
	}
	return true;
}
int main(){
	cin >> n >> m;
	for(int i=0;i<n;i++){
		cin >> nodes[i].x >> nodes[i].y >> type;
		nodes[i].type = (type=='A'? 1:-1);
	}
	for(int i=0;i<m;i++){
		cin >> theta0 >> theta1 >> theta2;
		cout << (check()? "Yes\n":"No\n");
	}
	return 0;
}