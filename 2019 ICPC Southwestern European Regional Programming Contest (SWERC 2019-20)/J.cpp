#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 10;

int power(int a, int n) {
    int res = 1;
    for (; n; n >>= 1, a = 1LL * a * a % MOD) {
        if (n & 1) {
            res = 1LL * res * a % MOD;
        }
    }
    return res;
}

int inverse(int a) {
    return power(a, MOD - 2);
}

int fact[maxN];

void precalc() {
    fact[0] = 1;
    for (int i = 1; i < maxN; i++) fact[i] = 1LL * fact[i - 1] * i % MOD;
}

int numBinaryTree(int n) { ///Catalan(n)
    int numerator = fact[2 * n];
    int denominator = 1LL * fact[n + 1] * fact[n] % MOD;
    return 1LL * numerator * inverse(denominator) % MOD;
}
typedef pair<int, int> i2;
void sol() {
    precalc();
    int n;
    cin >> n;
    vector<int> h(n);
    h.push_back(-1);
    for (int i = 0; i < n; i++) cin >> h[i];
    stack<int> stk;
    int res = 1;
    for (int i = 0; i <= n; i++) {
        if (stk.empty()) {
            stk.push(h[i]);
        }
        else {
            while (!stk.empty() && h[i] < stk.top()) {
                int old_h = stk.top();
                int d = 0;
                while (!stk.empty() && stk.top() == old_h) {
                    d++;
                    stk.pop();
                }
                res = 1LL * res * numBinaryTree(d) % MOD;
            }
            stk.push(h[i]);
        }
    }
    cout << res;
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
