#include <iostream>
#define MAX_N 200000
int n,m;
int a[MAX_N] = {0};
bool check(int l,int r){
    for(int i=0;i<l;i++){
        if(a[i]!=0)
            return false;
    }
    for(int i=l;i<=r;i++){
        if(a[i]==0)
            return false;
    }
    for(int i=r+1;i<n;i++){
        if(a[i]!=0)
            return false;
    }
    return true;
}
int main(){
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> l >> r;
        for(int i=l;i<=r;i++)
            a[i]++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(chgec)
        }
    }
}