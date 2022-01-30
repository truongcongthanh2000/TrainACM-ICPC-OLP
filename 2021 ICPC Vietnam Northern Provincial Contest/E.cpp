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

long long dp[16][200][200][3];
bool ok[200];
bool prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
void sol() {
    vector<int> primes;
    for (int i = 2; i <= 135; i++) {
        ok[i] = prime(i);
        if (ok[i]) primes.push_back(i);
    }
    long long n;
    cin >> n;
    string sn = std::to_string(n);
    reverse(sn.begin(), sn.end());
    int sz = (int)sn.size();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            int z = x + 2 * y;
            if (z % 10 == sn[0] - '0') {
                dp[1][x][y][z / 10]++;
            }
        }
    }
    for (int idx = 1; idx < sz; idx++) {
        for (int sx = 0; sx <= 135; sx++) {
            for (int sy = 0; sy <= 135; sy++) {
                for (int du = 0; du <= 2; du++) {
                    if (dp[idx][sx][sy][du]) {
                        for (int x = 0; x < 10; x++) {
                            for (int y = 0; y < 10; y++) {
                                int z = x + 2 * y + du;
                                if (z % 10 == sn[idx] - '0') {
                                    int ndu = z / 10;
                                    dp[idx + 1][sx + x][sy + y][ndu] += dp[idx][sx][sy][du];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int x : primes) {
        for (int y : primes) {
            ans += dp[sz][x][y][0];
        }
    }
    cout << ans << '\n';
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
