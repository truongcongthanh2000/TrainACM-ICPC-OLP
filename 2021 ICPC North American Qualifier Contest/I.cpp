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

vector<string> split(string s, string delimiter) {
    size_t pos = 0;
    vector<string> ans;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        string token = s.substr(0, pos);
        ans.push_back(token);
        s.erase(0, pos + (int)delimiter.size());
    }
    ans.push_back(s);
    return ans;
}
void sol() {
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    set<string> ans;
    set<pair<vector<string>, string> > vand, vor;
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        auto vs = split(s, " ");
        if ((int)vs.size() == 1) {
            ans.insert(s);
        }
        else {
            vector<string> a;
            for (int i = 1; i < (int)vs.size() - 2; i += 2)  a.push_back(vs[i]);
            if (s.find("and") != std::string::npos) vand.insert({a, vs.back()});
            else vor.insert({a, vs.back()});
        }
    }
    while ((int)vand.size() > 0 || (int)vor.size() > 0) {
        bool changeAnd = false, changeOr = false;
        for (auto it = vand.begin(); it != vand.end(); ) {
            bool ok = true;
            for (string s : it->first) {
                if (!ans.count(s)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                changeAnd = true;
                ans.insert(it->second);
                it = vand.erase(it);
            } else {
                ++it;
            }
        }
        for (auto it = vor.begin(); it != vor.end(); ) {
            bool ok = false;
            for (string s : it->first) {
                if (ans.count(s)) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                changeOr = true;
                ans.insert(it->second);
                it = vor.erase(it);
            } else {
                ++it;
            }
        }
        if (!changeAnd && !changeOr) break;
    }
    cout << (int)ans.size();
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
