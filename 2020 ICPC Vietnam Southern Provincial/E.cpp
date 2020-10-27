#include <bits/stdc++.h>
#define TASK "task"
/// 2020.10.27

using namespace std;

void rwFile() {
    #ifdef THEMIS
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
    #endif
}

vector<int> gen(set<int> &S) {
    vector<int> res;
    int n = S.size();
    for (int i = 0; i < n - 1; ++i) {
        if (i % 2 == 0) {
            res.push_back(*S.begin());
            S.erase(S.begin());
        }
        else {
            auto tmp = S.begin();
            tmp++;
            res.push_back(*tmp);
            S.erase(*tmp);
        }
    }
    while (S.size()) {
        res.push_back(*S.begin());
        S.erase(S.begin());
    }
    return res;
}

void solveE() {
    int n; cin >> n;
    vector<int> arr(n + 1, 0), r(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    if (n == 1) {
        cout << 1;
        return;
    }
    arr[0] = 1832;
    int type = 0;
    if (arr[1] > arr[2]) type = 1;
    set<int> S;
    for (int i = 1; i <= n; ++i) S.insert(i);
    if (type) {
        for (int i = 1; i < n; ++i) {
            if (i % 2 == 1) {
                r[i] = *S.rbegin();
                S.erase(arr[i]);
            }
            else {
                auto tmp = S.end();
                tmp--;
                tmp--;
                r[i] = *tmp;
                r[i] = min(r[i], arr[i - 1] - 1);
                S.erase(arr[i]);
            }
        }
        r[n] = *S.begin();
        S.erase(S.begin());
//        for (int i = 1; i <= n; ++i) cout << r[i] << ' ';
//        cout << '\n';
        int pos = n;
        while (arr[pos] == r[pos]) pos--;
        if (pos == 1) {
            arr[2] = arr[1] + 1;
            set<int> S;
            for (int i = 1; i <= n; ++i) {
                if (i != arr[1] && i != arr[1] + 1) S.insert(i);
            }
            vector<int> res = gen(S);
            cout << arr[1] << ' ' << arr[2] << ' ';
            for (int i : res) cout << i << ' ';
            return;
        }
        if (pos == 0) {
            set<int> S;
            for (int i = 1; i <= n; ++i) S.insert(i);
            vector<int> res = gen(S);
            for (int i : res) cout << i << ' ';
            return;
        }
        set<int> S;
        for (int i = 1; i <= n; ++i) {
            S.insert(i);
        }
        for (int i = 1; i < pos; ++i) S.erase(arr[i]);
        for (auto it = S.begin(); it != S.end(); ++it) {
            if (*it > arr[pos]) {
                int tmp = arr[pos];
                arr[pos] = *it;
                S.erase(it);
                S.insert(tmp);
                break;
            }
        }
        if (pos % 2 == 0) {
            for (auto it = S.begin(); it != S.end(); ++it) {
                if (*it > arr[pos]) {
                    arr[pos + 1] = *it;
                    S.erase(it);
                    break;
                }
            }
            vector<int> tmp = gen(S);
            for (int i = pos + 2; i <= n; ++i) arr[i] = tmp[i - pos - 2];
        }
        else {
            vector<int> tmp = gen(S);
            for (int i = pos + 1; i <= n; ++i) arr[i] = tmp[i - pos - 1];
        }
        for (int i = 1; i <= n; ++i) cout << arr[i] << ' ';
    }
    else {
        for (int i = 1; i < n; ++i) {
            if (i % 2 == 0) {
                r[i] = *S.rbegin();
                S.erase(arr[i]);
            }
            else {
                auto tmp = S.end();
                tmp--;
                tmp--;
                r[i] = *tmp;
                if (i > 1) r[i] = min(r[i], arr[i - 1] - 1);
                S.erase(arr[i]);
            }
        }
        r[n] = *S.begin();
        S.erase(S.begin());
//        for (int i = 1; i <= n; ++i) cout << r[i] << ' ';
//        cout << '\n';
        int pos = n;
        while (arr[pos] == r[pos]) pos--;
        set<int> S;
        for (int i = 1; i <= n; ++i) S.insert(i);
        if (pos == 0) {
            arr[1]++;
            S.erase(arr[1]);
            vector<int> tmp = gen(S);
            cout << arr[1] << ' ';
            for (int i : tmp) cout << i << ' ';
            return;
        }
        if (pos == 1) {
            for (auto it = S.begin(); it != S.end(); ++it) {
                if (*it > arr[pos]) {
                    int tmp = arr[pos];
                    arr[pos] = *it;
                    S.erase(it);
                    S.insert(tmp);
                    break;
                }
            }
            vector<int> tmp = gen(S);
            cout << arr[1] << ' ';
            for (int i : tmp) cout << i << ' ';
            return;
        }
        for (int i = 1; i <= pos; ++i) S.erase(arr[i]);
        for (auto it = S.begin(); it != S.end(); ++it) {
            if (*it > arr[pos]) {
                int tmp = arr[pos];
                arr[pos] = *it;
                S.erase(it);
                S.insert(tmp);
                break;
            }
        }
        if (pos % 2 == 1) {
            for (auto it = S.begin(); it != S.end(); ++it) {
                if (*it > arr[pos]) {
                    arr[pos + 1] = *it;
                    S.erase(it);
                    break;
                }
            }
            vector<int> tmp = gen(S);
            for (int i = 1; i <= pos + 1; ++i) cout << arr[i] << ' ';
            for (int i : tmp) cout << i << ' ';
            return;
        }
        vector<int> tmp = gen(S);
        for (int i = 1; i <= pos; ++i) cout << arr[i] << ' ';
        for (int i : tmp) cout << i << ' ';
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    rwFile();
    solveE();
}
