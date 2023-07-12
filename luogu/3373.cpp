/*
 * @Author: zanilia
 * @Date: 2023-03-15 18:24:17
 * @LastEditTime: 2023-03-16 15:22:19
 * @Descripttion: 
 */
#include <iostream>
#define MAX_N 100001
int n,m,op,x,y,k,p;
struct Info{
	int val,cnt;
	Info():val(0),cnt(0){}
	Info(int val,int cnt):val(val),cnt(cnt){}
	Info operator+(const Info& other)const {
		return Info((val+other.val)%p,cnt+other.cnt);
	}
};
struct Transform{
	int k,b;
	Transform():k(1),b(0){}
	Transform(int k,int b):k(k),b(b){}
	Info operator()(const Info& a){
		return Info((1ll*k*a.val+b*a.cnt)%p,a.cnt);
	}
	Transform operator()(const Transform& t){
		return Transform((1ll*k*t.k)%p,(1ll*k*t.b+b)%p);
	}
};
Info tree[4*MAX_N];
Transform lazy[4*MAX_N];
long long nums[MAX_N];
void build(int root,int left,int right){
	if(left==right) { tree[root] = Info(nums[left],1); return ;}
	int ls = root*2,rs = ls+1,mid = left+ (right-left)/2;
	build(ls,left,mid);
	build(rs,mid+1,right);
	tree[root] = tree[ls] + tree[rs];
}
inline void pushDown(int root){
	int ls = root*2, rs = ls+1;
	lazy[ls] = lazy[root](lazy[ls]); tree[ls] = lazy[root](tree[ls]);
	lazy[rs] = lazy[root](lazy[rs]); tree[rs] = lazy[root](tree[rs]);
	lazy[root] = Transform();
}
void update(int root,int start,int end,int left,int right,Transform& t){
	if(left<=start&&end<=right) { 
		tree[root] = t(tree[root]); lazy[root] = t(lazy[root]); return ; 
	}
	pushDown(root);
	int ls = root*2,rs = ls+1,mid = start + (end-start)/2;
	if(left<=mid)
		update(ls,start,mid,left,right,t);
	if(mid<right)
		update(rs,mid+1,end,left,right,t);
	tree[root] = tree[ls] + tree[rs];
}
Info getSum(int root,int start,int end,int left,int right){
	if(left<=start&&end<=right)
		return tree[root];
	int ls = root*2,rs = ls+1,mid = start + (end-start)/2;
	pushDown(root);
	Info ans;
	if(left<=mid)
		ans = ans + getSum(ls,start,mid,left,right);
	if(mid<right)
		ans = ans + getSum(rs,mid+1,end,left,right);
	return ans;
}
int main(){
	std::cin >> n >> m >> p;
	for(int i=1;i<=n;i++)
		std::cin >> nums[i];
	build(1,1,n);
	for(int i=0;i<m;i++){
		std::cin >> op;
		if(op==1) {
			std::cin >> x >> y >> k; Transform t(k,0);
			update(1,1,n,x,y,t);
		}else if(op==2){
			std::cin >> x >> y >> k; Transform t(1,k);
			update(1,1,n,x,y,t);
		}else{
			std::cin >> x >> y; 
			std::cout << getSum(1,1,n,x,y).val << '\n';
		}
	}
	return 0;
}