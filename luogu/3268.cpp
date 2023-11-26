/*
 * @Author: zanilia
 * @Date: 2023-02-27 19:53:31
 * @LastEditTime: 2023-02-27 20:10:05
 * @Descripttion: 
 */
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <vector>
#define MAX_N 200010
#define EPS 1e-5
using namespace std;
int N;
long long x[MAX_N],y[MAX_N],r[MAX_N];
bool depth[MAX_N];
long long now_x ,ans = 0;
struct Circle{
	int id;
	bool up;
	Circle(int id,bool up):id(id),up(up){}
	inline double getY() const {
		double dy = sqrt(r[id]*r[id]-(now_x - x[id] )*(now_x - x[id])) + EPS;
		return up? y[id]+dy: y[id] - dy;
	}
	bool operator < (const Circle& other) const {
		if (id==other.id)
			return !up;
		return getY() < other.getY();
	}
};
struct OP{
	long long pos;
	int id;
	bool insert;
	OP(long long pos,int id,bool insert):pos(pos),id(id),insert(insert){}
	bool operator < (const OP& other) const {
		return pos < other.pos;
	}
};
vector<OP> ops;
set<Circle> st;
int main(){
	cin >> N;
	ops.reserve(N*2);
	for(int i=0;i<N;i++){
		cin >> x[i] >> y[i] >> r[i];
		ops.push_back(OP(x[i]-r[i],i,1));
		ops.push_back(OP(x[i]+r[i],i,0));
	}
	sort(ops.begin(),ops.end());
	for(auto &op:ops){
		now_x = op.pos;
		if(op.insert){
			auto it = st.insert(Circle(op.id,1)).first;
			if(it==st.begin())
				depth[op.id] = 1;
			else{
				it--;
				if(it->up)
					depth[op.id] = depth[it->id];
				else
					depth[op.id] = depth[it->id]^1;
			}
			st.insert(Circle(op.id,0));
			if(depth[op.id]) 
				ans += r[op.id]*r[op.id];
			else
				ans -= r[op.id]*r[op.id];
		}else{
			st.erase(Circle(op.id,1));
			st.erase(Circle(op.id,0));
		}
	}
	cout << ans;
	return 0;
}