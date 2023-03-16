#include <iostream>
using namespace std;
#define f_2(i,begin,end)  for(int i=begin;i<end;++i)
#define f_2_dec(i,begin,end) for(int i=begin;i>end;--i)
long long c[21] = {1};
long long b[21];
long long n ,m;
int main(){
    ios::sync_with_stdio(false);
    cout.tie(0);
    cin >> n >> m;
    f_2(i,1,n+1){
        cin >> c[i];
    }
    f_2(i,1,n+1){
        c[i] *= c[i-1];        
    }
    f_2_dec(i,n,0){
        b[i-1] = m / c[i-1];
        m = m %c[i-1];
    }
    f_2(i,0,n){
        cout << b[i] << ' ';
    }
    return 0;
}