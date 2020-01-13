#include <bits/stdc++.h>
using namespace std;
const   int MaxN = 1e5+5;

int n, m, deg[MaxN], f[MaxN];
struct data{
    int x,c;
    data (){};
    data (int _x, int _c) : x(_x), c(_c) {};
};

vector<data> a[MaxN];
int top, bot, q[MaxN], res;

void solve(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back(data(v, w));
        deg[v]++;
    }
    top = bot = 0;
    for(int i = 0; i < n; i++)
        if (deg[i] == 0)
            q[++top] = i;
    while (bot < top){
        int u = q[++bot];
        for(data x : a[u]) {
            int v = x.x;
            int w = x.c;
            f[v] = max(f[v], f[u] + w);
            deg[v]--;
            if (deg[v] == 0) q[++top] = v;
        }
        res = max(res, f[u]);
    }
    cout << res;
}

int main(){

    solve();
}
