#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 998244353;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

struct Number {
    int len, val;
    Number() {
        len = 0;
        val = 0;
    }
    Number(int _val) {
        len = 1;
        val = _val;
    }
};

int pw[maxN];
Number Merge(Number a, Number b) {
    Number res;
    res.len = a.len + b.len;
    res.val = (1LL * a.val * pw[b.len] % MOD + b.val) % MOD;
    return res;
}

struct Node {
    Number first, last;
    char sign;
    int val; //không tính first, last
    Node() {
        first = last = Number();
        sign = '?';
        val = 0;
    }
    Node(Number _first, Number _last, char _sign, int _val) {
        first = _first;
        last = _last;
        sign = _sign;
        val = _val;
    }
};

Node IT[maxN * 4];

Node Merge(Node a, Node b) {
    if (a.sign == '?') return b;
    if (b.sign == '?') return a;
    Node res;
    if (a.sign == 'N') res.first = Merge(a.first, b.first);
    else res.first = a.first;
    if (b.sign == 'N') {
        assert(b.first.val == b.last.val);
        res.last = Merge(a.last, b.last);
    }
    else res.last = b.last;
    if (b.sign == 'N') res.sign = a.sign;
    else res.sign = b.sign;
    res.val = (a.val + b.val) % MOD;
    if (a.sign == '+' && b.sign != 'N') {
        Number mid = Merge(a.last, b.first);
        res.val = (res.val + mid.val) % MOD;
    }
    else {
        if (a.sign == '-' && b.sign != 'N') {
            Number mid = Merge(a.last, b.first);
            res.val = (res.val - mid.val + MOD) % MOD;
        }
    }
    return res;
}

Node get(char c) {
    if (c == '+' || c == '-') return Node(Number(), Number(), c, 0);
    int x = c - '0';
    return Node(Number(x), Number(x), 'N', 0);
}
void update(int i, int L, int R, int u, char c) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[i] = get(c);
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, c);
    update(i << 1 | 1, mid + 1, R, u, c);
    IT[i] = Merge(IT[i << 1], IT[i << 1 | 1]);
}

Node get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return Node();
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    Node Left = get(i << 1, L, mid, u, v);
    Node Right = get(i << 1 | 1, mid + 1, R, u, v);
    return Merge(Left, Right);
}
ostream& operator << (ostream &os, Number a) {
    os << a.val << " " << a.len << '\n';
    return os;
}
ostream& operator << (ostream &os, Node a) {
    os << a.first << a.last << a.sign << " " << a.val << '\n';
    return os;
}
void sol() {
    pw[0] = 1;
    for (int i = 1; i < maxN; i++) pw[i] = 1LL * pw[i - 1] * 10 % MOD;
    string s;
    cin >> s;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) update(1, 0, n - 1, i, s[i]);
    int Q;
    cin >> Q;
    while (Q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int L, R;
            cin >> L >> R;
            L--; R--;
            Node res = get(1, 0, n - 1, L, R);
            if (res.sign == 'N') {
                assert(res.first.val == res.last.val);
                cout << res.first.val << '\n';
                continue;
            }
            int ans = res.first.val;
            ans = (ans + res.val) % MOD;
            if (res.sign == '+') ans = (ans + res.last.val) % MOD;
            else ans = (ans - res.last.val + MOD) % MOD;
            cout << ans << '\n';
        }
        else {
            int idx;
            char c;
            cin >> idx >> c;
            idx--;
            s[idx] = c;
            update(1, 0, n - 1, idx, c);
        }
    }
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
