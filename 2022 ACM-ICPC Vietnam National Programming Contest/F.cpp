#include <bits/stdc++.h>

using namespace std;

void open_file() {
}
void sol() {
    string s, t, l;
    cin >> s >> t >> l;
    if (s == l + t)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
}
int main() {
    int t = 1;
    cin >> t;
    while (t--) sol();
}
