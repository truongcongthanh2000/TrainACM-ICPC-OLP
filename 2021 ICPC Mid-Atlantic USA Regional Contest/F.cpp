#include<bits/stdc++.h>

using namespace std;

#define task "sol"
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define zs(v) ((int)(v).size())
#define BIT(x, i) (((x) >> (i)) & 1)
#define CNTBIT __builtin_popcountll
#define ALL(v) (v).begin(),(v).end()
#define endl '\n'

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;

const int dx[4]={-1, 0, 1, 0}, dy[4]={0, 1, 0, -1};
const int dxx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, dyy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const ll mod = 1000000007; /// 998244353
const ll base = 331;

ll dp[25][25];
string s;
int n;

bool isClose(char c) {
    return (c == ')' || c == '>' || c == ']' || c == '}');
}
bool isOpen(char c) {
    return (c == '(' || c == '<' || c == '[' || c == '{');
}
bool check(char x, char y) {
    if (x == '(' && y == ')') {
        return 1;
    }
    if (x == '[' && y == ']') {
        return 1;
    }
    if (x == '{' && y == '}') {
        return 1;
    }
    if (x == '<' && y == '>') {
        return 1;
    }
    return 0;
}

int getMult(char x, char y) {
    if (x == y && x == '?') return 4;
    if (check(x, y)) return 1;
    if (isOpen(x) && y == '?') return 1;
    if (x == '?' && isClose(y)) return 1;
    return 0;
}

void solve() {
    cin >> s;
    n = s.size();
    if (!n) {
        cout << 1;
        return;
    }
    s = ' ' + s;
    memset(dp, 0ll, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i][i - 1] = 1;
    }
    for (int len = 2; len <= n; len += 2) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; k += 2) {
                dp[i][j] += dp[i + 1][k - 1] * getMult(s[i], s[k]) * dp[k + 1][j];
                // dp[i][j] += dp[i][k] * getMult(s[k + 1], s[j]) * dp[k + 2][j - 1];
            }
            dp[i][j] += getMult(s[i], s[j]) * dp[i + 1][j - 1];
        }
    }
    cout << dp[1][n];
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
}
