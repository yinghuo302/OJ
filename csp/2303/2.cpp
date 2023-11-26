#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100001
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
struct Info{
    int t,c;
    Info() = default;
    Info(int t,int c):t(t),c(c){}
    bool operator< (const Info& other) const {
        if(t==other.t) return c < other.c;
        return t < other.t;
    }
};
Info info[MAX_N];
typedef long long ll;
long long max_m = 0;
long long sum_c = 0;
long long sc = 0;
int main(){
    int n,m,k;
    cin >> n >> m >> k;
    f_2(i,0,n){
        cin >> info[i].t >> info[i].c;
    }
    sort(info,info+n);
    f_2(i,0,n){
        max_m += (info[i].t - info[0].t) * info[i].c;
        sum_c += info[i].c;
    }
    int i=n-1,cur_max = info[n-1].t,delta;
    if(m>=max_m){
        m -= max_m;
        cur_max = info[0].t;
        delta = info[0].t  - k;
        cur_max -= min((ll)delta,m/sum_c);
        cout << cur_max;
        return 0;
    }
    while (m>0){
        for(;i>0;i--){
            sc += info[i].c;
            if(info[i].t!=info[i-1].t)
                break;
        }
        delta = info[i].t - info[i-1].t;
        if(delta*sc<m){
            m -= delta* sc;
            cur_max = info[i-1].t;
            i--;
        }else{
            cur_max -= m / sc;
            break;
        }
    }
    cout << cur_max;
    return 0;
}