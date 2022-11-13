#include <bits/stdc++.h>

using namespace std;

void open_file() {
#ifdef THEMIS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif  // THEMIS
}

#define ull unsigned long long
ull power_mod(ull a, ull d, ull n) {
    ull ans = 1;
    a %= n;
    for (; d; d >= 1, a = a * a % n) {
        if (d & 1) {
            ans = ans * a % n;
        }
    }
    return ans;
}
bool check_composite(long long n, long long a, long long d, int s) {
}

struct query {
    int L, R, d, id;
    query(){};
    query(int _L, int _R, int _d, int _id) {
        L = _L;
        R = _R;
        d = _d;
        id = _id;
    }

    bool operator<(const query &other) {
        return d > other.d;
    }
};

struct BIT {
    vector<long long> fw;
    int n;
    void init(int _n) {
        n = _n;
        fw.assign(n + 5, 0);
    }
    void update(int i, int val) {
        for (; i <= n; i += i & -i) {
            fw[i] += val;
        }
    }
    long long get(int i) {
        long long ans = 0;
        for (; i; i -= i & -i) {
            ans += fw[i];
        }
        return ans;
    }
    long long get(int l, int r) {
        if (l > r) {
            return 0;
        }
        return get(r) - get(l - 1);
    }
};
void sol() {
    int n, Q;
    cin >> n >> Q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    a.push_back(1);

    vector<vector<int> > rmq(n + 1, vector<int>(20, 0));
    for (int i = 0; i < n + 1; i++) rmq[i][0] = a[i];

    for (int j = 1; j < 20; j++) {
        for (int i = 0; i + (1 << j) - 1 < n + 1; i++) {
            int ni = i + (1 << (j - 1));
            rmq[i][j] = __gcd(rmq[i][j - 1], rmq[ni][j - 1]);
        }
    }

    auto get_gcd = [&](int L, int R) {
        int k = (int)log2(R - L + 1);
        return __gcd(rmq[L][k], rmq[R - (1 << k) + 1][k]);
    };

    vector<vector<pair<int, int> > > jump(n);
    for (int i = 0; i < n; i++) {
        int j = i;
        int x = a[i];
        while (x > 1) {
            jump[i].push_back({j, get_gcd(i, j)});
            int L = j, R = n, nj = L;
            while (L <= R) {
                int mid = (L + R) >> 1;
                if (get_gcd(i, mid) != x) {
                    nj = mid;
                    R = mid - 1;
                } else {
                    L = mid + 1;
                }
            }
            j = nj;
            x = get_gcd(i, j);
        }
        jump[i].push_back({j, get_gcd(i, j)});
    }

    vector<int> cur_p(n, 0);

    vector<int> r(n);
    BIT bit;
    bit.init(n);

    for (int i = 0; i < n; i++) {
        r[i] = i;
        bit.update(i + 1, r[i]);
    }

    vector<query> q(Q);
    for (int i = 0; i < Q; i++) {
        cin >> q[i].L >> q[i].R >> q[i].d;
        q[i].L--;
        q[i].R--;
        q[i].id = i;
    }

    sort(q.begin(), q.end());

    set<pair<int, int> > S;
    for (int i = 0; i < n; i++) {
        S.insert({a[i], i});
    }

    vector<long long> ans(Q);
    for (query b : q) {
        int d = b.d;
        while (1) {
            auto it = S.end();
            it--;
            if (it->first <= d) break;
            int gcd = it->first, i = it->second;
            while (jump[i][cur_p[i]].second > d) {
                cur_p[i]++;
            }
            S.erase(it);
            bit.update(i + 1, -r[i]);
            r[i] = jump[i][cur_p[i]].first;
            bit.update(i + 1, +r[i]);
            S.insert({jump[i][cur_p[i]].second, i});
        }
        int L = b.L, R = b.R, id = b.id;
        int i = lower_bound(r.begin() + L, r.begin() + R + 1, R + 1) - r.begin();
        long long sum = bit.get(L + 1, i);
        ans[id] = 1LL * (R + 1) * (i - L) - sum;
    }

    for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
}
int main() {
    open_file();
    int t = 1;
    // cin >> t;
    while (t--) sol();
}
