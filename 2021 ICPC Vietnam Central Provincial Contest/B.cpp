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
    int n;
    cin >> n;
    vector<int> a(n);
    int equal = 0, lower = 0, upper = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] == 0) equal++;
        else if (a[i] < 0) lower++;
        else upper++;
    }

    long long res = 1, prod = 1;
    for (int v : a) prod = (prod * v) % MOD;

    if (equal >= 2) res = 0;
    else 
    if (equal == 1){
        if (lower % 2 == 0){
            for(int v : a) 
                if (v != 0) 
                    res = (res * v) % MOD;
        }
        else{
            res = 0;
        }
    }
    else{
        if (lower % 2 == 0){
            res = prod;
        }
        else{
            int temp = -1e9 - 10;
            for(int v : a)
                if (v < 0)
                    temp = max(temp, v);
            for(int v : a)
                if (v != temp)
                    res = (res * v) % MOD;
        }
    }
    cout << res << endl;
}

void solve() {
    clock_t start, end;
    start = clock();
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
