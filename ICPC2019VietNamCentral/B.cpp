#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}

void solve() {
    int n;
    cin >> n;
    int d[n], t[n];
    int H[n];
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> t[i];
        H[i] = i;
    }
    vector <int> A, B;
    for (int i = 0; i < n; i++) {
        int id = lower_bound(A.begin(), A.end(), d[i]) - A.begin();
        A.push_back(0);
        B.push_back(0);
        int SL = i + 1;
        for (int j = SL - 1; j >= id + 1; j--) {
            A[j] = A[j - 1];
            B[j] = B[j - 1];
        }
        A[id] = d[i];
        B[id] = t[i];
        int Res = 0;
        int T = 0;
        for (int j = 0; j <= i; j++) {
            T += B[j];
            Res = max(Res, max(0, T - A[j]));
        }
        //for (int x : A) cout << x << ' ';
        //cout << '\n';
        cout << Res << '\n';
    }
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
