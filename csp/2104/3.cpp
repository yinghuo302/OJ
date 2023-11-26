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
IPAddress ip_try_alloc;
unordered_map<Host,IPAddress> mp;
struct IpState{
	int state;
	int timeout;
	Host h;
	IpState():state(unalloc),timeout(0){}
};
IpState pool[10001];
inline IPAddress getIpByHost(const Host& h){
	from_to(i,1,N+1)
		if(pool[i].h==h)
			return i;
	return 0;
}
inline IPAddress getIpByState(int state){
	from_to(i,1,N+1)
		if(pool[i].state==state)
			return i;
	return 0;
}
void updateState(){
	from_to(i,1,N+1){
		if(pool[i].timeout!=0&&pool[i].timeout<=t){
			if(pool[i].state==waitalloc){
				pool[i].state = unalloc;
				pool[i].h.clear();
				pool[i].timeout = 0;
			}else if(pool[i].state==occupy){
				pool[i].state = time_out;
				pool[i].timeout = 0;
			}
		}
	}
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
	ip_try_alloc = getIpByHost(sender);
	if(ip_try_alloc==0) ip_try_alloc = getIpByState(unalloc);
	if(ip_try_alloc==0) ip_try_alloc = getIpByState(time_out);
	if(ip_try_alloc==0) return;
	pool[ip_try_alloc].h = sender;
	pool[ip_try_alloc].state = waitalloc;
	pool[ip_try_alloc].timeout = getTimeout();
	sendMessage("OFR");
}
void REQHandler(){
	if(receiver=="*")
		return ;
	if(receiver!=H){
		from_to(i,1,N+1){
			if(pool[i].h!=sender||pool[i].state!=waitalloc) continue;
			pool[i].state = unalloc;
			pool[i].h.clear();
			pool[i].timeout = 0;
		}
		return ;
	}
	if(sender_ip>=1&&sender_ip<=N&&pool[sender_ip].h==sender){
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
		updateState();
		messageHandler();
	}
	return 0;
}