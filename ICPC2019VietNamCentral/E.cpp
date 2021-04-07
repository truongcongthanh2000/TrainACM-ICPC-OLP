#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}
const int maxN = 5e4 + 100;
int IT[maxN * 4];
void up(int i, int L, int R, int u, int val) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[i] += val;
        return;
    }
    int mid = (L + R) >> 1;
    up(i << 1, L, mid, u, val);
    up(i << 1 | 1, mid + 1, R, u, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
}
int Get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    int Left = Get(i << 1, L, mid, u, v);
    int Right = Get(i << 1 | 1, mid + 1, R, u, v);
    return Left + Right;
}
#define BLOCK 251
struct Query {
    int L, R, x, y, id;
    Query(){};
};
bool cmp(Query A, Query B) {
    if ((A.x / BLOCK) != (B.x / BLOCK))
        return (A.x / BLOCK) < (B.x / BLOCK);
    return A.y < B.y;
}
int cnt[maxN], a[maxN];
int n;
void add(int index)
{
    int val = cnt[a[index]];
    if (val) up(1, 1, n, val, -1);
    cnt[a[index]]++;
    up(1, 1, n, val + 1, 1);
}

void remove(int index)
{
    int val = cnt[a[index]];
    up(1, 1, n, val, -1);
    cnt[a[index]]--;
    if (val - 1 > 0) up(1, 1, n, val - 1, 1);
}
void solve() {
    cin >> n;
    vector <int> B;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        B.push_back(a[i]);
    }
    sort(B.begin(), B.end());
    B.resize(unique(B.begin(), B.end()) - B.begin());
    for (int i = 0; i < n; i++)
        a[i] = lower_bound(B.begin(), B.end(), a[i]) - B.begin();
    int Q;
    cin >> Q;
    Query q[Q];
    int Res[Q];
    for (int i = 0; i < Q; i++) {
        cin >> q[i].x >> q[i].y >> q[i].L >> q[i].R;
        q[i].id = i;
        q[i].x--;
        q[i].y--;
    }
    sort(q, q + Q, cmp);
    int cl=0,cr=0;
    for (int i = 0; i < Q; i++)
    {
        int left=q[i].x,right=q[i].y;
        cerr << left << " " << right << '\n';
        while(cl<left) remove(cl),cl++;
        while(cl>left) add(cl-1),cl--;
        while(cr<=right) add(cr),cr++;
        while(cr>(right+1)) remove(cr-1),cr--;
        Res[q[i].id] = Get(1, 1, n, q[i].L, q[i].R);
    }
    for (int i = 0; i < Q; i++) cout << Res[i] << '\n';
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
