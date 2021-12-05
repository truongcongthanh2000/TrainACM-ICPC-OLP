#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

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
    multiset<int> odd, even;
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
        if (x % 2 == 0) even.insert(x);
        else odd.insert(x);
    }
    string s;
    cin >> s;
    for (char c : s) {
        if (c == '0') {
            multiset<int> newE;
            for (int x : even) {
                sum -= x / 2;
                int y = x / 2;
                if (y % 2 == 0) newE.insert(y);
                else odd.insert(y);
            }
            swap(newE, even);
        }
        else {
            for (int x : odd) {
                sum--;
                int y = x - 1;
                if (y > 0) {
                    even.insert(y);
                }
            }
            odd.clear();
        }
        cout << sum << '\n';
    }
}

void solve() {
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
