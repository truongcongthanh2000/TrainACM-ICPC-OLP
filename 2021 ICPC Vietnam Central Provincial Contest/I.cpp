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

typedef pair<long long, long long> ii;

struct rect{
    long long x, y, w, h;
    rect() {

    }
    rect(long long _x, long long _y, long long _w, long long _h){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    ii upper_left(){
        long long X = x * 2 - w;
        long long Y = y * 2 - h;
        return ii(X, Y); 
    }
    ii lower_right(){
        long long X = x * 2 + w;
        long long Y = y * 2 + h;
        return ii(X, Y); 
    }
};

bool giao(rect A, rect B){
    ii A_left = A.upper_left();
    ii A_right = A.lower_right();
    ii B_left = B.upper_left();
    ii B_right = B.lower_right();

    long long x_min = max(A_left.first, B_left.first);
    long long x_max = min(A_right.first, B_right.first);
    long long y_min = max(A_left.second, B_left.second);
    long long y_max = min(A_right.second, B_right.second); 
    
    if (x_max <= x_min || y_max <= y_min) return false;

    return true;
}

rect rotate(rect a) {
    return rect(a.x, a.y, a.h, a.w);
}

void sol() {
    int n;
    cin >> n;
    vector<rect> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y >> a[i].w >> a[i].h;

    vector<rect> old;
    string ans;
    for (int i = 0; i < n; i++) {
        bool can = false;
        for (char c : {'K','Q'}) {
            rect ai = c == 'Q' ? rotate(a[i]) : a[i];
            bool ok = true;
            for (rect x : old) {
                ok &= giao(x, ai) == false;
                if (!ok) break;
            }
            for (int j = i + 1; j < n; j++) {
                bool has = false;
                for (rect aj : {a[j], rotate(a[j])}) {
                    if (giao(ai, aj) == false) {
                        has = true;
                        break;
                    }
                }
                if (!has) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                can = true;
                ans += c;
                old.push_back(ai);
                break;
            }
        }
        if (!can) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
    cout << ans << endl;
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
