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

void solve() {
    int t; cin >> t;
    while (t--) {
        string slot, arr; cin >> slot >> arr;
        multiset<int, greater<int>> odd, even;
        int n = slot.size();
        for (int i = 0; i < n; ++i) {
            if (slot[i] == '.') {
                int id = i;
                while (id < n && slot[id] == '.') id++;
                if (id - i > 1) {
                    if ((id - i) % 2 == 0) even.insert(id - i);
                    else odd.insert(id - i);
                }
                i = id - 1;
            }
        }
        int m = arr.size();
        string res = "";
        if (even.size() || odd.size()) res += 'Y';
        else res += 'N';
        for (int i = 0; i < m; ++i) {
            if (!odd.size() && !even.size()) {
                res += 'N';
                continue;
            }
            if (arr[i] == 'M') {
                if (odd.size()) {
                    auto it = --odd.end();
                    int val = *it;
                    odd.erase(it);
                    if (val - 2 > 1) odd.insert(val - 2);
                }
                else {
                    auto it = --even.end();
                    int val = *it;
                    even.erase(it);
                    if (val - 2 > 1) even.insert(val - 2);
                }
            }
            else {
                if (even.size()) {
                    if (odd.size() && *even.begin() == 2) {
                        int val = *odd.begin();
                        odd.erase(odd.begin());
                        if (val - 3 > 1) even.insert(val - 3);
                    }
                    else {
                        int val = *even.begin();
                        even.erase(even.begin());
                        if (val - 3 > 1) odd.insert(val - 3);
                    }
                }
                else {
                    int val = *odd.begin();
                    odd.erase(odd.begin());
                    if (val - 3 > 1) even.insert(val - 3);
                }
            }
            if (odd.size() || even.size()) res += "Y";
            else res += "N";
        }
        cout << res << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
