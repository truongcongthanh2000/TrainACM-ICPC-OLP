#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 400;
const int maxM = 1e7;
const long long oo = 1e18;
const int module = 1e9 + 7;
const long double du = 1e-9;


void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);

}

vector <int> a[maxN];
int kt[maxN], stk[maxN], top = 0;
int match[maxN];
int n, m;
int link[maxN];
bool Found = false;
void DFS(int u)
{
    for (int i = 0; i < a[u].size(); i++) {
        int v = a[u][i];
        if (kt[v] == 0) {
            kt[v] = 1;
            stk[++top] = v;
            if (match[v] == 0) Found = true;
            else DFS(match[v]);
            if (Found) {
                match[v] = u;
                return;
            }
        }
    }
}
int CapGhep()
{
    int Nlink = n;
    for (int i = 1; i <= n; i++) link[i] = i;
    for (int i = 1; i <= m; i++) match[i] = 0;
    int Old;
    do {
        Old = Nlink;
        for (int i = 1; i <= top; i++) {
            kt[stk[i]] = 0;
        }
        top = 0;
        for (int i = Nlink; i >= 1; i--) {
            Found = false;
            DFS(link[i]);
            if (Found) {
                link[i] = link[Nlink--];
            }
        }
    }
    while (Old != Nlink);
    return n - Old;
}

bool Used[maxN];
int res[maxN][maxN];
bool solve(int val) {
    if (Used[val]) return true;
    for (int i = 1; i <= n; i++) {
        a[i].clear();
        for (int j = 1; j <= n; j++) {
            if (res[i][j] == 0) a[i].push_back(j);
        }
    }
    int resGhep = CapGhep();
    for (int j = 1; j <= n; j++) {
        int i = match[j];
        res[i][j] = val;
    }
    Used[val] = true;
    return resGhep == n;
}
void solve() {
    int k;
    cin >> n >> k;
    m = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> res[i][j];
            if (res[i][j]) Used[res[i][j]] = true;
        }
    }
    bool Ok = true;
    for (int i = 1; i <= n; i++) Ok &= solve(i);
//    if (!Ok) {
//        cout << "NO";
//        return;
//    }
    cout << "YES" << '\n';
    for (int i = 1; i <= n; i++) {
        cout << res[i][1];
        for (int j = 2; j <= n; j++) cout << " " << res[i][j];
        if (i != n) cout << '\n';
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
