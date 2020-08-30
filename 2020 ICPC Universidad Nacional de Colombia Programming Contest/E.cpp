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
//    #ifdef THEMIS
//        freopen(INP ".inp","r",stdin);
//        freopen(OUT ".out","w",stdout);
//    #endif // THEMIS
}

const int maxN = 5e5 + 100;

int Ask(long long x) {
    cout << x << endl;
    int d;
    cin >> d;
    return d;
}

void sol() {
    int n;
    cin >> n;
    long long root = 1;
    for (int d = Ask(root); d > 0; ) {
        int nxt = Ask(root * 2);
        if (d < nxt) root = root * 2 + 1;
        else root = root * 2;
        if (d == 1) {
            cout << "! " << root << endl;
            return;
        }
        d--;
    }
    cout << "! " << root << endl;
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
