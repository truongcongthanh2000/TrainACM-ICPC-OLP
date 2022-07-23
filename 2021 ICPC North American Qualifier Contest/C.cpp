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

int lp[maxN];

void sieve() {
    for (int i = 2; i * i < maxN; ++i) {
        if (!lp[i]) {
            for (int j = i; j * j < maxN; j += i) lp[j] = i;
        }
    }
    for (int i = 2; i < maxN; ++i) {
        if (!lp[i]) lp[i] = i;
    }
}

void sol() {
    sieve();
    long long n; cin >> n;
    long long den = 1;
    long long num = 1;
    for (int i = 2; i < maxN; ++i) {
        if (lp[i] != i) continue; 
        if (n / i >= den) {
            den *= i;
            num *= i - 1;
        }
    }
    long long g = __gcd(den, num);
    cout << (den - num) / g << "/" << den / g;
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
    cerr << "\nTime = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
