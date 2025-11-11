#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"

void doc() {
    #ifdef THEMIS
        freopen(TASK ".inp", "r", stdin);
        freopen(TASK ".out", "w", stdout);
    #endif
}
template <typename A, typename B>
string to_string(pair<A, B> p);
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
 
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}
 
void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
 
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
const int maxN = 5e5 + 100;
struct MaxBipartiteMatching { ///base 1th; X -> Y
    int n, m;
    vector <int> link, match, stk, Used;
    bool Found;
    vector <vector<int> > adj;
    MaxBipartiteMatching(){};
    MaxBipartiteMatching(int _n, int _m) {
        n = _n; ///Size(X)
        m = _m; ///Size(Y)
        link.assign(n + 7, 0); ///X
        match.assign(m + 7, 0); ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        Used.assign(m + 7, 0);
        stk.clear();
        adj.resize(n + 7);
    }

    void addEdge(int u, int v) { ///u in X and v in Y
        adj[u].push_back(v);
    }

    void DFS(int u) {
        for (int v : adj[u]) {
            if (Used[v] == 0) {
                Used[v] = 1;
                stk.push_back(v);
                if (match[v] == 0) Found = true;
                else DFS(match[v]);
                if (Found) {
                    match[v] = u;
                    return;
                }
            }
        }
    }

    int getCost() { ///get size MaxBipartiteMatching
        int Nlink = n;
        for (int i = 1; i <= n; i++) link[i] = i;
        for (int i = 1; i <= m; i++) match[i] = 0;
        int old;
        do {
            old = Nlink;
            for (int x : stk) Used[x] = 0;
            stk.clear();
            for (int i = Nlink; i >= 1; i--) {
                Found = false;
                DFS(link[i]);
                if (Found) {
                    link[i] = link[Nlink--];
                }
            }
        }
        while (old != Nlink);
        return n - old;
    }

    int getX(int y) { ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        return match[y];
    }
};

array<int, 2> e[maxN];
vector<int> adj[maxN];
int number[maxN], low[maxN], order = 0;
int TP[maxN], nTPLT = 0;
stack<int> stk;
void DFS(int u) {
    number[u] = ++order;
    low[u] = number[u];
    stk.push(u);
    for (int v : adj[u]) {
        if (TP[v] == 0) {
            if (number[v] == 0) {
                DFS(v);
                low[u] = min(low[u], low[v]);
            }
            else low[u] = min(low[u], number[v]);
        }
    }
    if (low[u] == number[u]) {
        int v;
        nTPLT += 1;
        do {
            v = stk.top(); stk.pop();
            TP[v] = nTPLT;
        }
        while (v != u);
    }
}
void sol() {
    int n, m;
    cin >> n >> m;
    MaxBipartiteMatching mbm(n, n);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        mbm.addEdge(u, v);
        e[i][0] = u;
        e[i][1] = v;
    }
    
    int cost = mbm.getCost();
    debug(cost);
    set<pair<int, int> > used;
    for (int i = 1; i <= m; i++) {
        int u = e[i][0], v = e[i][1];
        if (used.find({u, v}) == used.end() && mbm.getX(v) == u) {
            used.insert({u, v});
            adj[v + n].push_back(u);
            debug(u, v);
        }
        else {
            adj[u].push_back(v + n);
        }
    } 
    for (int i = 1; i <= 2 * n; i++) {
        if (number[i] == 0) DFS(i);
    }
    debug(nTPLT);
    int res = 0;
    for (int i = 1; i <= m; i++) {
        int u = e[i][0], v = e[i][1];
        if (mbm.getX(v) == u && TP[u] != TP[v + n]) res++;
    }
    cout << m - res << '\n';
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    while (T--) sol();
}
int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}