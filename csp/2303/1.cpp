#include <iostream>
using namespace std;
#define f_2(i,begin,end) for(auto i=begin;i!=end;i++)
struct Area{
    int x1,y1,x2,y2;
    Area() = default;
};
Area areas[101];
int n,a,b;
long long ans = 0;
long long calculate(Area& area){
    if(area.x2<=0||area.y2<=0)
        return 0;
    if(area.x1>=a||area.y1>=b)
        return 0;
    int lx = max(0,area.x1),ly = max(0,area.y1),rx =min(a,area.x2),ry = min(b,area.y2);
    return 1ll * abs(rx-lx) * abs(ry-ly);
}
int main(){
    cin >> n >> a >> b;
    f_2(i,0,n){
        cin >> areas[i].x1 >> areas[i].y1 >> areas[i].x2 >> areas[i].y2;
        ans += calculate(areas[i]);
    }
    cout << ans;
    return 0;
}