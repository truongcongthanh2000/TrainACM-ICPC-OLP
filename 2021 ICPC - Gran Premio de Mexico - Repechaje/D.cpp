#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

int prime[maxN];

void Sang(){
    for (int i = 2; i <= 1e7; i++)
        prime[i] = i;
    for(int i = 2; i <= sqrt(1e7); i++){
        if (prime[i] == i){
            for (int j = i + i; j <= 1e7; j+=i)
                prime[j] = i;
        }
    }
}

vector<int> get_prime(int A){
    vector<int> c;
    while(A > 1){
        c.push_back(prime[A]);
        A /= prime[A];
    }
    return c;
}

void sol(){
    Sang();
    int Q;
    cin >> Q;
    while(Q--){
        int K;
        cin >> K;
        vector<int> a;
        a = get_prime(K + 2);
        sort(a.begin(), a.end());
        a.resize(unique(a.begin(), a.end()) - a.begin());
        if (a.back() == 2){
            cout << -1 << '\n';
            continue;
        }
        vector<int> c;
        for (int i = 0; i < (int)a.size(); i++)
            if (a[i] > 2)
                c.push_back(a[i]);
        for(int i = 0; i < (int)c.size() - 1; i++)
            cout << c[i] << ' ';
        cout << c.back() << '\n';
    }
}

void solve() {
    clock_t begin = clock();
    int T;
//    cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
