#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}
void solve() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        string t;
        int k;
        cin >> s >> t >> k;
        int H1 = (s[0] - '0') * 10 + (s[1] - '0');
        int M1 = (s[3] - '0') * 10 + (s[4] - '0');
        int H2 = (t[0] - '0') * 10 + (t[1] - '0');
        int M2 = (t[3] - '0') * 10 + (t[4] - '0');
        int T1 = H1 * 60 + M1;
        int T2 = H2 * 60 + M2;
        ///cout << T1 << " " << T2 << '\n';
        int Res = 0;
        if (k == 0) {
            for (int i = 0; i < 24; i++) {
                int x = i % 12;
                if (x == 11) continue;
                int H = i;
                int M = 60 * x / 11;
                int Thua = 60 * x % 11;
                int vl = H * 60 + M;
                if (vl == T2) {
                    if (Thua == 0) Res += 1;
                }
                else {
                    if (vl >= T1 && vl <= T2) Res += 1;
                }
            }
        }
        if (k == 90) {
            for (int i = 0; i < 24; i++) {
                int x = i % 12;
                ///if (x == 11) continue;
                if (x <= 2) {
                    int TS = 2 * (30 * x + 90);
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        ///long double value = 1.0 * H * 60.0 + 1.0 * M + 1.0 * Thua / (11.0);
                        ///cout << i << " " << H << " " << M << " " << Thua << " " << value << '\n';
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                    TS = 2 * (30 * x + 270);
                    ///cout << TS << '\n';
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                }
                if (x >= 3 && x <= 8) {
                    int TS = 2 * (30 * x + 90);
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        ///long double value = 1.0 * H * 60.0 + 1.0 * M + 1.0 * Thua / (11.0);
                        ///cout << i << " " << H << " " << M << " " << Thua << " " << value << '\n';
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                    TS = 2 * (30 * x - 90);
                    ///cout << TS << '\n';
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                }
                if (x > 8) {
                    int TS = 2 * (30 * x - 90);
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        ///long double value = 1.0 * H * 60.0 + 1.0 * M + 1.0 * Thua / (11.0);
                        ///cout << i << " " << H << " " << M << " " << Thua << " " << value << '\n';
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                    TS = 2 * (30 * x - 270);
                    ///cout << TS << '\n';
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                }

            }
        }
        if (k == 180) {
            for (int i = 0; i < 24; i++) {
                int x = i % 12;
                if (x <= 5) {
                    int TS = 2 * (30 * x + 180);
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                }
                else {
                    int TS = 2 * (30 * x - 180);
                    ///cout << TS << '\n';
                    if (TS / 11 < 60) {
                        int H = i;
                        int M = TS / 11 % 60;
                        int Thua = TS % 11;
                        int vl = H * 60 + M;
                        if (vl == T2) {
                            if (Thua == 0) Res += 1;
                        }
                        else {
                            if (vl >= T1 && vl <= T2) Res += 1;
                        }
                    }
                }
            }
        }
        cout << Res << '\n';
    }
}
int main()
{
    ios_base::sync_with_stdio(1);
    cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
    return 0;
}

