#include <bits/stdc++.h>

using namespace std;

void rwFile() {
    freopen("INP.inp", "r", stdin);
    freopen("OUT.out", "w", stdout);
}

int toInt(string x) {
    int res = 0;
    for (int i = 0; i < x.size(); i++) {
        res = res * 10 + (x[i] - '0');
    }
    return res;
}

int power(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) res *= x;
    return res;
}

void solve() {
    int t; cin >> t;
    while (t--) {
        string x; cin >> x;
        int n = toInt(x);
        int res = 0;
        int c = 1;
        for (int i = 1; i <= 9; i++) {
            if (n >= power(10, i)) res += 10 * (i - 1) + 9;
            else {
                c = i;
                break;
            }
        }
        int special = 1;
        if (n < 10) {
            cout << n - 1 << '\n';
            continue;
        }
        for (int i = 1; i < x.size(); i++) {
            if (x[i] != '0') special = 0;
        }
        if (special) {
            if (x[0] == '1') {
                cout << res << '\n';
                continue;
            }
            res += (x[0] - '1') + 10 * (c - 1);
            if (x[0] == '2') res--;
            cout << res << '\n';
            continue;
        }
//        int diff = 0;
//        for (int i = 1; i < x.size(); i++) {
//            if (x[i] != '0') diff++;
//        }
        int hasOne = 0;
        for (int i = 1; i < x.size(); i++) {
            if (x[i] == '1') {
                //diff--;
                hasOne = 1;
                break;
            }
        }
//        if (x[0] != '1') diff++;
        //cout << res << ' ';
        string s = "10000000000";
        int used = 0;
        for (int i = 0; i < x.size(); i++) {
            if (x[i] != s[i]) {
                if (x[i] == '1') {
                    if (used == 0) {
                        used = 1;
                        continue;
                    }
                }
                res += (x[i] - '0') + 1;
                if (i == 0 && hasOne == 0) res--;
                if (i == x.size() - 1) res--;
            }
            else {
                if (i == 0) used = 1;
            }
        }
        cout << res << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
   /// rwFile();
    solve();
}
