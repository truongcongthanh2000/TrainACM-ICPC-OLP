#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

void solve() {
    int a, b, c, n;
    cin >> a >> b >> c >> n;
    if (min(a, min(b, c)) >= 1 && a + b + c >= n && n >= 3) cout << "YES";
    else cout << "NO";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
    return 0;
}
