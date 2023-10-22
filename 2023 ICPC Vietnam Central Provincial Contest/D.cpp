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
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s(n);
    cin >> s;
    vector<vector<int> > position_enemy(n);
    vector<vector<int> > swalls(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'x') {
                position_enemy[i].push_back(j);
            }
        }
        swalls[i][0] = s[i][0] == '#';
        for (int j = 1; j < m; j++) {
            swalls[i][j] = swalls[i][j - 1] + (s[i][j] == '#');
        }
    }

    auto get_walls = [&](int row, int L, int R) {
        if (L == 0) return swalls[row][R];
        return swalls[row][R] - swalls[row][L - 1];
    };
    auto valid = [&](int V) {
        int need_to_place = 0;
        for (int i = 0; i < n; i++) {
            if (position_enemy[i].size() == 0) continue;
            for (int j = 0; j < position_enemy[i].size(); ) {
                need_to_place++;
                int L = position_enemy[i][j];
                int mid = L + V;
                while (s[i][mid] == '#') mid--;
                int R = mid + V;
                int nj = j;
                while (nj < position_enemy[i].size() && position_enemy[i][nj] <= R && get_walls(i, position_enemy[i][j], position_enemy[i][nj]) == 0) {
                    nj++;
                }
                j = nj;
            }
        }
        return need_to_place <= k;
    };
    int L = 0, R = m, ans = -1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (valid(mid)) {
            R = mid - 1;
            ans = mid;
        } else {
            L = mid + 1;
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
