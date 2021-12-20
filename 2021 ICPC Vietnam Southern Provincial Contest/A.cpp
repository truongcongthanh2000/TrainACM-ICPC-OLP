#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

struct DinicFlow { ///Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9; ///if flow > int, use long long
    int n, numEdge;
    vector <int> point, next, head, Dist, work;
    vector <int> flow, cap; ///if flow > int, use long long

    DinicFlow(int _n = 0) {
        n = _n; numEdge = 0;
        head.assign(n + 7, -1);
        work.assign(n + 7, -1);
        Dist.assign(n + 7, 0);
        point.clear();
        cap.clear();
        flow.clear();
        next.clear();
    }

    void rs() {
        numEdge = 0;
        head.assign(n + 7, -1);
        work.assign(n + 7, -1);
        Dist.assign(n + 7, 0);
        point.clear();
        cap.clear();
        flow.clear();
        next.clear();
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

// Source: RR
// Tested with VOJ - MCQUERY

/*
 * Find min cut between every pair of vertices using N max_flow call (instead of N^2)
 * Not tested with directed graph
 * Index start from 0
 */
struct GomoryHu {
    int ok[202], cap[202][202];
    int answer[202][202], parent[202];  
    int n;
    DinicFlow flow;

    GomoryHu(int _n) : n(_n), flow(_n) {
        for(int i = 0; i < n; ++i) ok[i] = parent[i] = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                cap[i][j] = 0, answer[i][j] = INF;
    }

    void addEdge(int u, int v, int c) {
        cap[u][v] += c;
    }

    void calc() {
        for(int i = 0; i < n; ++i) parent[i]=0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                answer[i][j]=INF;

        for(int i = 1; i <= n-1; ++i) {
            flow.rs();
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    if (cap[u][v]) {
                        flow.add_Edge(u, v, cap[u][v]);
                    }
                }
            }
            int f = flow.maxFlow(i, parent[i]);

            bfs(i);
            for(int j = i+1; j < n; ++j)
                if (ok[j] && parent[j]==parent[i])
                    parent[j]=i;
            
            answer[i][parent[i]] = min(f, answer[i][parent[i]]);
            for(int j = 0; j < i; ++j)
                answer[i][j]=answer[j][i]=min(f,answer[parent[i]][j]);
        }
    }
    void bfs(int start) {
        memset(ok,0,sizeof ok);
        queue<int> qu;
        qu.push(start);
        while (!qu.empty()) {
            int u=qu.front(); qu.pop();
            for (int i = flow.head[u]; i >= 0; i = flow.next[i]) {
                int v = flow.point[i];
                if (!ok[v] && flow.flow[i] < flow.cap[i]) {
                    ok[v] = 1;
                    qu.push(v);
                }
            }
        }
    }
};
void sol() {
    int n;
    cin >> n;
    vector<vector<int> > a(n, vector<int>(n, 0));
    GomoryHu gh(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            gh.addEdge(i, j, a[i][j]);
        }
    }
    gh.calc();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) cout << 0 << ' ';
            else cout << gh.answer[i][j] << ' ';
        }
        cout << '\n';
    }
}

void solve() {
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cerr << "Processing test = " << TestCase << '\n';
        cout << "Case #" << TestCase << ":" << '\n'; 
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
