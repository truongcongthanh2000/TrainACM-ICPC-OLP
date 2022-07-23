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

#define ll long long

bool umin(ll &a, ll b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
void sol() {
    ll n;
    cin >> n;
    vector<int> dig;

    vector<bool> vis(10, 0);

    ll temp = n;
    while (temp > 0) {
        dig.push_back(temp % 10);
        temp /= 10;
        vis[dig.back()] = 1;
    }
    reverse(dig.begin(), dig.end());

    ll ans = -1, res = -1, diff = 1e18, diff1 = 1e18;
    int mn = 1e9, mx = 1e9;
    for (int i = 0; i <= 9; ++i)
        if (!vis[i]) 
            mx = i;
    for (int i = 9; i >=0 ; --i) 
        if (!vis[i])
            mn =i;

    if (mx != 1e9) {
        for (int i = dig[0] - 1; i >= 1; --i) if (!vis[i]) {
            ll val = i;
            for (int j = 1; j < dig.size(); ++j)
                val = val * 10 + mx;
            if (umin(diff, n - val)) {
                ans = val;
            }
            // cout << i << ' ' << val << '\n';
        }
        ll val = 0;
        for (int i = 0; i < (int) dig.size() - 1; ++i) {
            val = val * 10 + mx;
        }
        if (umin(diff, n - val)) {
            ans = val;
        }

        for (int i = dig[0] + 1; i <= 9; ++i) if (!vis[i]) {
            ll val = i;
            for (int j = 1; j < dig.size(); ++j) 
                val = val * 10 + mn;
            if (umin(diff1, val - n)) {
                res = val;
            }
        }

        val = 0;

        mn = -1;
        for (int i = 9; i >= 1; --i) 
            if (!vis[i])      
                mn = i;
        if (mn != -1) {     
            for (int i = 0; i <= (int) dig.size(); ++i) {
                val = val * 10 + mn;
            }
            // cout << diff1 << ' ' << val << '\n';
            if (umin(diff1, val - n)) {
                res = val;
            }
        }

        // cout << diff1 << '\n';

        if (diff == diff1) {
            cout << ans << ' ' << res;
        } else if (diff < diff1) {
            cout << ans;
        } else cout << res;
        return;
    }
    cout << "Impossible";

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
