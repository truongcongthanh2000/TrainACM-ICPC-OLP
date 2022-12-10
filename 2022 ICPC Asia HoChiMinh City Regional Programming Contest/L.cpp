#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

void sol() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<int> d(26, 0);
    for (char c : s) d[c - 'a']++;

    int remain = (int)s.size();
    auto check = [&]() {
        int mx = *max_element(d.begin(), d.end());
        return mx <= 1LL * (remain - mx + 1) * (k - 1);
    };

    if (!check()) {
        cout << "OH NO!" << '\n';
        return;
    }

    vector<int> last(26, 0);
    for (int i = 0; i < (int)s.size(); i++) {
        for (int c = 0; c < 26; c++) {
            if (!d[c]) continue;
            if (last[c] == k - 1) {
                continue;
            }
            d[c]--;
            remain--;
            if (check()) {
                cout << char(c + 'a');
                last[c]++;
                for (int j = 0; j < 26; j++) {
                    if (j != c) last[j] = 0;
                }
                break;
            }
            remain++;
            d[c]++;
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
    cin >> t;
    while (t--) sol();
}
