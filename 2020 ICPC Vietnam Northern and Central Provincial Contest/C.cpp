#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;

vector<int> primes;
int p[maxN];

void sieve() {
    for (int i = 2; i < maxN; i++) {
        if (!p[i]) {
            for (int j = i; j < maxN; j += i) p[j] = 1;
            primes.push_back(i);
        }
    }
}

int sum(int n) {
    if (n < 10) return n;
    return sum(n / 10) + n % 10;
}
bool check(int n) {
    return sum(n) % 10 == 0;
}
void sol(){
    sieve();
    int m, n;
    cin >> m >> n;
    int i = lower_bound(primes.begin(), primes.end(), m) - primes.begin();
    int res = 0;
    for (int d = 0; d < n; d++) {

        res += check(primes[i + d]);
    }
    cout << res;
}

void solve() {
    int T;
//    cin >> T;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
