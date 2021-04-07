#include <bits/stdc++.h>
using namespace std;
const int MaxN=100005*2;
int n,m;
struct data
{
    int L,R,cs;
}a[MaxN];
vector <int> c;

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}
bool Check(char c0, string s) {
    string a = "";
    string b = "";
    int Pos = -1;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == c0) {
            Pos = i;
            break;
        }
    }
    if (Pos == -1) return true;
    for (int i = 0; i < Pos; i++) b += s[i];
    a += s[Pos];
    int tmp = Pos;
    for (int i = Pos + 1; i < n; i++) {
        if (s[i] == c0) Pos = i;
    }
    for (int i = tmp + 1; i < n; i++) {
        char c = s[i];
        if (c == a[0]) {
            a += c;
        }
        else {
            if (i < Pos) b += c;
            else {
                if ((int)b.size() > 0 && c == b[0]) a += c;
                else {
                    b += c;
                }
            }
        }
    }
    a += b;
    int L = 0;
    while (L < (int)a.size() && a[L] == a[0]) L++;
    if (L == n) {
        return true;
    }
    char c = a[L];
    while (L < (int)a.size() && a[L] == c) L++;
    if (L == n) {
        return true;
    }
    c = a[L];
    while (L < (int)a.size() && a[L] == c) L++;
    if (L == n) {
        return true;
    }
    return false;
}
void solve() {
    string s;
    cin >> s;
    bool KQ = false;
    KQ |= Check('R', s);
    KQ |= Check('G', s);
    KQ |= Check('B', s);
    cout << (KQ ? "YES": "NO");
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
