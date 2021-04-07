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
    for (int i = 1; i <= n; i++) {
        int d, t;
        cin >> d >> t;
        a[t]++;
        a[t - d]++;
        a[t - 2 * d]++;
    }
    cout << (*max_element(a, a + maxN) + 1) / 2;
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
