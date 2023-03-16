/*
 * @Author: zanilia
 * @Date: 2022-09-06 17:25:32
 * @LastEditTime: 2022-09-06 23:53:13
 * @Descripttion: 
 */
#include <iostream>
#include <map>
#define INF 1e9+7
using namespace std;
int n,m,k;
int op,id,l,r,x,p;
char state[2][6] ={"FAIL\n","OK\n"}; 
struct Node{
	int right;
	int id;
	int deleted;
	int val;
	Node() = default;
	Node(int right,int id,int val):right(right),id(id),deleted(0),val(val){}
	bool operator==(const Node& other)const {
		return other.id==id&&other.val==val&&other.deleted==deleted;
	}
	bool operator!=(const Node& other)const{
		return other.id!=id||other.val!=val||other.deleted!=deleted;
	}
};
map<int,Node> disk;
typedef map<int,Node>::iterator iter;
iter split(int x){
	auto it = disk.lower_bound(x);
	if(it!=disk.end()&&it->first==x) 
		return it;
	it--;
	int l = it->first,right = it->second.right;
	auto node = it->second;
	disk.erase(it);
	node.right = x-1;
	disk.emplace(l,node);
	node.right = right;
	return disk.emplace(x,node).first;
}
int writeDisk(int id,int l,int r,int val){
	auto itr = split(r+1),itl = split(l);
	int right = l-1;
	auto it = itl;
	while(itl!=itr){
		if(itl->second.id==id||itl->second.deleted==1||itl->second.id==0){
			right = itl->second.right;
			++itl;
		}else{
			break;
		}
	}
	if(itl==itr)
		right = r;
	disk.erase(it,itl);
	if(right!=l-1)
		disk.emplace(l,Node(right,id,val));
	return right==l-1 ? -1 :right;
}
char* deleteFromDisk(int id,int l,int r){
	auto itr = split(r+1),itl = split(l);
	auto it = itl;
	while(it!=itr){
		if(it->second.id!=id||it->second.deleted==1)
			return state[0];
		it++;
	}
	while(itl!=itr){
		itl->second.deleted = 1;
		++itl;
	}
	return state[1];
}
char* recoveryFromDisk(int id,int l,int r){
	auto itr = split(r+1),itl = split(l);
	auto it = itl;
	while(it!=itr){
		if(it->second.id!=id||it->second.deleted==0)
			return state[0];
		it++;
	}
	while(itl!=itr){
		itl->second.deleted = 0;
		++itl;
	}
	return state[1];
}
int query(int& id,int pos){
	auto it = disk.upper_bound(pos);
	if(it==disk.end()||it->first!=pos)
		--it;
	if(it->second.id!=0&&it->second.deleted==0){
		id = it->second.id;
		return it->second.val;
	}else{
		id = 0;
		return 0;
	}
}
int main(){
	disk.emplace(1,Node(INF,0,0));
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for(int i=0;i<k;++i){
		cin >> op;
		switch (op) {
			case 0:cin >> id >> l >> r >> x; cout << writeDisk(id,l,r,x) << '\n';break;
			case 1:cin >> id >> l >> r;cout << deleteFromDisk(id,l,r);break;
			case 2:cin >> id >> l >> r;cout << recoveryFromDisk(id,l,r); break;
			case 3:cin >> p;x = query(id,p);cout << id << ' ' << x << '\n';break;
		}
	}
	return 0;
}