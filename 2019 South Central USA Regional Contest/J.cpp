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

string s[maxN];
void sol() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    int ok = 1;
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = 0; j < n; j++) {
            if (s[i][j] == 'B') t++;
            else t--;
        }
        if (t != 0) {
            ok = 0;
            break;
        }
        t = 0;
        for (int j = 0; j < n; j++) {
            if (s[j][i] == 'B') t++;
            else t--;
        }
        if (t != 0) {
            ok = 0;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 2; j++) {
            if (s[i][j] == s[i][j + 1] && s[i][j + 1] == s[i][j + 2]) {
                ok = 0;
                break;
            }
            if (s[j][i] == s[j + 1][i] && s[j + 1][i] == s[j + 2][i]) {
                ok = 0;
                break;
            }
        }
    }
    cout << ok;
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

