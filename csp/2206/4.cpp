/*
 * @Author: zanilia
 * @Date: 2023-03-08 19:00:38
 * @LastEditTime: 2023-03-08 21:15:23
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
using namespace std;
struct Point{
	int x,y;
};
struct Mirror{
	Point a,b;
};
struct Reflection{
	int turn;
	double a;
	Reflection() = default;
	Reflection(int turn,double a):turn(turn),a(a){} 
};
unordered_map<int,Mirror> mirrors;
Mirror tmp_m;
unordered_map<int,map<int,Reflection>> x_mp_l;
unordered_map<int,map<int,Reflection>> y_mp_l;
unordered_map<int,map<int,Reflection,greater<int>>> x_mp_g;
unordered_map<int,map<int,Reflection,greater<int>>> y_mp_g;
double a,I;
int k,op_num,m,x,y,t,d;
char op;
Reflection tmp_r;
void addMirror(){
	int delta_x = (tmp_m.a.x < tmp_m.b.x)? 1: -1;
	int delta_y = (tmp_m.a.y < tmp_m.b.y)? 1: -1;
	int x = tmp_m.a.x +delta_x , y = tmp_m.a.y + delta_y;
	tmp_r.turn = (delta_x==delta_y)? 1:-1;
	while(x!=tmp_m.b.x){
		x_mp_l[x].emplace(y,tmp_r);
		x_mp_g[x].emplace(y,tmp_r);
		y_mp_l[y].emplace(x,tmp_r);
		y_mp_g[y].emplace(x,tmp_r);
		x += delta_x; y += delta_y;
	}
	mirrors[op_num] = tmp_m;
}
void delMirror(){
	tmp_m = mirrors[k];
	int delta_x = (tmp_m.a.x < tmp_m.b.x)? 1: -1;
	int delta_y = (tmp_m.a.y < tmp_m.b.y)? 1: -1;
	int x = tmp_m.a.x +delta_x , y = tmp_m.a.y + delta_y;
	while(x!=tmp_m.b.x){
		x_mp_l[x].erase(y);x_mp_g[x].erase(y);
		y_mp_l[y].erase(x);y_mp_g[y].erase(x);
		x += delta_x; y += delta_y;
	}
	mirrors.erase(k);
}
void reflect(){
	switch (d){
		case 0:{
			auto iter = y_mp_l[y].upper_bound(x);
			if (iter == y_mp_l[y].end()||x+t<iter->first){
				x += t;
				t = 0;
			} else{
				t -= iter->first - x;
				x = iter->first;
				I *= iter->second.a;
				d = (iter->second.turn == 1)? 1 : 3;
			}
			break;
		}
		case 1:{
			auto iter = x_mp_l[x].upper_bound(y);
			if (iter == x_mp_l[x].end()||y+t<iter->first){
				y += t;
				t = 0;
			} else{
				t -= iter->first - y;
				y = iter->first;
				I *= iter->second.a;
				d = (iter->second.turn == 1)? 0 : 2;
			}
			break;
		}
		case 2:{
			auto iter = y_mp_g[y].upper_bound(x);
			if (iter == y_mp_g[y].end()||x-t>iter->first){
				x -= t;
				t = 0;
			} else{
				t -= x - iter->first;
				x = iter->first;
				I *= iter->second.a;
				d = (iter->second.turn == 1)? 3 : 1;
			}
			break;
		}
		case 3:{
			auto iter = x_mp_g[x].upper_bound(y);
			if (iter == x_mp_g[x].end()||y-t>iter->first){
				y -= t;
				t = 0;
			} else{
				t -= y - iter->first;
				y = iter->first;
				I *= iter->second.a;
				d = (iter->second.turn == 1)? 2 : 0;
			}
			break;
		}
	}
}
void calculate(){
	while(I>=1&&t>0){
		reflect();
	}
	if(I>=1){
		cout << x << ' ' << y << ' '<< int(I) << '\n';
	} else {
		cout << "0 0 0\n";
	}
}
int main(){
	cin >> m;
	for(op_num=1;op_num<=m;op_num++){
		cin >> op;
		switch (op){
			case '1' : cin >> tmp_m.a.x >> tmp_m.a.y >> tmp_m.b.x >> tmp_m.b.y >> tmp_r.a;addMirror();break; 
			case '2': cin >> k;delMirror();break;
			case '3': cin >> x >> y >> d >> I >> t;calculate();break;
		}
	}
	return 0;
}
// case 1:{
		// 	auto iter = y_mp[y].lower_bound(x);
		// 	if (iter == y_mp[y].begin()||x-t>(--iter)->pos){
		// 		x -= t;
		// 		t = 0;
		// 	} else{
		// 		t -= x - iter->pos;
		// 		x = iter->pos;
		// 		I *= iter->a;
		// 		d = (iter->turn == 1)? 3 : 2;
		// 	}
		// 	break;
		// }
		// case 2:{
		// 	tmp_r.pos = y;
		// 	auto iter = x_mp[x].upper_bound(y);
		// 	if (iter == x_mp[y].end()||y+t<iter->pos){
		// 		y += t;
		// 		t = 0;
		// 	} else{
		// 		t -= iter->pos - y;
		// 		y = iter->pos;
		// 		I *= iter->a;
		// 		d = (iter->turn == 1)? 0 : 1;
		// 	}
		// 	break;
		// }
		// case 3:{
		// 	tmp_r.pos = y;
		// 	auto iter = x_mp[x].lower_bound(y);
		// 	if (iter == x_mp[x].begin()||y-t>(--iter)->pos){
		// 		y -= t;
		// 		t = 0;
		// 	} else{
		// 		t -= y - iter->pos;
		// 		y = iter->pos;
		// 		I *= iter->a;
		// 		d = (iter->turn == 1)? 1 : 0;
		// 	}
		// 	break;
		// }

// void test(stringstream& in){
// 	in >> op;
// 	switch (op){
// 		case '1' : cin >> tmp_m.first.x >> tmp_m.first.y >> tmp_m.second.x >> tmp_m.second.y >> tmp_r.a;addMirror();break;
// 		case '2': cin >> k;delMirror();break;
// 		case '3': cin >> x >> y >> d >> I >> t;calculate();break;
// 	}
// }

	// stringstream ss;
	// uniform_real_distribution<double> a_dis(0.2,0.8);
	// uniform_real_distribution<double> i_dis(0,1e9);
	// default_random_engine engine;
	// for(int i=0;i<1e6;++i){
	// 	int op = rand()%3 + 1;
	// 	ss << op;
	// 	switch (op){
	// 		case 1:{
	// 			int x1 = rand(),x2 = rand(),y1 = rand();
	// 			int turn = rand()%2;  int y2 = turn? y1 + (x1-x2) : y1 + (x2-x1);
	// 			double a = a_dis(engine);
	// 			ss << op << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << a << '\n';
	// 			test(ss);
	// 			break;
	// 		}
	// 		case 2: {
	// 			if(!mirrors.empty()){
	// 				ss << op << ' '  << (rand()%mirrors.size())+1 << '\n'; 
	// 				test(ss);
	// 			}
	// 			break;
	// 		}
	// 		case 3:{
	// 			ss << rand() << ' ' << rand() << ' ' << rand()%4 << ' ' << i_dis(engine) << ' '
	// 			<< rand()%int(1e8) << '\n'; test(ss);
	// 			break;
	// 		}
	// 	}
	// }