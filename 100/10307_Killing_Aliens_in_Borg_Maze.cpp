#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1248
// https://blog.csdn.net/u012965890/article/details/38493999

int n, m, total;
vector<string>  G(102);
int vis[101][101];
int sx, sy;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

struct node{
    int x, y;
    int w;
    node(int x, int y, int w){
        this->x = x;
        this->y = y;
        this->w = w;
    }
};

struct compare{
    bool operator()(const node& a, const node& b){
        return a.w > b.w;   // 選小的走 // priority要相反
    }
};

int bfs(){  //prim & bfs
    int res = 0;
    priority_queue<node, vector<node>, compare> q;
    memset(vis, 0x3f, sizeof(vis));
    q.push(node(sx, sy, 0));
    vis[sx][sy] = 0;

    while(!q.empty() || total){
        node now = q.top();
        q.pop();

        if(G[now.x][now.y] == 'A'){
            res += now.w;   // 計算步數
            // cout<< now.w << endl;
            total--;
            now.w = 0;  //重新出發
            G[now.x][now.y] = ' ';
        }

        for(int i = 0; i < 4; i++){
            int next_x = now.x + dx[i];
            int next_y = now.y + dy[i];
            int next_w = now.w + 1;
            if(next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) continue;
            if(G[next_x][next_y] != '#' && vis[next_x][next_y] > next_w){   //格子是可以重覆走的，但只有比之前到達這個格子的步數少才走。 
                vis[next_x][next_y] = next_w;
                // cout<< next_x << " " << next_y << " " << next_w << endl;
                q.push(node(next_x, next_y, next_w));
            }
        }
    }
    return res;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        string line;
        cin >> m >> n;   // 反人體工學
        cin.ignore();
        for(int i = 0; i < n; i++){
            getline(cin, line);
            G[i] = line;
        }
        total = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(G[i][j] == 'S'){
                    sx = i;
                    sy = j;
                }
                if(G[i][j] == 'A'){
                    total++;
                }
            }
        }
        cout << bfs() << endl;
    }
}