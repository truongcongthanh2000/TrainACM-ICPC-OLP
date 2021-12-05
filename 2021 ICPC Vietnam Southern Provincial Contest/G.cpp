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
    typedef pair<int, int> i2;
    set<i2> can;
    string s;
    cin >> s;
    int must = 0;
    for (int i = 0, sz = (int)s.size(); i < sz; ) {
        int j = i;
        while (j < sz && s[i] == s[j]) j++;
        if (s[i] == '.') can.insert({j - i, 1});
        i = j;
        must += max(0, (j - i - 1));
    }
    string t;
    cin >> t;

    auto ok = [&](int w) {
        if ((int)can.size() == 0) return false;
        auto it = can.end();
        it--;
        int v = it->first, t = it->second;
        can.erase(it);
        if (v <= 1) return false;
        can.insert({v - (2 + w) + t, 0});
        return true;
    };
    int x = 0, y = 0;
    for (int k = 0; k <= (int)t.size(); k++) {
        if (3 * x + 2 * y - (int)can.size())
    }
    for (int k = 0; k <= (int)t.size(); k++) {
        if ((int)can.size() > 0 && (can.rbegin())->first >= 2) cout << "Y";
        else cout << "N";
        if (k < (int)t.size()) ok(t[k] == 'M' ? 0 : 1);
    }
    cout << '\n';
}

void solve() {
    int T = 1;
    cin >> T;
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
