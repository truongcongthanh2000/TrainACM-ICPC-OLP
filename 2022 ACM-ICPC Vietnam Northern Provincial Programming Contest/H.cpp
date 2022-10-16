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
    int Q;
    cin >> Q;

    multiset<int> less, greater;

    auto norm = [&]() {
        while ((int)less.size() > (int)greater.size() + 1) {
            auto it = less.end();
            it--;
            greater.insert(*it);
            less.erase(it);
        }

        while ((int)less.size() < (int)greater.size()) {
            auto it = greater.begin();
            less.insert(*it);
            greater.erase(it);
        }

        while ((int)greater.size() > 0 && *less.rbegin() > *greater.begin()) {
            auto it1 = less.end();
            it1--;

            auto it2 = greater.begin();

            greater.insert(*it1);
            less.insert(*it2);

            less.erase(it1);
            greater.erase(it2);
        }
    };

    while (Q--) {
        string type;
        cin >> type;
        if (type == "IN") {
            int x;
            cin >> x;
            less.insert(x);
        }
        if (type == "OUT") {
            int x;
            cin >> x;
            if (less.find(x) != less.end())
                less.erase(less.find(x));
            else
                greater.erase(greater.find(x));
        }
        if (type == "MEDIAN") {
            if ((int)less.size() == (int)greater.size()) {
                int x = *less.rbegin();
                int y = *greater.begin();
                cout << (x + y) / 2 << ((x + y) % 2 ? ".5" : "") << '\n';
            } else {
                cout << *less.rbegin() << '\n';
            }
        }
        norm();
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
