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
    int x;
    cin >> x;
    int k = 1;

    int nx = 0;
    while (x > 0) {
        int md = x % 10;
        nx += md * k;
        x /= 10;
        k *= 8;
    }


    x = nx;
    nx = 0;

    vector<vector<int>> a(3, vector<int> (3, -1));
    int cnt = 0;
    for (int i = 9; i < 18; ++i) {
        int r = cnt / 3, c = cnt % 3;
        if ((x >> (i - 9) & 1)) {
            a[r][c] = (x >> i & 1);
        }
        cnt++;
    }
    
    for (int i = 0; i < 3; ++i) {
        if (a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][0] != -1) {
            cout << (a[i][0] ? 'X' : 'O') << ' ' << "wins\n";
            return;
        }
    }
    for (int j = 0; j < 3; ++j) {
        if (a[0][j] != -1 && a[0][j] == a[1][j] && a[1][j] == a[2][j]) {
            cout << (a[0][j] ? 'X' : 'O') << ' ' << "wins\n";
            return;
        }
    }

    if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[2][2] != -1) {
        cout << (a[0][0] ? 'X' : 'O') << ' ' << "wins\n";
        return;
    }
    if (a[2][0] == a[1][1] && a[1][1] == a[0][2] && a[1][1] != -1) {
        cout << (a[2][0] ? 'X' : 'O') << ' ' << "wins\n";
        return;
    }

    for (int i = 0; i < 9; ++i) {
        if (!((x >> i) & 1)) {
            cout << "In progress\n";
            return;
        }
    }

    cout << "Cat's\n";
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
