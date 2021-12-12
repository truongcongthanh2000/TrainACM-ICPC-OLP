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

int L[maxN], R[maxN], pre[maxN];

void sol() {
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        L[i] = 0;
        R[i] = s.length() - 1;
    }
    for(char ch = 'a'; ch <= 'z'; ch++)
        pre[ch] = -1;
    for(int i = 0; i < s.length(); i++){
        char ch = s[i];
        L[i] = pre[ch] + 1;
        if (pre[ch] != -1)
            R[pre[ch]] = i - 1;
        pre[ch] = i;
    }
    long long res = 0;
    for(int i = 0; i < s.length(); i++){
        // cout << L[i] << ' ' << R[i] << endl;
        res += (long long)(i - L[i] + 1) * (R[i] - i + 1);
    }
    cout << res << endl;
}

void solve() {
    clock_t start, end;
    start = clock();
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
