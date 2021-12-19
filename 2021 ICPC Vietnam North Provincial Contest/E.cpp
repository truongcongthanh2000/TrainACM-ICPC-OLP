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

int Used[500][500];
long long dp[500][500];
long long F(int n, int S) {
    if (S < 0) return 0;
    if (S > n * 9) return 0;
    if (n == 0)
        return S == 0;
    if (Used[n][S]++) return dp[n][S];
    long long &res = dp[n][S];
    for (int i = 0; i < 10; i++) res += F(n - 1, S - i);
    return res;
}

long long get(long long sz, int S) {
    int n = 1;
    while (true) {
        long long s = 0;
        for (int i = 1; i < 10; i++) {
            s += F(n - 1, S - i);
            if (s >= sz) break;
        }
        if (s >= sz) break;
        sz -= s;
        n += 1;
    }
    long long res = 0;
    for (int sl = 1; sl <= n; sl++) {
        for (int i = (sl == 1 ? 1 : 0); i < 10; i++) {
            long long val = F(n - sl, S - i);
            if (val >= sz) {
                res = res * 10 + i;
                S -= i;
                break;
            }
            else sz -= val;
        }
    }
    assert(S == 0);
    return res;
}

bool prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
void sol() {
    vector<int> primes;
    for (int i = 2; i <= 135; i++) {
        if (prime(i)) primes.push_back(i);
    }
    long long limits = 1e15;
    for (int p : primes) {
        cout << "Prime = " << p << ": ";
        int idx = 1;
        while (true) {
            long long v = get(idx, p);
            if (v > limits) break;
            idx++;
        }
        cout << idx - 1 << endl;
    }
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    //cin >> T;
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
