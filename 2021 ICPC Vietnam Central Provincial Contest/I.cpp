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

typedef pair<double, double> ii;

struct rect{
    int x, y, w, h;
    rect(int _x, int _y, int _w, int _h){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    ii upper_left(){
        double X = x - (double)w / 2;
        double Y = y - (double)h / 2;
        return ii(X, Y); 
    }
    ii lower_right(){
        double X = x + (double)w / 2;
        double Y = y + (double)h / 2;
        return ii(X, Y); 
    }
};

bool giao(rect A, rect B){
    ii A_left = A.upper_left();
    ii A_right = A.lower_right();
    ii B_left = B.upper_left();
    ii B_right = B.lower_right();

    double x_min = max(A_left.first, B_left.first);
    double x_max = min(A_right.first, B_right.first);
    double y_min = max(A_right.second, B_right.second);
    double y_max = min(A_left.second, B_left.second); 
    
    if (x_max < x_min || y_max < y_min) return false;

    return true;
}

void sol() {
    
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
