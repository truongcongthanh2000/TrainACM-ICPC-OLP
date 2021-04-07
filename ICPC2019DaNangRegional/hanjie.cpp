#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

vector <int> a[10], b[10];
vector <int> S[10], T[10];

int vl[30][30];
int r, c;
int Res = 0;
void Check() {
    bool Ok = true;
//    for (int i = 0; i < r; i++) {
//        for (int j = 0; j < c; j++) cout << vl[i][j] << ' ';
//        cout << endl;
//    }
    for (int i = 0; i < c; i++) {
        vector <int> vc;
        for (int j = 0; j < r; ) {
            int k = j;
            while (k < r && vl[k][i] == vl[j][i]) k++;
            if (vl[j][i] == 1) vc.push_back(k - j);
            j = k;
        }
        if (vc != b[i]) {
            Ok = false;
            break;
        }
    }
//    if (Ok) {
//        for (int i = 0; i < r; i++) {
//            for (int j = 0; j < c; j++) cout << vl[i][j] << ' ';
//            cout << endl;
//        }
//    }
    Res += Ok;
}
void Vet(int x, int y, int id) {
    if (x == r) {
        Check();
        return;
    }
    ///cout << x << " " << y << " " << id << '\n';
    if (id == (int)a[x].size()) {
        if (y > c + 1) return;
        Vet(x + 1, 0, 0);
        return;
    }
    int Tong = S[x][(int)a[x].size() - 1] - (id == 0 ? 0 : S[x][id - 1]);
    int Len = (int)a[x].size() - id;
    ///cout << Tong << " " << Len << " " << y << " " << y + Tong + (Len - 1) - 1 << '\n';
    if (y + Tong - (Len - 1) - 1 >= c) return;
    int Lm = (Tong - a[x][id]) + max(0, Len - 2);
    for (int next_Y = y, lm_Y = c - Lm; next_Y < lm_Y; next_Y++) {
        for (int p = next_Y; p < next_Y + a[x][id]; p++) {
            vl[x][p] = 1;
//            if (x == 0) T[p].push_back(1);
        }
        Vet(x, next_Y + a[x][id] + 1, id + 1);
        for (int p = next_Y; p < next_Y + a[x][id]; p++) {
            vl[x][p] = 0;
//            int x = T[p][(int)T[p].size() - 1];
//            x -= 1;
////            if (x > 0) T[p][(int)T[p].size() - 1] -= 1;
////            else T[p].pop_back();
        }
    }
}
void solve() {
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        S[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
            S[i][j] = j == 0 ? a[i][j] : S[i][j - 1] + a[i][j];
        }
    }
    for (int i = 0; i < c; i++) {
        int k;
        cin >> k;
        b[i].resize(k);
        for (int j = 0; j < k; j++) cin >> b[i][j];
    }
    Vet(0, 0, 0);
    cout << Res;
}
int main()
{
    ios_base::sync_with_stdio(1);
    cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
    return 0;
}

