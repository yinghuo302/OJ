
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int id,cnt;
    bool operator > (const Node b)const{
        if(cnt==b.cnt) return id<b.id; 
        return cnt>b.cnt;
    }
};
int n,m,q,idx,op;
int tot[100010];
int p[200010],h[200010],pre[200010];
set<Node,greater<Node> > heap;

class ODT{
public:
    struct Node{
        int right;
        int vote;
        Node()  = default;
        Node(int right,int vote):right(right),vote(vote){}
    };
    map<int,Node> mp;
    typedef map<int,Node>::iterator iter;
    ODT(){
        mp.emplace(0,Node(int(1e9+7),0));
    }
    iter split(int x){
        auto it = mp.lower_bound(x);
        if(it!=mp.end()&&it->first==x)
            return it;
        --it;
        Node node = it->second;
        it->second.right = x-1;
        return mp.emplace(x,node).first;
    }
}odt;

void init(){//初始化
    tot[0]=n;
    for(int i=0;i<=m;i++){
        p[i]=h[i]=pre[i]=i;
        heap.insert({i,tot[i]});
    }
    idx=m+1;
}

int find(int x){
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
 
int mid(int x){//通过编号找到任一个id
    return h[x];
}
 
int idm(int x){//通过id找到唯一的编号
    return pre[find(x)];
}
 
void rangeChange(int x,int l,int r){//操作1
    auto it_r = odt.split(r+1),it_l = odt.split(l);    
    for(auto it=it_l;it!=it_r;it++){
		int id = idm(it->second.vote);
		heap.erase({id,tot[id]});
		tot[id] -= (it->second.right-it->first+1);
		heap.insert({id,tot[id]});
	}
	odt.mp.erase(it_l,it_r);
	odt.mp.emplace(l,ODT::Node(r,mid(x)));
	heap.erase({x,tot[x]});
    tot[x]+=(r-l+1);
	heap.insert({x,tot[x]});
}
 
void swapVote(int x,int y){//操作3
    heap.erase({x,tot[x]}),heap.erase({y,tot[y]});
    int a=h[x],b=h[y];
    pre[a]=y,pre[b]=x;
    swap(h[x],h[y]);
    swap(tot[x],tot[y]);
    heap.insert({x,tot[x]});
    heap.insert({y,tot[y]});
}
 
void changeF2(int x,int y){//操作2
    heap.erase({x,tot[x]}),heap.erase({y,tot[y]});
    p[h[x]]=h[y];
    p[idx]=idx;
    h[x]=idx;
    pre[idx++]=x;
    tot[y]+=tot[x];
    tot[x]=0;
    heap.insert({x,tot[x]});
    heap.insert({y,tot[y]});
}
 
int main(){
    cin>>n>>m>>q;
    init();
    while(q--){
        cin>>op;
        if(op==1){
            int l,r,x;
            cin>>l>>r>>x;
            rangeChange(x,l,r);
        }
        else if(op==2){
            int x,y;
            cin>>x>>y;
            changeF2(x,y);
        }
        else if(op==3){
            int x,y;
            cin>>x>>y;
            swapVote(x,y);
        }
        else if(op==4){
            int x;
            cin>>x;
            cout<<tot[x]<<endl;
        }
        else{
            if(tot[0]==n) cout<<0<<endl;
            else{
                if((*heap.begin()).id) cout<<(*heap.begin()).id<<endl;
                else cout<<(*(++heap.begin())).id<<endl;
            }
        }
    }
	return 0;
}