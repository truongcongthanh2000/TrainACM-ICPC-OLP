#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
// #include "uint128_t.h"

using namespace std;

#define INP "OB"
#define OUT "OB"
#define X first
#define Y second

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

using u64 = uint64_t;
 using u128 = __uint128_t;
 u64 binpower(u64 base, u64 e, u64 mod) {
     u64 result = 1;
     base %= mod;
     while (e) {
         if (e & 1)
             result = (u128)result * base % mod;
         base = (u128)base * base % mod;
         e >>= 1;
     }
     return result;
 }

 bool check_composite(u64 n, u64 a, u64 d, int s) {
     u64 x = binpower(a, d, n);
     if (x == 1 || x == n - 1)
         return false;
     for (int r = 1; r < s; r++) {
         x = (u128)x * x % n;
         if (x == n - 1)
             return false;
     }
     return true;
 };
 bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
     if (n < 4)
         return n == 2 || n == 3;
     int s = 0;
     u64 d = n - 1;
     while ((d & 1) == 0) {
         d >>= 1;
         s++;
     }
     for (int i = 0; i < iter; i++) {
         // int a = 2 + rand() % (n - 3);
         u64 a = 2 + rand() % (n - 3);
         if (check_composite(n, a, d, s))
             return false;
     }
     return true;
 }

int inv(int n){
    if (n == 6) return 9;
    if (n == 9) return 6;
    return n;
}

void sol(){
    u64 n;
    cin >> n;
    if (!MillerRabin(n, 20)){
        cout << "No";
        return;
    }
    u64 m = 0;
    while (n > 0){
        int t = n % 10;
        if (t == 3 || t == 4 || t == 7){
            cout << "No";
            return;
        }
        m = m * 10 + inv(n % 10);
        n /= 10;
    }
//    cout << m;
    cout << (MillerRabin(m, 20) ? "Yes" : "No");
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
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
//    open_file();
    solve();
}
