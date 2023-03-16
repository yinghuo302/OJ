/*
 * @Author: zanilia
 * @Date: 2022-10-27 20:52:53
 * @LastEditTime: 2023-03-01 23:41:04
 * @Descripttion: 
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define M 30
#define N 300001
int dp[2][N] = {0};
int price[M];
int book_n,target;
int main(){
    cin >> book_n >> target;
    int sum_price = 0;
    for(int i=1;i<=book_n;i++){
        cin >> price[i];
        sum_price += price[i];
    }
    int remain = sum_price - target;
    for(int i=1;i<=book_n;i++){
        int curr = i&1,prev = curr^1;
        for(int j=0;j<=remain;j++){
            dp[curr][j] = dp[prev][j];
            if (j-price[i] >= 0) 
                dp[curr][j] = max(dp[curr][j],dp[prev][j-price[i]]+price[i]);
        }
    }
    cout << sum_price - dp[book_n&1][remain];
    return 0;
}