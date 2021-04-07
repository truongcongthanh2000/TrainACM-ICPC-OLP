#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

void sol(){
    int n, c;
    cin >> n >> c;
    int res = 0;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int m = 0;
        int j = 0;
        while (s[j] != ':'){
            m = m * 10 + s[j] -'0';
            j++;
        }
        j++;
        int ss = 0;
        while(j < s.length()){
            ss = ss * 10 + s[j] - '0';
            j++;
        }
        res += m * 60 + ss;
    }

    res -= c * (n - 1);
    int h, m, ss;
    h = res / 3600;
    res %= 3600;
    m = res / 60;
    ss = res % 60;
    auto p = [&](int h){
        stringstream ss;
        if (h < 10) ss << 0 << h;
        else ss << h;
        return ss.str();
    };
    cout << p(h) << ':' << p(m) << ':' << p(ss);
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
