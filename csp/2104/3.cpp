/*
 * @Author: zanilia
 * @Date: 2022-09-10 13:52:41
 * @LastEditTime: 2022-09-10 16:17:55
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <queue>
#define unalloc 1
#define waitalloc 2
#define occupy 3
#define time_out 4
using namespace std;
#define from_to(i,begin,end) for(int i=begin;i<end;++i)
#define range(i,n) for(int i=0;i<n;++i)
typedef int IPAddress;
typedef string Host;
int N,t_def,t_max,t_min;
Host H;
int n;
int t;
Host sender,receiver;
string type;
IPAddress sender_ip;
int timeout;
int ip_try_alloc;
unordered_map<Host,IPAddress> mp;
struct IpState{
	int state;
	int timeout;
	Host h;
	IpState():state(unalloc),timeout(0){}
};
IpState pool[10001];
inline int checkState(int i){
	if(t>=pool[i].timeout){
		if(pool[i].state==waitalloc){
			pool[i].state = unalloc;
			mp.erase(pool[i].h);
			pool[i].h.clear();
		}else if(pool[i].state==occupy){
			pool[i].state = time_out;
			pool[i].timeout = 0;
		}
	}
	return pool[i].state;
}
IPAddress getIp(){
	int min_unalloc = 0, min_timeout = 0;
	from_to(i,1,N+1){
		if(min_unalloc!=0)
			break;
		int state = checkState(i);
		if(state==unalloc)
			min_unalloc = i;
		else if (state==time_out&&min_timeout==0)
			min_timeout = i;
	}
	return (min_unalloc==0)? min_timeout:min_unalloc;
}
inline int getTimeout(){
	if(timeout==0)
		return t+t_def;
	else if(timeout<=t+t_min)
		return t+t_min;
	else if(timeout>= t+t_max)
		return t + t_max;
	return timeout;
}
void sendMessage(string _type){
	if(_type=="OFR"){
		cout << H << ' ' << sender << ' ' << _type  << ' ' << ip_try_alloc << ' ' << pool[ip_try_alloc].timeout << '\n';
	}else if(_type=="ACK"){
		cout << H << ' ' << sender << ' ' << _type  << ' ' << sender_ip << ' ' << pool[sender_ip].timeout << '\n';
	}else{
		cout << H << ' ' << sender << ' ' << _type << ' ' << sender_ip << ' ' << 0 << '\n';
	}
}
void DISHandler(){
	if(receiver!="*")
		return ;
	if(mp.count(sender)){
		ip_try_alloc = mp[sender];
	}else{
		ip_try_alloc = getIp();
		if(ip_try_alloc==0)
			return ;
	}
	mp[sender] = ip_try_alloc;
	if(pool[ip_try_alloc].state==time_out)
		mp.erase(pool[ip_try_alloc].h);
	pool[ip_try_alloc].h = sender;
	pool[ip_try_alloc].state = waitalloc;
	pool[ip_try_alloc].timeout = getTimeout();
	sendMessage("OFR");
}
void REQHandler(){
	if(receiver=="*")
		return ;
	if(receiver!=H){
		if(mp.count(sender)){
			int ip = mp[sender];
			pool[ip].state = unalloc;
			pool[ip].h.clear();
			pool[ip].timeout = 0;
			mp.erase(sender);
		}
		return ;
	}
	if(mp.count(sender)&&mp[sender]==sender_ip){
		pool[sender_ip].state = occupy;
		pool[sender_ip].timeout = getTimeout();
		sendMessage("ACK");
		return ;
	}
	else
		sendMessage("NAK");
}
inline void messageHandler(){
	if(type=="DIS"){
		DISHandler();
	}else if(type=="REQ"){
		REQHandler();
	}
}


int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin >> N >> t_def >> t_max >> t_min >> H;
	cin >> n;
	range(i,n){
		cin >> t >> sender >> receiver >> type >> sender_ip >> timeout;
		messageHandler();
	}
	return 0;
}