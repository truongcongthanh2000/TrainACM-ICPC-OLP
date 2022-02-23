#include<bits/stdc++.h>

using namespace std;

void ioFiles() {
    #ifdef THEMIS
        freopen("solve.txt", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

struct point {
    int x, y;
    point(){};
};

void dif(point &a, point b) {
    a.x -= b.x;
    a.y -= b.y;
}
bool Line(point a, point b, point c) {
    dif(b, a);
    dif(c, a);
    return 1LL * b.x * c.y == 1LL * b.y * c.x;
}

long long dist(point a, point b) {
    long long x = abs(a.x - b.x);
    long long y = abs(a.y - b.y);
    return x * x + y * y;
}

int type(vector<long long> a) {
    if (a[0] == a[1] || a[1] == a[2]) return 2;
    return 1;
}
void solve() {
    int n;
    cin >> n;
    vector<point> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    long long ans = 0;
    {
        map<vector<long long>, int> m;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (Line(a[i], a[j], a[k])) continue;
                    vector<long long> vdist = {dist(a[i], a[j]), dist(a[i], a[k]), dist(a[j], a[k])};
                    sort(vdist.begin(), vdist.end());
                    m[vdist]++;
                }
            }
        }
        for (auto it : m) {
            int n = it.second;
            ans += 1LL * n * (n - 1) * type(it.first);
        }
    }
    {
        for (int i = 0; i < n; i++) {
            map<vector<long long>, int> m;
            for (int j = 0; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (Line(a[i], a[j], a[k])) continue;
                    vector<long long> vdist = {dist(a[i], a[j]), dist(a[i], a[k]), dist(a[j], a[k])};
                    sort(vdist.begin(), vdist.end());
                    m[vdist]++;
                }
            }
            for (auto it : m) {
                int n = it.second;
                ans -= 1LL * n * (n - 1) * type(it.first);
            }
        }
    }
    {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                map<vector<long long>, int> m;
                for (int k = 0; k < n; k++) {
                    if (Line(a[i], a[j], a[k])) continue;
                    vector<long long> vdist = {dist(a[i], a[j]), dist(a[i], a[k]), dist(a[j], a[k])};
                    sort(vdist.begin(), vdist.end());
                    m[vdist]++;
                }
                for (auto it : m) {
                    int n = it.second;
                    ans += 1LL * n * (n - 1) * type(it.first);
                }
            }
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ioFiles();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
