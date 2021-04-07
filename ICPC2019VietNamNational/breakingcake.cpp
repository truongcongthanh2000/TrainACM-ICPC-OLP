#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

struct Node {
    int x, y, z;
    int id;
    Node(){};
    Node(int _x, int _y, int _z, int _id) {
        x = _x;
        y = _y;
        z = _z;
        id = _id;
    }
};
struct Line {
    Node A, B;
    int id;
    Line(){};
    Line(Node _A, Node _B, int _id) {
        A = _A;
        B = _B;
        id = _id;
    }
};
void Print(Node A) {
    cout << A.x << " " << A.y << " " << A.z;
}
Node a[maxN];
int m;
int DA, DB, DC;
vector <Line> Get(int Z) {
    vector <Node> A;
    for (int i = 0; i < m; i++) {
        if (a[i].z == Z) A.push_back(a[i]);
    }
    sort(A.begin(), A.end(), [](Node a, Node b) {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    });
    vector <Line> Res;
    int n = (int)A.size();
    int L = 1;
    for (int i = 0; i < n; ){
        ///cerr << i << ' ';
        int j = i;
        while (j < n && A[i].x == A[j].x) j++;
        ///cerr << j << '\n';
        int R = 1;
        for (int k = i; k < j; k++) {
            if (k == j - 1)
                Res.push_back(Line(Node(L, R, 0, -1), Node(A[k].x, DB, -1, -1), A[k].id));
            else Res.push_back(Line(Node(L, R, 0, -1), Node(A[k].x, A[k].y, -1, -1), A[k].id));
            R = A[k].y + 1;
        }
        L = A[i].x + 1;
        i = j;
        ///cerr << i << " " << j << '\n';
    }
    int x = A[(int)A.size() - 1].x;
    for (int i = 0; i < n; i++) {
        if (A[i].x == x) {
            Res[i].B.x = DA;
        }
    }
    return Res;
}
void solve() {
    while (true) {
        cin >> DA;
        if (DA == -1) break;
        cin >> DB >> DC;
        cin >> m;
        vector <int> Z;
        for (int i = 0; i < m; i++) {
            cin >> a[i].x >> a[i].y >> a[i].z;
            a[i].id = i;
            Z.push_back(a[i].z);
        }
        sort(Z.begin(), Z.end());
        Z.resize(unique(Z.begin(), Z.end()) - Z.begin());
        int L = 1;
        Line Res[m];
        for (int i = 0; i < (int)Z.size(); i++) {
            vector <Line> Value = Get(Z[i]);
            for (Line x : Value) {
                Res[x.id] = x;
                if (i == (int)Z.size() - 1) {
                    Res[x.id].A.z = L;
                    Res[x.id].B.z = DC;
                }
                else {
                    Res[x.id].A.z = L;
                    Res[x.id].B.z = Z[i];
                }
            }
            L = Z[i] + 1;
        }
        cout << "YES" << '\n';
        for (int i = 0; i < m; i++) {
            Print(Res[i].A);
            cout << ' ';
            Print(Res[i].B);
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ///doc();
    solve();
}
