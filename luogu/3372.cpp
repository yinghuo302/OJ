/*
 * @Author: zanilia
 * @Date: 2023-03-15 18:24:17
 * @LastEditTime: 2023-03-15 21:32:38
 * @Descripttion: 
 */
#include <iostream>
#define MAX_N 100001
int n,m,op,x,y,k;
long long tree[4*MAX_N] = {0};
long long lazy[4*MAX_N] = {0};
long long nums[MAX_N];
void build(int root,int left,int right){
	if(left==right) { tree[root] = nums[left]; return ;}
	int ls = root*2,rs = ls+1,mid = left+ (right-left)/2;
	build(ls,left,mid);
	build(rs,mid+1,right);
	tree[root] = tree[ls] + tree[rs];
}
void update(int root,int start,int end,int left,int right,long long val){
	if(left<=start&&end<=right) { 
		tree[root] += val * (end-start+1); lazy[root] += val; return ; 
	}
	int ls = root*2,rs = ls+1,mid = start + (end-start)/2;
	if(start!=end){
		lazy[ls] += lazy[root]; tree[ls] += (mid-start+1) * lazy[root];
		lazy[rs] += lazy[root]; tree[rs] += (end-mid) * lazy[root]; lazy[root] = 0;
	}
	if(left<=mid)
		update(ls,start,mid,left,right,val);
	if(mid<right)
		update(rs,mid+1,end,left,right,val);
	tree[root] = tree[ls] + tree[rs];
}
long long getSum(int root,int start,int end,int left,int right){
	int ls = root*2,rs = ls+1,mid = start + (end-start)/2;
	if(start!=end){
		lazy[ls] += lazy[root]; tree[ls] += (mid-start+1) * lazy[root];
		lazy[rs] += lazy[root]; tree[rs] += (end-mid) * lazy[root]; lazy[root] = 0;
	}
	if(left<=start&&end<=right)
		return tree[root];
	long long ans =0;
	if(left<=mid)
		ans += getSum(ls,start,mid,left,right);
	if(mid<right)
		ans += getSum(rs,mid+1,end,left,right);
	return ans;
}
int main(){
	std::cin >> n >> m;
	for(int i=1;i<=n;i++)
		std::cin >> nums[i];
	build(1,1,n);
	for(int i=0;i<m;i++){
		std::cin >> op;
		if(op==1) {
			std::cin >> x >> y >> k; 
			update(1,1,n,x,y,k);
		}else{
			std::cin >> x >> y; 
			std::cout << getSum(1,1,n,x,y) << '\n';
		}
	}
	return 0;
}