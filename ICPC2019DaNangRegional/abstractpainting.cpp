#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 1e5 + 100;
const int maxM = 1e7;
const long long oo = 1e18;
const int module = 1e9 + 7;
const long double du = 1e-9;


void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);

}


void solve() {
    int T;
    cin >> T;
    while (T--) {
        int R, C;
        cin >> R >> C;
        long long Res = 1;
        for (int i = 1; i <= R + C; i++) Res = Res * 3 % module;
        for (int i = 1; i <= R * C; i++) Res = Res * 2 % module;
        cout << Res << '\n';
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
   /// doc();
    solve();
}
