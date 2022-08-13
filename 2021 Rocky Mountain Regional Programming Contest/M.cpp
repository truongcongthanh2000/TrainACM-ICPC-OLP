#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    std::copy(std::istream_iterator<T>(is), std::istream_iterator<T>(), std::back_inserter(v));
    return is;
}
/* end template */

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
const int N = 3e5 + 5;

#define ll long long

int n;
vector<int> adj[N];
int lim[N], value[N];
set<int> s[N];
ll sum[N];
map<int, int> pos;

void dfs(int u) {
    if (lim[u] > 0) 
        s[u].insert(value[u]);
    for (int v : adj[u]) {
        dfs(v);
        if (s[u].size() < s[v].size()) {
            swap(s[u], s[v]);
        }
        for (int val : s[v]) {
            s[u].insert(val);
        }
        while ((int) s[u].size() > lim[u]) {
            s[u].erase(s[u].begin());
        }
    }
}
void sol() {
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int j;
        cin >> j;
        adj[j].push_back(i);
        // cout << j << ' ' << i << '\n';
    }
    for (int i = 1; i <= n; ++i) {
        cin >> lim[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
        pos[value[i]] = i;
        
    }
    dfs(1);
    ll ans = 0;
    vector<int> res;
    for (int i : s[1]) {
        ans += i;
        res.push_back(pos[i]);
    }
    cout << ans << '\n';
    cout << res.size() << ' ';
    sort(res.begin(), res.end());
    for (int i : res) {
        cout << i << ' ';
    }
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
