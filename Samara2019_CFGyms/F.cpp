#include <bits/stdc++.h>

using namespace std;

void doc()
{
    freopen("solve.inp","r",stdin);
    freopen("solve.out","w",stdout);
}
const int N = 3e5 + 10;
struct Node {
    int val, id;
    Node(){};
    Node (int _val, int _id) : val(_val), id(_id) {};
};
Node IT[N * 4 * 2];
Node lazy[N * 4 * 2];
Node Get(Node Left, Node Right) {
    if (Left.val > Right.val) return Left;
    return Right;
}
void cn(int i, int L, int R) {
    if (lazy[i].val == 0) return;
    IT[i] = lazy[i];
    if (L != R) {
        lazy[i << 1] = lazy[i];
        lazy[i << 1 | 1] = lazy[i];
    }
    lazy[i] = Node(0, -1);
}
void update(int i, int L, int R, int u, int v, int val, int id) {
    cn(i, L, R);
    if (L > v || R < u) return;
    if (L >= u && R <= v) {
        lazy[i] = Node(val, id);
        cn(i, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, v, val, id);
    update(i << 1 | 1, mid + 1, R, u, v, val, id);
    IT[i] = Get(IT[i << 1], IT[i << 1 | 1]);
}
Node Get(int i, int L, int R, int u, int v) {
    cn(i, L, R);
    if (L > v || R < u) return Node(0, -1);
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    Node Left = Get(i << 1, L, mid, u, v);
    Node Right = Get(i << 1 | 1, mid + 1, R, u, v);
    return Get(Left, Right);

}
void solve() {
    int n;
    cin >> n;
    vector <int> x;
    int a[n], h[n], pos[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> h[i];
        pos[i] = i;
        x.push_back(a[i]);
        x.push_back(h[i]);
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());
    int m = (int)x.size();
    for (int i = 0; i < m; i++) update(1, 1, m, i, i, 0, -1);
    sort(pos, pos + n, [&](int i, int j){
        if (a[i] != a[j]) return a[i] < a[j];
        return h[i] < h[j];
    });
//    for (int y : x) cout << y << ' ';
//    cout << '\n';
//    for (int i = 0; i < n; i++) cout << a[pos[i]] << " " << h[pos[i]] << '\n';
    int Res = 0;
    int id1 = 0, id2 = 1;
    for (int i = n - 1; i >= 0; i--) {
        int id = pos[i];
        int A = a[id];
        int H = h[id];
        if (i == n - 1) {
            if (H <= a[pos[n - 2]]) {
                int val = A;
                if (val > Res) {
                    id1 = id;
                    id2 = pos[n - 2];
                    Res = val;
                }
            }
        }
        if (i != n - 1 && H <= a[pos[n - 1]]) {
            int val = A;
            if (val > Res) {
                id1 = id;
                id2 = pos[n - 1];
                Res = val;
            }
        }
        int posA = lower_bound(x.begin(), x.end(), A) - x.begin() + 1;
        int posH = lower_bound(x.begin(), x.end(), H) - x.begin() + 1;
        Node valC = Get(1, 1, m, posA, posA);
        if (H <= valC.val) {
            int val = A + valC.val;
            if (val > Res) {
                id1 = id;
                id2 = valC.id;
                Res = val;
            }
        }
        if (H <= A) update(1, 1, m, posH, posA, A, id);
    }
    cout << Res << '\n';
    cout << id1 + 1 << " " << id2 + 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
