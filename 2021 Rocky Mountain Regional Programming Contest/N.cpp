#include<bits/stdc++.h>

using namespace std;

#define task "N"
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
const int N = 1e4 + 5;

int n, k;
string a[N], b[N], c[N];
int cnt[30];
bool cant[N];

void gogo() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
    }
    int ans = 0;
    for (int i = 1; i <= k; ++i) {
        cin >> c[i];
        bool ok = 1;
        for (int j = 1; j <= n; ++j) {
            for (int x = 0; x < 26; ++x) {
                cnt[x] = 0;
                cant[x] = 0;
            }
            for (int x = 0; x < 5; ++x) {
                if (b[j][x] == 'G') {
                    ok &= c[i][x] == a[j][x];
                } else if (b[j][x] == 'Y') {
                    ok &= c[i][x] != a[j][x];
                    cnt[a[j][x] - 'A']++;
                    cant[a[j][x] - 'A'] |= 1;
                }
            }
            // cout << ok << '\n';
            for (int x = 0; x < 5; ++x) {
                if (b[j][x] == 'G') {
                    continue;
                }
                if (b[j][x] == '-' && !cant[a[j][x] - 'A']) {
                    for (int y = 0; y < 5; ++y) {
                        if (b[j][y] == 'G') {
                            continue;
                        }
                        ok &= c[i][y] != a[j][x];
                    }
                }
                cnt[c[i][x] - 'A']--;
            }
            // cout << ok << '\n';
            for (int x = 0; x < 5; ++x) {
                if (cnt[a[j][x] - 'A'] > 0) {
                    ok = 0;
                }
            }
            // cout << j << ' ' << ok << '\n';
        }
        if (ok) {
            cout << c[i] << '\n';
        }
    }
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    gogo();
}








