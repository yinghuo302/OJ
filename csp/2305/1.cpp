#include <bits/stdc++.h>
using namespace std;
string countAndSay(int n) {
        if(n==1) return "1";
        string prev = countAndSay(n-1);
        string ans = "";
        char last=prev[0]; int cnt = 0;
        for(auto ch: prev){
            if(ch!=last)
				ans.append( to_string(cnt)).push_back(last);
            else
                cnt++;
        }
        return prev;
    }
int main(){
	int n;
	cin >> n;
	unordered_map<string, int> cnt;
	while(n!=0){
		string str; 
		str.reserve(64);
		string tem;
		for(int i=0;i<8;i++){
			cin >> tem;
			str.append(tem);
		}
		cnt[str]++;
		cout << cnt[str] << '\n';
		n--;
	}
	return 0;
}