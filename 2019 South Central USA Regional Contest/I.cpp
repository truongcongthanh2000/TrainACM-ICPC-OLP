#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

#define INP "solve"
#define OUT "solve"

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 10000;
const long long MOD = 998244353;
int lp[maxN];
int mobius[maxN];
int coeff[maxN];

void sol() {
    int n;
    cin >> n;
    if (n & 1) cout << "Either";
    else {
        if ((n / 2) % 2) cout << "Odd";
        else cout << "Even";
    }
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

