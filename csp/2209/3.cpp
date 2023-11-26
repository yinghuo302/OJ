/*
 * @Author: zanilia
 * @Date: 2023-03-01 13:17:51
 * @LastEditTime: 2023-03-01 15:12:47
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;
unordered_map<int,vector<int>> visit_arr[7];  // 滚动数组，(d-7,d], map<user,place>
unordered_map<int,int> risk_arr[13];  // 滚动数组，(d-7,d+7), map<place,begin_day>
inline unordered_map<int,vector<int>>& visit(int i){ 
	return visit_arr[(i+100000)%7];
}
inline unordered_map<int,int>& risk(int i){
	return risk_arr[(i+100000)%13];
}
int n,r_i,m_i,p_ij,d_ij,u_ij,r_ij;
set<int> ans;
int main(){
	cin >> n;
	for(int i=0;i<n;i++){
		risk(i-7).clear();
		visit(i-7).clear();
		cin >> r_i >> m_i;
		for(int j=0;j<r_i;j++){
			cin >> p_ij;
			int begin = i;
			if(risk(i-1).count(p_ij))
				begin = risk(i-1)[p_ij];
			for(int k=0;k<7;k++)
				risk(i+k)[p_ij] = begin;
		}
		for(int j=0;j<m_i;j++){
			cin >> d_ij >> u_ij >> r_ij;
			if(d_ij-i<=-7)
				continue;
			visit(d_ij)[u_ij].push_back(r_ij);
		}
		ans.clear();
		for(int j=i-6;j<=i;j++){
			for(auto &v:visit(j)){
				for(auto place:v.second)
					if(risk(i).count(place)&&risk(i)[place]<=j)
						ans.insert(v.first);
			}
		}
		cout << i;
		 for(auto& a:ans)
            cout << ' ' << a;
        cout << '\n';
	}
	return 0;
}


