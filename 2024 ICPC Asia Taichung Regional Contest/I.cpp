#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e6 + 100;
const int MOD = 998244353;

int T[maxN][95], numNode = 0;
int parent[maxN], link[maxN];
multiset<pair<int, int>> setNode[maxN];
void sol() {
    int Q;
    cin >> Q;
    vector<vector<string>> q(Q);
    vector<string> order_p;
    for (int i = 0; i < Q; i++) {
        string s;
        cin >> s;
        q[i].push_back(s);
        if (s == "add") {
            string id, p;
            cin >> id >> p;
            q[i].push_back(id);
            q[i].push_back(p);
            order_p.push_back(p);
        } else {
            string n;
            cin >> n;
            q[i].push_back(n);
        }
    }
    sort(order_p.begin(), order_p.end());
    order_p.resize(unique(order_p.begin(), order_p.end()) - order_p.begin());

    map<int, set<int>> map_order_id;
    auto add = [&](const string &p, int pid) {
        int id = lower_bound(order_p.begin(), order_p.end(), p) - order_p.begin();
        map_order_id[id].insert(pid);

        int root = 0, m = p.size();
        for (int i = 0; i < m; i++) {
            setNode[root].insert({-m, id});
            int c = p[i] - 33;
            if (T[root][c] == 0) {
                T[root][c] = ++numNode;
                parent[numNode] = root;
                link[numNode] = c;
            }
            root = T[root][c];
        }
        setNode[root].insert({-m, id});
    };
    auto remove = [&](const string &p, int pid) {
        int id = lower_bound(order_p.begin(), order_p.end(), p) - order_p.begin();
        map_order_id[id].erase(pid);

        int root = 0, m = p.size();
        for (int i = 0; i < m; i++) {
            setNode[root].erase(setNode[root].find({-m, id}));
            int c = p[i] - 33;
            root = T[root][c];
        }
        setNode[root].erase(setNode[root].find({-m, id}));
    };

    int root = 0;
    list<char> add_T;
    auto pop_first = [&]() {
        while (add_T.size()) {
            int c = add_T.front() - 33;
            if (T[root][c] == 0 || setNode[root].empty() || setNode[T[root][c]].empty()) {
                break;
            }
            root = T[root][c];
            add_T.pop_front();
        }
    };
    auto pop_last = [&](int d) {
        while (add_T.size() && d) {
            add_T.pop_back();
            d--;
        }
        while (d && root) {
            root = parent[root];
            d--;
        }
    };
    vector<string> vector_string(Q + 1);
    for (int i = 0; i < Q; i++) {
        string type = q[i][0];
        if (type == "add") {
            int id = std::stoi(q[i][1]);
            string p = q[i][2];
            vector_string[id] = p;
            add(p, id);
        }
        if (type == "delete") {
            int id = std::stoi(q[i][1]);
            remove(vector_string[id], id);
            while (root && setNode[root].empty()) {
                int c = link[root];
                add_T.push_front(char(c + 33));
                root = parent[root];
            }
        }
        if (type == "append") {
            for (char &c : q[i][1]) {
                add_T.push_back(c);
            }
        }
        if (type == "backspace") {
            int d = std::stoi(q[i][1]);
            pop_last(d);
        }
        pop_first();
        if (add_T.size() || setNode[root].empty()) {
            cout << -1 << '\n';
        } else {
            auto it = setNode[root].begin();
            int order_id = it->second;
            cout << *map_order_id[order_id].begin() << '\n';
        }
    }
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
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
