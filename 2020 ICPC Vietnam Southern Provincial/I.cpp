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

const int maxN = 2e5 + 100;

int Hash(string s) {
    long long res = 0;
    for (char c : s) {
        res = (res * Base + (int)c) % MOD;
    }
    return res;
}
int value[maxN];
long long pw[maxN], H[maxN];
int nxt[maxN][105];
void sol() {
    string P, S;
    cin >> P >> S;
    if ((int)P.size() == 0 || (int)S.size() == 0) {
        cout << 0;
        return;
    }
    vector<string> T;
    int limits = 0;
    for (int i = 0, n = (int)P.size(), d = 0; i < n; d++) {
        int j = i;
        if (P[i] == '*') {
            T.push_back({"*"});
            while (j < n && P[j] == '*') j++;
            value[d] = 0;
        }
        else {
            string tmp;
            while (j < n && P[j] != '*') tmp += P[j++];
            T.push_back(tmp);
            limits += (int)tmp.size();
            value[d] = Hash(tmp);
        }
        i = j;
    }
    int n = (int)S.size();
    S += S.substr(0, n - 1);
    pw[0] = 1;
    for (int i = 1; i < 2 * n; i++) {
        pw[i] = pw[i - 1] * Base % MOD;
        H[i] = (H[i - 1] * Base + (int)S[i]) % MOD;
    }

    auto getHash = [&](int L, int R) {
        return (H[R] - (H[L - 1] * pw[R - L + 1]) % MOD + MOD) % MOD;
    };

    int sz = (int)T.size();
    for (int i = 0; i < sz; i++) nxt[2 * n - 1][i] = 2 * n;
    for (int i = 2 * n - 2; i >= 0; i--) {
        for (int j = 0; j < sz; j++) {
            nxt[i][j] = nxt[i + 1][j];
            if (T[j][0] != '*' && i + (int)T[j].size() < 2 * n) {
                int hash_value = getHash(i + 1, i + (int)T[j].size());
                if (hash_value == value[j]) nxt[i][j] = i + (int)T[j].size();
            }
        }
    }

    auto Check = [&](int L, int R) {
        if (sz == 1) {
            if (T[0][0] == '*') return true;
            return (int)T[0].size() == R - L + 1 && T[0] == S.substr(L, R - L + 1);
        }
        if (R - L + 1 < limits) return false;
        if (sz == 2) {
            if (T[0][0] != '*') {
                return T[0] == S.substr(L, (int)T[0].size());
            }
            else {
                return T[1] == S.substr(R - (int)T[1].size() + 1, (int)T[1].size());
            }
        }
        if (sz == 3 && T[0][0] != '*') {
            bool ok = T[0] == S.substr(L, (int)T[0].size());
            ok &= T[2] == S.substr(R - (int)T[2].size() + 1, (int)T[2].size());
            return ok;
        }
        int first = 0, last = sz - 1;
        if (T[0][0] != '*') {
            if (T[0] != S.substr(L, (int)T[0].size())) return false;
            L += (int)T[0].size();
            first = 1;
        }
        if (T.back()[0] != '*') {
            if (T.back() != S.substr(R - (int)T.back().size() + 1, (int)T.back().size())) {
                return false;
            }
            R -= (int)T.back().size();
            last--;
        }
        for (int i = first; L <= R + 1 && i <= last; i += 2) {
            assert(T[i][0] == '*');
            L = nxt[L][i + 1];
        }
        return L <= R + 1;
    };
    int res = 0;
    for (int i = 0; i < n; i++) res += Check(i, i + n - 1);
    cout << res;
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
