#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;

int ss(string s1, string s2){
    if (s1 == s2) return 2;
    if (s1.length() < s2.length()) return 0;
    if (s1.length() > s2.length()) return 1;
    int i = 0;
    while (i < s1.length() && s1[i] == s2[i]){
        i++;
    }
    return (s1[i] > s2[i]);
}

int get(string s1, string s2){
    if (s1 == s2) return 2;
    int i = 0, j = 0;
    while (i < s1.length() && j < s2.length()){
        if ('a' <= s1[i] && s1[i] <= 'z'){
            if (s1[i] < s2[j]) return 0;
            if (s1[i] > s2[j]) return 1;
            i++;j++;
        }
        else {
            string n1 = "", n2 = "";
            while (i < s1.length() && '0' <= s1[i] && s1[i] <= '9') n1 += s1[i++];
            while (j < s2.length() && '0' <= s2[j] && s2[j] <= '9') n2 += s2[j++];
            int k = ss(n1, n2);
            if (k == 2) continue;
            return k;
        }
    }
}

void sol() {
    string s1, s2;
    cin >> s1 >> s2;
    int k = get(s1, s2);
    if (k == 0) cout << "<";
    else
        if (k == 1) cout << ">";
        else cout << "=";

}
void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
