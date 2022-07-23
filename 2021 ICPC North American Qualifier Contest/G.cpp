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
const int N = 1005;

int a[N];
int n, c;

void sol() {
    cin >> c >> n;    
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    vector<pair<int, int>> seg, seg2;

    for (int i = 1; i <= n; ++i) {
        int j = i;
        while (j + 1 <= n && a[j + 1] - a[j] == 1) 
            j++;
        seg.push_back(make_pair(a[i], a[j]));
        i = j;
    }
    a[0] = 0;
    a[n + 1] = c + 1;
    for (int i = 1; i <= n + 1; ++i) {
        if (a[i] - a[i - 1] > 1) {
            seg2.push_back(make_pair(a[i - 1] + 1, a[i] - 1));
        }
    }

    auto print = [&](vector<pair<int, int> > seg) {
        for (int i = 0; i < (int) seg.size(); ++i) {
            if (i == (int) seg.size() - 1) {
                if (i > 0) 
                    cout << " and ";
                if (seg[i].first == seg[i].second) {
                    cout << seg[i].first;
                } else {
                    cout << seg[i].first << '-' << seg[i].second;
                }
            } else {
                if (seg[i].first == seg[i].second) {
                    cout << seg[i].first;
                } else {
                    cout << seg[i].first << '-' << seg[i].second;
                }
                if (i < (int) seg.size() - 2) {
                    cout << ", ";
                }
            }
        }
    };
    cout << "Errors: ";
    print(seg);
    cout << '\n';
    cout << "Correct: ";
    print(seg2);
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
