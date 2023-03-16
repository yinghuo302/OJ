/*
 * @Author: zanilia
 * @Date: 2022-09-17 15:10:18
 * @LastEditTime: 2022-09-17 15:58:27
 * @Descripttion: 
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#define f_2(i,begin,end) for(int i=begin;i<end;++i)
#define f_2_dec(i,right,left) for(int i=right;i>=left;--i)
static unsigned long next = 1;
/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % 32768);
}
struct Neurons{
	double v,u,a,b,c,d;		
};
struct PulseSource{
	int r;
};
struct Synaphistic{
	int next;
	int D;
	double w;
	Synaphistic(int t,double w,int D):next(t),w(w),D(D){}
};
Neurons neurons[1000];
std::vector<Synaphistic> syn_mp[2000];
PulseSource pulse[1000];
double pulse_sum[1001][1000] = {0};
int N,S,P,T;
double dt;

int r_n;
double v,u,a,b,c,d;

int s,t,D;
double w;

int cur_time = 1;
int cnt[1000] = {0};
inline void sendPulse(int pos){
	for(auto& syn:syn_mp[pos])
		pulse_sum[(cur_time+syn.D)%1001][syn.next] += syn.w;
}
inline void getNextState(int pos,double I){
	double v = neurons[pos].v, u = neurons[pos].u;
	neurons[pos].v = v + dt * (0.04*v*v+5*v+140-u)+I;
	neurons[pos].u = u + dt * neurons[pos].a * (neurons[pos].b*v-u);
	if(neurons[pos].v>=30){
		sendPulse(pos);
		++cnt[pos];
		neurons[pos].v = neurons[pos].c;
		neurons[pos].u += neurons[pos].d;
	}
}
inline void setState(){
	int t_rel = cur_time % 1001;
	f_2(i,0,N){
		getNextState(i,pulse_sum[t_rel][i]);
		pulse_sum[t_rel][i] = 0;	
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cin >> N >> S >> P >> T >> dt;
	int n = 0;
	while(n<N){
		std::cin >> r_n >> v >> u >> a >> b >> c >> d;
		f_2(i,0,r_n){
			neurons[n].v = v;
			neurons[n].u = u;
			neurons[n].a = a;
			neurons[n].b = b;
			neurons[n].c = c;
			neurons[n].d = d;
			n++;
		}
	}
	f_2(i,0,P){
		std::cin >> pulse[i].r;
	}
	f_2(i,0,S){
		std::cin >> s >> t >> w >> D;
		syn_mp[s].emplace_back(Synaphistic{t,w,D});
	}
	while(cur_time<T){
		f_2(i,0,P){
			if(pulse[i].r>myrand())
				sendPulse(i+N);
		}
		setState();
		++cur_time;
	}
	setState();
	double v_min = neurons[0].v,v_max = neurons[0].v;
	int cnt_min = cnt[0],cnt_max = cnt[0];
	f_2(i,1,N){
		v_min = std::min(v_min,neurons[i].v);
		v_max = std::max(v_max,neurons[i].v);
		cnt_min = std::min(cnt_min,cnt[i]);
		cnt_max = std::max(cnt_max,cnt[i]);
	}
	std::cout << std::setprecision(3) <<std::fixed <<  v_min << ' ' << std::setprecision(3) << std::fixed << v_max << '\n' << cnt_min << ' ' << cnt_max;
	return 0;
}