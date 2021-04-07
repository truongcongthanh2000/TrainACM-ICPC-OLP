#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 10;

long long F[maxN], minF[maxN];
long long oldF[maxN];
vector<int> adj[maxN];
void sol() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> F[i];
        oldF[i] = F[i];
    }
    for (int i = n; i >= 1; i--) {
        int numNode = 0;
        long long sumF = 0;
        for (int u : adj[i]) {
            if (F[u] > 0) {
                numNode++;
                sumF += F[u];
            }
        }
        if (numNode == (int)adj[i].size() && numNode > 0) F[i] = sumF;
        if (F[i] > 0) minF[i] = F[i];
        else {
            for (int u : adj[i]) {
                minF[i] += minF[u];
            }
            minF[i] = max(1LL, minF[i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        long long pushDown = F[i];
        int numZero = 0;
        for (int u : adj[i]) {
            pushDown -= minF[u];
            numZero += F[u] == 0;
        }
        if (pushDown == 0 || numZero == 1) {
            for (int u : adj[i]) {
                if (F[u] == 0) {
                    F[u] = minF[u] + pushDown;
                }
            }
        }
        if (F[i] == 0) {
            cout << "impossible";
            return;
        }
        if (oldF[i] > 0 && F[i] != oldF[i]) {
            cout << "impossible";
            return;
        }
    }
    for (int i = 1; i <= n; i++) cout << F[i] << '\n';

}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
