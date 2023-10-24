#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

void sol() {
    auto get_0 = [&](vector<int> row) {
        if (row[0] == 0) return 0;
        if (row[1] == 0) return 1;
        return 2;
    };
    int n, k;
    cin >> n >> k;
    map<int, map<int, map<int, int>>> m;
    vector<vector<int>> a;
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if (m[x][y][z]) {
            continue;
        }
        m[x][y][z] = 1;
        vector<int> add = {x, y, z};
        a.push_back(add);
        ans += n;
    }
    map<int, map<int, map<int, int>>> c;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            for (int k = 0; k < 3; k++) {
                if (a[i][k] == a[j][k] && a[i][k] > 0) {
                    if (get_0(a[i]) != get_0(a[j])) {
                        c[max(a[i][0], a[j][0])][max(a[i][1], a[j][1])][max(a[i][2], a[j][2])]++;
                        break;
                    }
                }
            }
        }
    }
    for (auto it = c.begin(); it != c.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            for (auto it3 : it2->second) {
                int sum = it3.second;
                int n = sqrt(sum * 2);
                while (n * (n - 1) / 2 < sum) n++;
                while (n * (n - 1) / 2 > sum) n--;
                assert(n * (n - 1) / 2 == sum);
                ans -= n - 1;
            }
        }
    }
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
