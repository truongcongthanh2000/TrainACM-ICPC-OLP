#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}

bool Check(string s, string t) { ///s < t = true
    int n = (int)s.size();
    int m = (int)t.size();
    for (int i = 0; i < min(n, m); i++) {
        if (s[i] != t[i]) {
            if (s[i] < t[i]) return true;
            if (s[i] > t[i]) return false;
        }
    }
    if (n < m) return true;
    return false;
}
bool Check(string s) {
    ///cerr << s << '\n';
    string TMP = "";
    int n = (int)s.size();
    for (int i = 0; i < n - 1; i++) {
        assert(s != "");
        TMP += s[0];
        s.erase(s.begin());
        ///cerr << "OK" << '\n';
        if (Check(TMP, s) == false) return false;
    }
    return true;
}
void solve() {
    int Test;
    cin >> Test;
    while (Test--) {
        string s;
        cin >> s;
        int idx = -1;
        int n = (int)s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') idx = i;
        }
        if (idx == -1) {
            cout << "" << '\n';
            continue;
        }
        for (int i = idx; i < n; i++) {
            assert(i < (int)s.size());
            s[i] = '1';
        }
        ///cerr << S << '\n';
        ///cerr << s << '\n';
        if (Check(s) == false) {
            cout << "" << '\n';
            continue;
        }
        for (int i = idx + 1; i < n; i++) {
            s[i] = '0';
            if (Check(s) == false) s[i] = '1';
        }
        cout << s << '\n';
    }
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
