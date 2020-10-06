#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

typedef pair<char, int> i2;

void sol() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<i2> process;
    for (int i = 0; i < n - 1; ){
        int j = i;
        while (j < n - 1 && s[i] == s[j]) j++;
        process.push_back({s[i], j - i});
        i = j;
    }
    int sz = (int)process.size();
    int real = 1, R = 2;
    for (int i = 0; i < sz; i++) {
        char c = process[i].first;
        int len = process[i].second;
        if (c == 'L') {
            assert(real + 1 == R);
            int nxt = real + len;
            R = nxt + 1;
            for (int i = 0; i < len; i++) {
                cout << nxt << '\n';
                nxt--;
            }
            real = nxt;
            if (i == sz - 1) cout << real;
        }
        else {
            cout << real << '\n';
            if (i == sz - 1) {
                for (int i = R; i <= n; i++) cout << i << '\n';
                break;
            }
            for (int i = 0; i < len - 1; i++) cout << (R++) << '\n';
            real = R;
            R = real + 1;
            ///cout << real << " " << R << '\n';
        }
    }
}

void solve() {
    int T;
    //cin >> T;
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
