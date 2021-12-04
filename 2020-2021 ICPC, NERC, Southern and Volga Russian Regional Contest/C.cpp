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

const int maxN = 5e5 + 100;

typedef pair<int, int> i2;

void sol(){
    queue<int> que;
    priority_queue<i2> Q;
    int n;
    cin >> n;
    vector<bool> d(n, false);
    int cnt = 1;
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        if (k == 1){
            int x;
            cin >> x;
            que.push(cnt);
            Q.push(i2(x, -cnt));
            cnt++;
        }
        else if (k == 2){
            int t;
            do
            {
                t = que.front();
                que.pop();
            } while (d[t]);
            d[t] = true;
            cout << t << ' ';
        }
        else {
            int t;
            do{
                t = -Q.top().second;
                Q.pop();
            }while(d[t]);
            d[t] = true;
            cout << t << ' ';
        }
    }
}

void solve() {
    clock_t begin = clock();
    int T;
    // cin >> T;
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
