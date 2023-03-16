/*
 * @Author: zanilia
 * @Date: 2022-08-29 11:36:20
 * @LastEditTime: 2022-08-29 12:12:57
 * @Descripttion: 
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
struct Role{
	unordered_set<string> op;
	unordered_set<string> kind;
	unordered_set<string> resource;
};
typedef string User;
typedef string Group;
unordered_map<string,Role> roles;
unordered_map<User,vector<string>> roles_u_ass;
unordered_map<Group,vector<string>> roles_g_ass;
int n,m,q;
int nv,no,nn,ns,ng;
string tmp;
string query_user,query_op,query_kind,query_resource;
vector<string> query_group;
bool queryRole(const Role& role){
	if((role.op.count(query_op)||role.op.count("*"))&&
		(role.kind.count(query_kind)||role.kind.count("*"))&&
		(role.resource.empty()||role.resource.count(query_resource))
	)
		return true;
	return false;
}
bool queryUser(){
	for(auto& role_name:roles_u_ass[query_user]){
		if(queryRole(roles[role_name]))
			return true;
	}
	return false;
}
bool queryGroup(){
	for(auto& group:query_group){
		for(auto& role_name:roles_g_ass[group]){
			if(queryRole(roles[role_name]))
				return true;
		}
	}
	return false;
}
void initRole(){
	for(int i=0;i<n;++i){
		cin >> tmp >> nv;
		roles.emplace(tmp,Role());
		auto& role = roles[tmp];
		for(int i=0;i<nv;++i){
			cin >> tmp;
			role.op.emplace(tmp);
		}
		cin >> no;
		for(int i=0;i<no;++i){
			cin >> tmp;
			role.kind.emplace(tmp);
		}
		cin >> ns;
		for(int i=0;i<ns;++i){
			cin >> tmp;
			role.resource.emplace(tmp);
		}
	}
}
void initAss(){
	for(int i=0;i<m;++i){
		cin >> tmp;
		char u_g;string user;
		cin >> ns;
		for(int i=0;i<ns;++i){
			cin >> u_g >> user;
			if(u_g=='u'){
				roles_u_ass[user].emplace_back(tmp);
			}else{
				roles_g_ass[user].emplace_back(tmp);
			}
		}
	}
}
void query(){
	for(int i=0;i<q;++i){
		query_group.clear();
		std::cin >> query_user >> ng;
		for(int i=0;i<ng;++i){
			std::cin >> tmp;
			query_group.emplace_back(tmp);
		}
		std::cin >> query_op >> query_kind >> query_resource;
		cout << (queryUser()||queryGroup()) << '\n';
	}
}
int main(){
	std::cin >> n >> m >> q;
	initRole();
	initAss();
	query();
	return 0;
}