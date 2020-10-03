#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

long long gcd(long long x, long long y) {
    return y == 0 ? abs(x) : gcd(y, x % y);
}

long long lcm(long long x, long long y) {
    return x / gcd(x, y) * y;
}
struct Fraction{
    long long x, y;
    Fraction(){};
    Fraction(long long _x, long long _y) : x(_x), y(_y) {
        normal();
    };
    void normal() {
        long long GCD = gcd(x, y);
        x /= GCD;
        y /= GCD;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
    }
    Fraction operator+ (const Fraction& A){
        long long mau = lcm(y, A.y);
        long long tu = x * (mau / y) + (mau / A.y) * A.x;
        return Fraction(tu, mau);
    }
    Fraction operator- (const Fraction& A){
        long long mau = lcm(y, A.y);
        long long tu = x * (mau / y) - (mau / A.y) * A.x;
        return Fraction(tu, mau);
    }
};

bool is_val(char s){
    return '0' <= s && s <= '9';
}

void sol() {
    string s;
    while (getline(cin, s)){
        s = '(' + s + ')';
        int i = 0;
        auto fn = [&](int &i){
            long long tu = 0;
            while (i < (int)s.size() && is_val(s[i]))
                tu = tu * 10 + (s[i++] - '0');
            return tu;
        };

        stack<Fraction> st;
        stack<char> op;
        while (i < (int)s.size()){
            if (is_val(s[i])) {
                long long tu = fn(i);
                i++;
                long long mau = fn(i);
                st.push(Fraction(tu, mau));
            }
            else{
                if (s[i] == ')'){
                    cerr << "ok" << '\n';
                    vector<Fraction> process;
                    vector<char> tmp_op;
                    while (op.top() != '(') {
                        Fraction F = st.top(); process.push_back(F);
                        tmp_op.push_back(op.top());
                        st.pop(); op.pop();
                    }
                    process.push_back(st.top()); st.pop();
                    tmp_op.push_back('+'); op.pop();
                    Fraction res(0, 1);
                    assert((int)process.size() == (int)tmp_op.size());
                    for (int i = 0; i < (int)process.size(); i++) {
                        if (tmp_op[i] == '+') res = res + process[i];
                        else res = res - process[i];
                    }
                    st.push(res);
                }
                else {
                    op.push(s[i]);
                }
                i++;
            }
        }
        cout << st.top().x << "/" << st.top().y << '\n';
    }
}

void solve() {
    int T;
    //cin >> T;
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
