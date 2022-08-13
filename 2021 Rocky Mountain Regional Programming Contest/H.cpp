#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template<typename T>
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
    std::copy(std::istream_iterator<T>(is), std::istream_iterator<T>(), std::back_inserter(v));
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
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    auto primes = [](long long n) -> vector<long long> {
        vector<long long> ans;
        int x = sqrt(n);
        for (int i = 2; i <= x && i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    ans.push_back(i);
                    n /= i;
                }
            }
        }
        if (n > 1) ans.push_back(n);
        return ans;
    };
    auto isPrime = [](long long n) -> bool {
        for (int i = 2, x = sqrt(n); i <= x; i++) {
            if (n % i == 0) return false;
        }
        return true;
    };
    long long a, b;
    cin >> a >> b;
    if (isPrime(a) && isPrime(b) && a != b) {
        cout << "full credit";
    } else {
        auto va = primes(a);
        auto vb = primes(b);
        for (auto x : vb) va.push_back(x);
        sort(va.begin(), va.end());
        for (int i = 0; i < (int)va.size() - 1; i++) {
            if (va[i] == va[i + 1]) {
                cout << "no credit";
                return;
            }
        }
        cout << "partial credit";
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
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
