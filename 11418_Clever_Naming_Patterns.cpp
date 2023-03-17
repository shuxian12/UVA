/*
source -> index of problems -> names,alphabet -> sink
實際放置位置： 0 -> 27~27+n -> 照alpha放(只word需要開頭即可) -> 1~26 -> 27
*/
#include <iostream>
#include <cstring>
#include <cctype>
#include <queue>
#include <algorithm>
#define INF 2147483647

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2413
// https://www.pinghenotes.com/UVa-11418-Clever-Naming-Patterns/

using namespace std;

void normalize(string& s){
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	s[0] = toupper(s[0]);
	// cout << s << endl;
}

int N, n, k;
const int s = 0;
const int t = 27;
int flow[t << 1][t << 1];
string name[t << 1][t << 1];

int pre[t << 1];
int bottle[t << 1];

bool bfs(){
	memset(pre, -1, sizeof(pre));
	queue<int> q;
	q.push(s);
	pre[s] = s;
	bottle[s] = INF;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i = 0; i < t + 1 + n; ++i){
			if(flow[u][i] == 0 || pre[i] != -1) continue;    //沒容量或已經走過
			pre[i] = u;
			bottle[i] = min(bottle[u], flow[u][i]);
			if(i == t) return true;
			q.push(i);
		}
	}
	return false;
}

void EdmondsKarp(){
	while(bfs()){
		int b = bottle[t];
		int v = t;
		while(pre[v] != v){
			int u = pre[v];
			flow[u][v] -= b;
			flow[v][u] += b;
			v = u;
		}
	}
}

int main(){
	cin >> N;
	for(int tc = 1; tc <= N; ++tc){
		memset(flow, 0, sizeof(flow));
		cin >> n;
		for(int i = 0; i < n; ++i){
			cin >> k;
			flow[s][i + t + 1] = 1;	// source -> index of problems
			flow[i + 1][t] = 1;	// alpha -> sink
			for(int j = 0; j < k; ++j){
				string str;
				cin >> str;
				normalize(str);
				int letter = str[0] - 'A' + 1;
				if(letter <= n){
					flow[i + t + 1][letter] = 1;	//把alpha的位置放在最前面方，方便直接取值
					name[i + t + 1][letter] = str;
				}
			}
		}
		EdmondsKarp();
		cout << "Case #" << tc << ":\n";
		for(int i = 1; i <= n; ++i){	// letter
			for(int j = 0; j < n; ++j){	// problem
				if(flow[j + t + 1][i] == 0 && flow[i][j + t + 1] != 0){	////求残余网络中：一个方向还残余容量，另一个方向没有容量的边
					cout << name[j + t + 1][i] << endl;
					break;
				}
			}
		}
	}
}