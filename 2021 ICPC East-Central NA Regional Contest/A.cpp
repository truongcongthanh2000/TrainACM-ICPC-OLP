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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
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
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, INF);
    iota(dp.begin(), dp.end(), 0);

    auto divisors = [&](int n) -> vector<int> {
        vector<int> ans;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                ans.push_back(i);
                // if (i * i != n) ans.push_back(n / i); no need to push
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    };

    for (int i = 1; i <= n; i++) {
        string ni = std::to_string(i);
        for (int j = 1; j < (int)ni.size(); j++) {
            if (ni[j] != '0') {
                int prev_t = std::stoi(ni.substr(0, j));
                int sub_t = std::stoi(ni.substr(j));
                dp[i] = min(dp[i], dp[prev_t] + dp[sub_t]);
            }
        }

        auto divs = divisors(i);
        for (int t : divs) {
            dp[i] = min(dp[i], dp[t] + dp[i / t]);
        }

        for (int j = 1; j <= i - 1; j++) {
            dp[i] = min(dp[i], dp[j] + dp[i - j]);
        }
    }

    cout << dp[n];
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

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
