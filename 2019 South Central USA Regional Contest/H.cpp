#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

#define INP "solve"
#define OUT "solve"

using namespace std;

const int INF = 1e9;
void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;

int a[maxN];
void sol() {
    int n;
    cin >> n;
    long long s = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s += a[i];
    }
    sort(a + 1, a + 1 + n);
    int L = 1;
    long long t = 0;
    for (int m = 0; m <= 100000; m++) {
        long long remain = 0;
        while (L <= n && a[L] < m) {
            t += a[L];
            s -= a[L++];
        }
        while (L <= n && a[L] == m) {
            remain += a[L];
            s -= a[L++];
        }
        if (s == t) {
            cout << m;
            return;
        }
        t += remain;
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
