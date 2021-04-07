#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 3e5 + 10;
const int maxA = 1e6 + 10;
const long long oo = 1e16;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double du = 1e-9;
const string YES = "YES";
const string NO = "NO";
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}

typedef pair<int, int> i2;
vector<int> Used;
char Ask(int i, int x) {
    cout << "? " << i << " " << x << endl;
    char ans;
    cin >> ans;
    return ans;
}
void sol() {
    int n;
    cin >> n;
    vector<int> resa(n + 1), resb(n + 1);
    function<void(vector<int>, vector<int>, vector<int>)> Process = [&](vector<int> cur_a, vector<int> cur_b, vector<int> cur_used) {
        assert((int)cur_a.size() == (int)cur_b.size());
        if ((int)cur_a.size() == 0) return;
        if ((int)cur_a.size() == 1) {
            int idA = cur_a[0];
            int idB = cur_b[0];
            resa[idA] = cur_used[0];
            resb[idB] = cur_used[0];
            return;
        }
        int sz = (int)cur_a.size();
        int idPivot_a = rnd() % sz;
        int idPivot_b = 0;
        int Pivot_a = cur_a[idPivot_a];
        vector<int> weakB, biggerB;
        for (int i = 0; i < sz; i++) {
            char c = Ask(Pivot_a, cur_b[i]);
            if (c == '=') idPivot_b = i;
            if (c == '<') biggerB.push_back(cur_b[i]);
            if (c == '>') weakB.push_back(cur_b[i]);
        }
        int Pivot_b = cur_b[idPivot_b];
        vector<int> weakA, biggerA;
        for (int i = 0; i < sz; i++) {
            if (i == idPivot_a) continue;
            char c = Ask(cur_a[i], Pivot_b);
            if (c == '<') weakA.push_back(cur_a[i]);
            else biggerA.push_back(cur_a[i]);
        }
        assert((int)weakB.size() < (int)cur_used.size());
        int value_pivot = cur_used[(int)weakB.size()];
        resa[Pivot_a] = value_pivot;
        resb[Pivot_b] = value_pivot;
        vector<int> cur_usedWeak;
        for (int x : cur_used) {
            if (x < value_pivot) cur_usedWeak.push_back(x);
        }
        vector<int> cur_usedBigger;
        for (int x : cur_used) {
            if (x > value_pivot) cur_usedBigger.push_back(x);
        }
        Process(weakA, weakB, cur_usedWeak);
        Process(biggerA, biggerB, cur_usedBigger);
    };
    vector<int> cur_a(n), cur_b(n), cur_used(n);
    for (int i = 1; i <= n; i++) {
        cur_a[i - 1] = i;
        cur_b[i - 1] = i;
        cur_used[i - 1] = i;
    }
    Process(cur_a, cur_b, cur_used);

    vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = resa[i];
        res[i] = 1;
        while (resb[res[i]] != x) res[i]++;
    }
    cout << "! " << res[1];
    for (int i = 2; i <= n; i++) cout << " " << res[i];
    cout << endl;
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        ///cout << "Case #" << TestCase << ": ";
        sol();
    }
}

int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
