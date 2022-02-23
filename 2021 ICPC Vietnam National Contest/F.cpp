#include<bits/stdc++.h>

using namespace std;

void ioFiles() {
    #ifdef THEMIS
        freopen("solve.txt", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

void solve() {
    int n;
    cin >> n;
    cout << (1LL << (n - 1));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ioFiles();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
