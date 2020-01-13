#include <bits/stdc++.h>
using namespace std;
const int MaxN = 1e6+5;

int n, m, q, P[1005][1005];
void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

struct tree {
    int x,y,w;
    tree(){};
    tree(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {};
    bool operator < (const tree &A) {
        return w < A.w;
    }
};
vector<tree> canh;

void cre_path(int i, int j, int x, int y){
    if (x >= n || y >= m) return;
    int w = max(P[i][j], P[x][y]);
    int u = i * m + j;
    int v = x * m + y;
    canh.push_back(tree(u, v, w));
}

int root[MaxN];
int findroot(int x){
    return root[x] < 0 ? x : root[x] = findroot(root[x]);
}

void Union(int s,int t){
    root[s] += root[t];
    root[t] = s;
}

vector <int> a[MaxN], b[MaxN];

void Cre_graph(){
    cin >> n >> m >> q;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> P[i][j];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            cre_path(i,j,i,j+1);
            cre_path(i,j,i+1,j);
        }
    sort(canh.begin(), canh.end());
    for(int i = 0; i <= n * m; i++) root[i] = -1;
    for(int i = 0; i < canh.size(); i++){
        int u = canh[i].x;
        int v = canh[i].y;
        int w = canh[i].w;
        int s = findroot(u);
        int t = findroot(v);
        //cerr << u << " " << v << " " << s << " " << t << " " << w << '\n';
        if (s != t) {
            Union(s, t);
            a[u].push_back(v);
            b[u].push_back(w);
            a[v].push_back(u);
            b[v].push_back(w);
        }
    }
}

int h[MaxN], cha[MaxN][22], F[MaxN][22];

void DFS(int u){
    for(int i = 0; i <= 20; i++){
        int v = cha[u][i];
        if (v == 0) break;
        cha[u][i + 1] = cha[v][i];
        F[u][i + 1] = max(F[u][i], F[v][i]);
    }
    for(int i = 0; i < a[u].size(); i++){
        int v = a[u][i];
        int w = b[u][i];
        if (v != cha[u][0]) {
            cha[v][0] = u;
            F[v][0] = w;
            h[v] = h[u] + 1;
            DFS(v);
        }
    }
}

int Jump(int u,int v){
    int delta = h[v] - h[u];
    for(int i = 19; i >= 0; i--)
        if ((delta >> i) & 1)
            v = cha[v][i];
    return v;
}

int LCA(int u, int v) {
    if (h[u] <= h[v]){
        v = Jump(u, v);
        if (u == v) return u;
        for(int i = 19; i >= 0; i--)
            if (cha[u][i] != cha[v][i]){
                u = cha[u][i];
                v = cha[v][i];
            }
        return cha[u][0];
    }
    else return LCA(v,u);
}

int mcost(int u,int v){
    int delta = h[v] - h[u];
    int temp = 0;
    for(int i = 19; i >= 0; i--)
        if ((delta >> i) & 1){
            temp = max(temp, F[v][i]);
            v = cha[v][i];
        }
    return temp;
}

void solve(){
    Cre_graph();
    DFS(0);
    //cerr << "OK" << '\n';
    for(int i = 0; i < q; i++){
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        x--;
        y--;
        u--;
        v--;
        int s = x * m + y;
        int t = u * m + v;
        if (s == t) cout << P[x][y];
        else{
            int x = LCA(s, t);
            //cerr << s << " " << t << " " << x << '\n';
            int res = max(mcost(x, s), mcost(x, t));
            cout << res;
        }
        cout << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
