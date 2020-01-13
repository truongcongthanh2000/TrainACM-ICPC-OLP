#include <bits/stdc++.h>
using namespace std;
const int MaxN=100005*2;
int n;
vector <int> a[MaxN];

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

int h[MaxN],cha[MaxN][20],k = 0,m = 0,L[MaxN],R[MaxN];
void DFS(int u)
{
    L[u] = ++k;
    m = max(m, h[u]);
    for (int i = 0; i < 18; i++) {
        if (cha[u][i] == 0) break;
        int v = cha[u][i];
        cha[u][i + 1] = cha[v][i];
    }
    for (int v : a[u])
        if (cha[u][0] != v){
            h[v] = h[u] + 1;
            cha[v][0] = u;
            DFS(v);
        }
    R[u] = k;
}

bool Checkroot(int u,int v){
    return L[u] <= L[v] && R[v] <= R[u];
}

int Jump(int u,int v) {
    int delta = h[v] - h[u];
    for(int i = log2(delta); i >= 0; i--)
        if ((delta >> i)&1 == 1)
            v = cha[v][i];
    return v;
}

int LCA(int u,int v) {
    if (h[u] <= h[v]) {
        v=Jump(u,v);
        if (v == u) return u;
        for (int i = 18; i >= 0; i--)
            if (cha[u][i] != cha[v][i]){
                u = cha[u][i];
                v = cha[v][i];
            }
        return cha[u][0];
    }
    else return LCA(v,u);
}

void solve() {
    //cerr << "OK" << '\n';
    cin >> n;
    for (int i = 1; i < n; i++){
        int x,y;
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    //cerr << "OK" << '\n';
    DFS(1);
    //for (int i = 1; i <= n; i++) cout << L[i] << " " << R[i] << '\n';
    int q;
    cin >> q;
    while (q--){
        int r,b;
        cin >> r >> b;
        int t[r+b+2];
        for (int i = 0; i < r; i++) cin >> t[i];
        for (int i = r; i < r+b; i++) cin >> t[i];
        int temp1=t[0],temp2=t[r];
        for (int i = 1; i < r; i++) temp1=LCA(temp1,t[i]);
        for (int i = r; i < r+b; i++) temp2=LCA(temp2,t[i]);
        //cout << temp1 << " " << temp2 << '\n';
        bool check1 = false;
        for (int i = 0; i < r; i++)
            check1 |= Checkroot(temp2, t[i]);
        bool check2 = false;
        for (int i = r; i < r + b; i++)
            check2 |= Checkroot(temp1, t[i]);
        cout << ((check1 & check2) ? "NO" : "YES") << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);

    solve();
}
