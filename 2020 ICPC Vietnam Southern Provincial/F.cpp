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

const int maxN = 1e6 + 100;

int z[maxN];
int min_rotation(string s) {
    int a = 0, N = (int)s.size();
    for (int b = 0; b < N; b++) {
        for (int i = 0; i < N; i++) {
            if (a + i == b || s[(a + i) % N] < s[(b + i) % N]) {
                b += max(0, i - 1);
                break;
            }
            if (s[(a + i) % N] > s[(b + i) % N]) {
                a = b;
                break;
            }
        }
    }
    return a;
};

void Zfunction(int z[], string s) {
    int n = (int)s.size();
    for (int i = 1; i <= n; i++) z[i] = 0;
    int L = 1, R = 1;
    for (int i = 2; i <= n; i++) {
        if (i <= R) z[i] = min(z[i - L + 1], R - i + 1);
        while (i + z[i] <= n && s[z[i]] == s[i + z[i] - 1]) z[i]++;
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
}

void sol() {
    int n;
    cin >> n;

    auto readString = [&]() {
        string res;
        string s;
        getline(cin, s);
        while (cin >> s) {
            string tmp;
            for (char c : s) {
                if (c >= 'a' && c <= 'z') tmp += c;
                if (c >= 'A' && c <= 'Z') tmp += c;
            }
            res += tmp;
        }
        return res;
    };

    string inp = readString();
    n = (int)inp.size();
    assert(n % 2 == 0);
    string s = inp.substr(0, n / 2);
    string t = inp.substr(n / 2, n / 2);

    n /= 2;
    string keywords;
    for (int i = 0; i < n; i++) {
        int c = (t[i] - s[i] + 26) % 26;
        if (c == 0) c = 26;
        keywords += char(c + 'a' - 1);
    }
    //keywords: eappleappleappleappleappleappl
    //prefix = eappl
    //min_rotate(prefix) = apple
    string ans;
    Zfunction(z, keywords);
    for (int i = 2; i <= n + 1; i++) {
        if (i + z[i] == n + 1) {
            ans = keywords.substr(0, i - 1);
            break;
        }
    }
    n = (int)ans.size();
    int p = min_rotation(ans);
    for (int i = 0; i < n; i++) cout << ans[(i + p) % n];
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case " << TestCase << ":" << ' ';
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
