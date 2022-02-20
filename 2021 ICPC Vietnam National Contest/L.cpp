#include<bits/stdc++.h>

using namespace std;

void ioFiles() {
    #ifdef THEMIS
        freopen("solve.txt", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > a(n + 1, {0, 0});
    for (int i = 0; i <= n; i++) a[i].second = i;
    vector<int> ans(n * n);
    vector<set<int> > adj(n + 1);
    for (int i = 0; i < n * n; i++) {
        int x;
        cin >> x;
        x--;
        adj[x].insert(i);
        a[x].first += 1;
    }
    set<pair<int, int> > cur;
    for (int i = 0; i <= n; i++) {
        if (a[i].first > 0) {
            cur.insert(a[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        vector<pair<int, int> > a(cur.begin(), cur.end());
        int rm = n;
        int cL = min(rm, a[0].first);
        rm -= cL;
        a[0].first -= cL;
        int cR = min(rm, a[(int)a.size() - 1].first);
        a[(int)a.size() - 1].first -= cR;
        for (int j = 0; j < cL; j++) {
            auto it = adj[a[0].second].begin();
            ans[*it] = i + 1;
            adj[a[0].second].erase(it);
        }
        for (int j = 0; j < cR; j++) {
            auto it = adj[a[(int)a.size() - 1].second].begin();
            ans[*it] = i + 1;
            adj[a[(int)a.size() - 1].second].erase(it);
        }
        cur.clear();
        for (auto it : a) {
            if (it.first > 0) cur.insert(it);
        }
    }
    cout << "YES" << '\n';
    for (int i = 0; i < n * n; i++) cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ioFiles();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
