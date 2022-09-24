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
    vector<string> var(3);
    char op;
    char eq;
    cin >> var[0] >> op >> var[1] >> eq >> var[2];
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            for (int ki = 0; ki < (int)var[i].size(); ki++) {
                for (int kj = 0; kj < (int)var[j].size(); kj++) {
                    if (ki == 0 && kj == 0) continue;
                    vector<string> nvar = var;
                    nvar[i] = var[j].substr(0, kj) + var[i].substr(ki);
                    nvar[j] = var[i].substr(0, ki) + var[j].substr(kj);
                    if (op == '+') {
                        if (std::stoll(nvar[0]) + std::stoll(nvar[1]) == std::stoll(nvar[2])) {
                            cout << nvar[0] << " + " << nvar[1] << " = " << nvar[2];
                            return;
                        }
                    }
                    if (op == '*') {
                        if (std::stoll(nvar[0]) * std::stoll(nvar[1]) == std::stoll(nvar[2])) {
                            cout << nvar[0] << " * " << nvar[1] << " = " << nvar[2];
                            return;
                        }
                    }
                }
            }
        }
    }
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
