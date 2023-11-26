#include <bits/stdc++.h>
using namespace std;
int n,d;
int Q[10000][20];
int K[10000][20];
int V[10000][20];
long long W;
long long tem[10000];
long long res[20];
void calculate(int i){
	for(int j=0;j<n;j++){
		long long tmp = 0;
		for(int k=0;k<d;k++)
			tmp += Q[i][k] * K[j][k];
		tem[j] = tmp * W;
	}
	for(int j=0;j<d;j++){
		long long tmp = 0;
		for(int k=0;k<n;k++)
			tmp += tem[k]* V[k][j];
		res[j] = tmp;
	}
}
int main(){
	cin >> n >> d;
	for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			cin >> Q[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			cin >> K[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			cin >> V[i][j];
		}
	}
	for(int i=0;i<n;i++){
		cin >> W;
		calculate(i);
		for(int j=0;j<d;j++)
			cout << res[j] << ' ';
		cout << '\n';
	}
	return 0;
}