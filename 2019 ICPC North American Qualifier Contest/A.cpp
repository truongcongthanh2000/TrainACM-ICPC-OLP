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

void sol() {
    int n;
    cin >> n;
    vector<int> a(26, 0);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'T') a[i] = 1;
    }
    char c;
    stack<int> stk;
    while (cin >> c) {
        if (c >= 'A' && c <= 'Z') {
            int v = c - 'A';
            stk.push(a[v]);
        }
        else {
            int u = stk.top(); stk.pop();
            if (c == '+') {
                int v = stk.top(); stk.pop();
                stk.push(u | v);
            }
            if (c == '*') {
                int v = stk.top(); stk.pop();
                stk.push(u & v);
            }
            if (c == '-') stk.push(u ^ 1);
        }
    }
    cout << (stk.top() ? 'T' : 'F');
}

void solve() {
    int T;
    ///cin >> T;
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
