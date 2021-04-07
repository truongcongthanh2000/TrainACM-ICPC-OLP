#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

int SL = 0;
typedef pair<int, int> i2;
int M[2005][2005];
vector <i2> Q[maxN];
vector<int> Ans[maxN];
vector<int> Res[maxN];
vector <int> Ques[maxN];
int id = 0;
void Ask(int L, int R, int Deg, bool Question) {
    if (Question) {
        for (int i = L; i <= R; i++) Ques[Deg].push_back(i);
    }
    if (L == R) return;
    int mid = (L + R) >> 1;
    Ask(L, mid, Deg + 1, true);
    Ask(mid + 1, R, Deg + 1, false);
}
void Ask(int L, int R, int Deg) {
    Q[Deg].push_back(i2(L, R));
    M[L][R] = id++;
    if (L == R) return;
    int mid = (L + R) >> 1;
    Ask(L, mid, Deg + 1);
    Ask(mid + 1, R, Deg + 1);
}
int D1[maxN], D2[maxN], T[maxN];
vector <int> KQ;
void Get(int L, int R, int Deg) {
    if (L == R) {
        int id = M[L][R];
        KQ.push_back(Res[id][0]);
        return;
    }
    ///memset(D1, 0, sizeof(D1));
    memset(D2, 0, sizeof(D2));
    int mid = (L + R) >> 1;
    ///cout << "Deg :" << Deg << '\n';
    for (int x : Ans[Deg + 1]) {
        D2[x] = 1;
        ///cout << x << ' ';
    }
    ///cout << endl;
    int idRight = M[mid + 1][R];
    int idLeft = M[L][mid];
    for (int x : Res[M[L][R]]) {
        if (D2[x] == 0) {
            Res[idRight].push_back(x);
        }
        if (D2[x] == 1) {
            Res[idLeft].push_back(x);
        }
    }
    Get(L, mid, Deg + 1);
    Get(mid + 1, R, Deg + 1);
}
void solve() {
    int n;
    cin >> n;
    Ask(1, n, 0, true);
    Ask(1, n, 0);
    int lm = 0;
    for (int i = 0; i < maxN; i++) {
        if ((int)Q[i].size() != 0) lm = i;
    }
    for (int i = lm; i >= 0; i--) {
        while ((int)Ques[i].size() == 0) continue;
        cout << "ASK " << (int)Ques[i].size() << " ";
        cout << Ques[i][0];
        for (int id = 1; id < (int)Ques[i].size(); id++) {
            cout << " " << Ques[i][id];
        }
        cout << endl;
        vector <int> A;
        for (int id = 0; id < (int)Ques[i].size(); id++) {
            int x;
            cin >> x;
            A.push_back(x);
        }
        Ans[i] = A;
    }
    Res[0] = Ans[0];
    Get(1, n, 0);
//    for (int x : Res[0]) cout << x << ' ';
//    cout << endl;
    int VL[maxN];
    while ((int)KQ.size() != n) continue;
    for (int i = 0; i < n; i++) VL[KQ[i]] = i + 1;
    cout << "ANSWER" << " ";
    cout << VL[1];
    for (int i = 2; i <= n; i++) cout << " " << VL[i];
    cout << endl;
    ///cout << lm << '\n';
}
int main()
{
    ios_base::sync_with_stdio(1);
    cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
    return 0;
}


