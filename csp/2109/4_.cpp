/*
 * @Author: zanilia
 * @Date: 2022-09-18 10:07:01
 * @LastEditTime: 2022-09-18 10:23:22
 * @Descripttion: 
 */
#include<iostream>
using namespace std;
int n, k;
double p[20];
double f[81][1 << 16];
double dp(int depth, int coin, int state, int cnt){
    if(f[coin][state]) 
        return f[coin][state];
    if(cnt * k <= coin) 
        return depth;
    double s = 0;
    for(int i = 0; i < n; i ++ ){
        if(state&(1<<i))
            s += p[i] * dp(depth + 1, coin + 1, state, cnt);
        else
            s += p[i] * dp(depth + 1, coin, state | (1 << i), cnt - 1);
    }
    return f[coin][state] = s;
}

int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i ++ )
        cin >> p[i];
    cout << dp(0, 0, 0, n);
    return 0;
}