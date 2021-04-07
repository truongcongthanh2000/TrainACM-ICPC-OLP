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

const int maxN = 1e3 + 100;
typedef pair<int, int> i2;

vector<i2> compress(string s){
    int i = 0;
    vector<i2> c;
    while(i < s.length()){
        int j = i + 1;
        while (j < s.length() && s[i] == s[j]){
            j++;
        }
        c.push_back(i2(s[i], j - i));
        i = j;
    }
    return c;
}

bool check[maxN], in[maxN];

void sol(){
    string a, b;
    getline(cin, a);
    getline(cin, b);
    vector<i2> A = compress(a);
    vector<i2> B = compress(b);
    for(int i = 0; i < (int)A.size(); i++ ){
        in[A[i].first] = true;
        if (2 * A[i].second != B[i].second){
            check[A[i].first] = true;
        }
    }
    for(char h = 'a'; h <= 'z'; h++){
        if (!check[h] && in[h])
            cout << h;
    }
    if (!check[' '] && in[' ']) cout << ' ';
}


void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
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