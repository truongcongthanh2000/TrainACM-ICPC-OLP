 #pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
//#include <boost/date_time.hpp>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 100;

struct DinicFlow { ///Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9; ///if flow > int, use long long
    int n, numEdge;
    vector <int> point, next, head, Dist, work;
    vector <int> flow, cap; ///if flow > int, use long long

    DinicFlow(int _n = 0) {
        n = _n; numEdge = 0;
        head.assign(n + 5, -1);
        work.assign(n + 5, -1);
        Dist.assign(n + 5, 0);
    }

    void add_Edge(int u, int v, int c1, int c2 = 0) {///if flow > int, use long long c1, c2
        ///u -> v: c1
        point.push_back(v); flow.push_back(0); cap.push_back(c1); next.push_back(head[u]); head[u] = numEdge++;
        ///v -> u: c2
        point.push_back(u); flow.push_back(0); cap.push_back(c2); next.push_back(head[v]); head[v] = numEdge++;
    }

    bool BFS(int s, int t) { ///check has path from s to t
        queue <int> Q;
        for (int i = 0; i <= n; i++) Dist[i] = -1;
        Dist[s] = 0;
        Q.push(s);
        while ((int)Q.size() != 0) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = point[i];
                if (flow[i] < cap[i] && Dist[v] == -1) {
                    Dist[v] = Dist[u] + 1;
                    if (v == t) return true;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    int DFS(int s, int t, int f) { ///if flow > int, use long long
        if (f == 0) ///Min F always >= 0 so if f = 0 break recursive
            return f;
        if (s == t)
            return f;
        for (int &i = work[s]; i >= 0; i = next[i]) { ///&i so important, don't use i = work[s] because it's maybe TLE
            int v = point[i];
            if (flow[i] < cap[i] && Dist[v] == Dist[s] + 1) {
                int D = DFS(v, t, min(f, cap[i] - flow[i]));
                if (D > 0) {
                    flow[i] += D;
                    flow[i ^ 1] -= D;
                    return D;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) { ///if flow > int, use long long
        int Flow = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int d = DFS(s, t, oo);
                if (d == 0) break;
                Flow += d;
            }
        }
        return Flow;
    }

    int GetFlow(int idEdge) {
        return flow[idEdge];
    }
};

int a[maxN];
string b[maxN], c[maxN];
void sol() {
    int n, m, k, L;
    cin >> n >> m >> k >> L;
    set<int> A;
    set<string> B, C;
    for (int i = 1; i <= L; i++) {
        cin >> a[i] >> b[i] >> c[i];
        A.insert(a[i]);
        B.insert(b[i]);
        C.insert(c[i]);
    }
    vector<int> vA(A.begin(), A.end());
    vector<string> vB(B.begin(), B.end());
    vector<string> vC(C.begin(), C.end());

    int s = 0, t = n + m * 2 + k + 1;
    DinicFlow df(t);
    for (int i = 1; i <= n; i++) df.add_Edge(s, i, 1);
    for (int i = 1; i <= m; i++) df.add_Edge(i + n, i + n + m, 1);
    for (int i = 1; i <= L; i++) {
        int u = lower_bound(vA.begin(), vA.end(), a[i]) - vA.begin() + 1;
        int v = lower_bound(vB.begin(), vB.end(), b[i]) - vB.begin() + 1;
        int z = lower_bound(vC.begin(), vC.end(), c[i]) - vC.begin() + 1;
        df.add_Edge(u, v + n, 1);
        df.add_Edge(v + n + m, z + n + m + m, 1);
    }
    for (int i = 1; i <= k; i++) df.add_Edge(i + n + m + m, t, 1);
    cout << df.maxFlow(s, t) << '\n';
}
void solve() {
    int T;
    cin >> T;
    //T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case " << TestCase << ":" << ' ';
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
