/*
 * @Author: zanilia
 * @Date: 2023-03-08 21:39:29
 * @LastEditTime: 2023-03-14 11:37:50
 * @Descripttion: 
 */
#include <iostream>
#include <cmath>
using namespace std;
struct Info{
	double x,y,x_2,y_2,xy;
	int cnt;
	Info():x(0),y(0),x_2(0),y_2(0),xy(0),cnt(0){}
	Info(double x,double y):x(x),y(y),x_2(x*x),y_2(y*y),xy(x*y),cnt(1){}
	Info operator+(const Info& a) const {
		Info res;
		res.x = x + a.x; res.y = x + a.y;
		res.x_2 = x_2 + a.x_2; res.y_2 = y_2 + a.y_2; 
		res.xy = xy + a.xy; res.cnt = cnt + a.cnt;
		return res;
	}
};
struct Transform{
	double k_xx,k_xy,b_x,k_yx,k_yy,b_y;
	Transform():k_xx(0),k_xy(0), b_x(0),k_yx(0),k_yy(0),b_y(0){}
	Transform(double k_xx,double k_xy,double b_x,double k_yx,double k_yy,double b_y):k_xx(k_xx) ,k_xy(k_xy), b_x( b_x),k_yx(k_yx),k_yy(k_yy),b_y(b_y) {}
	Info operator()(const Info& a)const{
		Info ans;
		ans.x = k_xx * a.x + k_xy * a.y + b_x * a.cnt;
		ans.y = k_yx * a.x + k_yy * a.y + b_y * a.cnt;
		ans.x_2 = k_xx*k_xx*a.x_2 +  k_xy*k_xy*a.y_2 + b_x * b_x * a.cnt + 2*k_xx*k_xy*a.xy + 2*k_xx*b_x*a.x + 2*k_xy*b_x*a.y; 
		ans.y_2 = k_yx*k_yx*a.x_2 +  k_yy*k_yy*a.y_2 + b_y * b_y * a.cnt + 2*k_yx*k_yy*a.xy + 2*k_yx*b_y*a.x + 2*k_yy*b_y*a.y; 
		ans.xy = k_xx*k_yx*a.x_2 + k_xy*k_yy*a.y_2 + (k_xx*k_yy+k_xy*k_yx)*a.xy +  (k_xx*b_y+k_yx*b_x)*a.x + (k_xy*b_y+k_yy*b_x) *a.y + b_x*b_y*a.cnt;
		return ans;
	}
	Transform operator()(const Transform& t) const {
		Transform ans;
		ans.k_xx = k_xx * t.k_xx + k_xy * t.k_yx;
		ans.k_xy = k_xx * t.k_xy + k_xy * t.k_yy;
		ans.b_x = k_xx * t.b_x + k_xy * t.b_y + b_x;
		ans.k_yx = k_yx * t.k_xx + k_yy * t.k_yy;
		ans.k_yy = k_yx * t.k_xy + k_yy * t.k_yy;
		ans.b_y = k_yx * t.b_x + k_yy * t.b_y + b_y;
		return ans;
	}
	bool operator!() const {
		return k_xx==0 && k_xy==0 && b_x==0 && k_yx==0 && k_yy==0 && b_y ==0;
	}
};
double x[500000],y[500000];
Info tree[4*500000];
Transform lazy[4*500000];
int n,q;
void build(int root,int l, int r) {
	if(l==r){
		tree[root] = Info(x[l],y[l]); return ;
	}
	int mid = l + (r-l)/2;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	tree[root] = tree[root*2] + tree[root*2+1];
}
inline void pushDown(int root){
	if(!lazy[root]) return ;
	int ls = root*2, rs = ls+1;
	lazy[ls] = lazy[root](lazy[ls]); tree[ls] = lazy[root](tree[ls]);
	lazy[rs] = lazy[root](lazy[rs]); tree[rs] = lazy[root](tree[rs]);
	lazy[root] = Transform();
}
Info getSum(int root,int start,int end,int l, int r) {
	if(l<=start&&end<=r)
		return tree[root];
	pushDown(root);
	int mid = start + (end-start)/2;
	Info sum;
	if(l<=mid)
		getSum(root,start,mid,l,r);
	if(mid<r)
		sum = sum + getSum(root,mid+1,end,l,r);
	return sum;
}
void update(int root,int start,int end,int l,int r,const Transform& t){
	if(l<=start &&end <= r){
		tree[root] = t(tree[root]);
		lazy[root] = t(lazy[root]);
		return;
	}
	int leftroot = root * 2;
	int rightroot = root * 2 + 1;
	int mid = (start+end)/2;
	if(l<=mid)
		update(leftroot,start,mid,l,r,t);
	if(r>mid)
		update(rightroot,mid+1,end,l,r,t);
	tree[root] = tree[leftroot] + tree[rightroot];
}
Info sumRange(int left, int right) {
	return getSum(1,0,n-1,left,right);
}
void update(int left,int right,const Transform& k){
	update(1,0,n-1,left,right,k);
}
int l,r;
double a,b,lmd,theta,y_0;
char op;
Transform tmp_t;
int main(){
	cin >> n >> q;
	for(int i=0;i<n;i++)
		cin >> x[i] >> y[i];
	build(1,0,n-1);
	for(int i=0;i<q;i++){
		cin >> op >> l >> r;
		switch (op) {
			case '1':{
				cin >> a >> b;
				tmp_t = Transform(0,0,a,0,0,b);
				update(l,r,tmp_t); break;
			}
			case '2':{
				cin >> a >> b >> theta;
				double c = cos(theta), s = sin(theta);
				tmp_t = Transform(c,s,-a*c-s*b+a,-s,c,a*s-b*c+b);
				update(l,r,tmp_t); break;
			}
			case '3':{
				cin >> a >> b >> lmd;
				tmp_t = Transform(lmd,0,a-lmd*a,0,lmd,b-lmd*b);
				update(l,r,tmp_t); break;
			}
			case '4':{
				cin >> theta >> y_0;
				double k = tan(theta),k2 = k*k,k2_1 = k2 + 1; 
				tmp_t = Transform( 2/k2_1-1, 2*k/k2_1,-2*y_0*k/k2_1,2*k/k2_1,2*k2/k2_1-1,2*y_0/k2_1);
				update(l,r,tmp_t); break;
			}
			case '5':{
				cin >> theta >> y_0;
				double k = tan(theta),k2 = k*k,k2_1 = k2 + 1; 
				tmp_t = Transform(1/k2_1,k/k2_1,-y_0*k/k2_1,k/k2_1,k2/k2_1,y_0/k2_1);
				update(l,r,tmp_t); break;
			}
			case '6':{
				Info i1 = sumRange(l,r);
				cout << i1.x / i1.cnt << ' ' <<  i1.y / i1.cnt << '\n';
				break;
			}
			case '7':{
				cin >> a >> b;
				Info i1 = sumRange(l,r);
				cout << i1.x_2 + i1.y_2 - 2*a*i1.x - 2*b*i1.y + i1.cnt * a*a + i1.cnt * b*b << '\n';
			}
		}
	}
	return 0;
}