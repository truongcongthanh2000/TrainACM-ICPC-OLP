#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const {
        return make_pair(l / BLOCK, r) <
               make_pair(other.l / BLOCK, other.r);
    }
};

void sol2() {  // % 2 == 0
    // To count number of s[i]..s[j] % 2 == 0 in range [L, R]
    // We just need to care s(j) % 2 == 0, so that all i from range [L, j] will make s[i]..s[j] % 2 == 0
    // The problem is calculate sum(i - L + 1) for all i in range [L, R]
    // We can transform the sum(i - L + 1) to sum - count * (L - 1)
    //  count: number of position i in range [L, R]
    //  sum: sum of position i in range [L, R]
    // Use prefix sum to calculate count and sum in O(1)
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> sum(n + 1, 0);
    vector<int> count(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        count[i] = count[i - 1];
        sum[i] = sum[i - 1];
        if ((s[i - 1] - '0') % 2 == 0) {
            sum[i] += i;
            count[i]++;
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int L, R;
        cin >> L >> R;
        int d = count[R] - count[L - 1];
        long long s = sum[R] - sum[L - 1];
        cout << s - 1LL * d * (L - 1) << '\n';
    }
}

void sol5() { // % 5 == 0
    // Just same as solution % 2 == 0, just change condition i to s[i] = 0 or s[i] = 5 instead
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> sum(n + 1, 0);
    vector<int> count(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        count[i] = count[i - 1];
        sum[i] = sum[i - 1];
        if ((s[i - 1] == '5') || (s[i - 1] == '0')) {
            sum[i] += i;
            count[i]++;
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int L, R;
        cin >> L >> R;
        int d = count[R] - count[L - 1];
        long long s = sum[R] - sum[L - 1];
        cout << s - 1LL * d * (L - 1) << '\n';
    }
}
void sol() {
    // assume suffix[i] = s[i]...s[n] = s[i] * 10^(n - i) + s[i + 1] * 10^(n - i - 1) + ... + s[n]
    //  -> s[i]..s[j] = suffix[i] - suffix[j + 1] * 10^(j - i + 1)
    // if s[i]..s[j] % p == 0 -> suffix[i] == suffix[j + 1] * 10^(j - i + 1) (mod p) (*)
    /*
        If p = 2, p = 5: We can do a special problem
        If p != 2 and p != 5, so for (*) -> suffix[i] == suffix[j + 1] (mod p)
            So the problem is just count number of pair (i, j) in range [L, R + 1] that suffix(i) = suffix(j)
            We have many ways to count, in this code I will use Mo's algorithm with complexity is O((N + Q)sqrt(N))
    */
    int p;
    cin >> p;
    if (p == 2) {
        sol2();
        return;
    }
    if (p == 5) {
        sol5();
        return;
    }
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n + 1, 0);
    int pw10 = 1;
    for (int i = n - 1; i >= 0; i--) {
        a[i] = 1LL * (s[i] - '0') * pw10 % p;
        a[i] = (a[i] + a[i + 1]) % p;
        pw10 = 1LL * pw10 * 10 % p;
    }
    vector<int> list_value;
    for (int i = 0; i <= n; i++) {
        list_value.push_back(a[i]);
    }
    sort(list_value.begin(), list_value.end());
    list_value.resize(unique(list_value.begin(), list_value.end()) - list_value.begin());
    for (int i = 0; i <= n; i++) {
        a[i] = lower_bound(list_value.begin(), list_value.end(), a[i]) - list_value.begin();
    }
    int Q;
    cin >> Q;
    vector<Query> queries(Q);
    for (int i = 0; i < Q; i++) {
        // calc number of pair (i, j) in range [L, R + 1] that a(i) = a(j)
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end());

    vector<int> count(list_value.size());
    long long ans = 0;
    auto add = [&](int idx) {
        int x = a[idx];
        ans += count[x];
        count[x]++;
    };
    auto remove = [&](int idx) {
        int x = a[idx];
        count[x]--;
        ans -= count[x];
    };
    vector<long long> answers(Q);
    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = ans;
    }
    for (int i = 0; i < Q; i++) cout << answers[i] << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
