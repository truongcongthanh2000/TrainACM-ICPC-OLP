#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<int,int> pii;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ll,ll> pl;
typedef vector<pi> vpi;

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define R0F(i,a) for (int i = (a)-1; i >= 0; --i)
#define sz(a) (int)a.size()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define pb push_back

#define f first
#define s second

const int MX = 200005;
const ll INF = 1e18;

template<class T> void ckmax(T& a, T b) { a = max(a,b); }
template<class T> void ckmin(T& a, T b) { a = min(a,b); }

int n;
vpi adj[MX];
ll mn[MX];
int X[MX], root = 0;
ll minAns = 0;
bool special[MX];

void addEdge(int a, int b, int c) {
    adj[a].pb({b,c});
    adj[b].pb({a,c});
}

void dfsw(int x, int y) {
    special[x] = x == 0;
    ll ret = 0;
    int cool = -1;
    trav(t,adj[x]) if (t.f != y) {
        dfsw(t.f,x);
        special[x] |= special[t.f];
        if (!special[t.f]) ret += min(1LL-t.s,mn[t.f]-t.s);
        else ret += mn[t.f]-t.s;
    } else cool = t.s;
    if (x != root) {
        assert(cool != -1);
        mn[x] = ret+X[x];
        ckmin(minAns,mn[x]-cool);
    }
}

ll worst() {
    dfsw(root,-1);
    return -minAns;
}

priority_queue<pi> stor[MX];
// stores pairs in the form (a,b) where b >= 0, in decreasing order of a

// suppose that you currently have cur dollars
// then using this pair means that cur -> cur+a -> cur+b
// if a is negative, think of this as going into debt while entering a subtree
// in order to gain money after you exit a subtree

// if you have a bunch of pairs in these form, then in order to gain as much profit
// as possible while minimizing the amount you go into debt, you should take the pairs
// with greater a first

pi operator+(const pi& l, const pi& r) { // if you use pair l and then pair r
    return {min(l.f,l.s+r.f),l.s+r.s};
}

void adjust(priority_queue<pi>& a, int x) {
    assert(x < 0); pi p = {x,x};
    while (sz(a) && (p.s <= 0 || a.top().f >= p.f)) {
        // don't want to put an element in priority queue if it's second element is <= 0
        // (you wouldn't want to enter a subtree if it gives non-positive overall profit)
        // so keep popping from priority queue and modifying p until p.s > 0
        auto t = a.top(); a.pop();
        p = p+t;
    }
    if (p.s > 0) a.push(p);
    // if p.s <= 0, then definitely no point in entering subtree corresponding to a
}

void comb(priority_queue<pi>& a, priority_queue<pi>& b) {
    // merge two pqs in O(S*logS) where S is size of smaller one
    if (sz(a) < sz(b)) swap(a,b);
    while (sz(b)) { a.push(b.top()); b.pop(); }
}

void yay(int x, int y) { // great function name!
    trav(t,adj[x]) if (t.f != y) {
        yay(t.f,x);
        adjust(stor[t.f],-t.s); // adjust elements in pq cost of edge
    }
    stor[x].push({X[x],X[x]});
    trav(t,adj[x]) if (t.f != y) comb(stor[x],stor[t.f]);
}

ll best() {
    X[root] = 1e9; yay(0,-1); // set value of motherlode = INF
    int ans = 0, cur = 0;
    while (sz(stor[0]) && ans < 1e9/2) { // you can stop once you reach the motherlode
        // (initial amount of money)+cur+stor[0].top().f must be at least 0
        ckmax(ans,-cur-stor[0].top().f); cur += stor[0].top().s;
        stor[0].pop();
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    FOR(i,1,n) {
        int p,y; cin >> p >> X[i] >> y;
        addEdge(i,p,y);
    }
    while (X[root] != -1) root ++;
    cout << worst() << " " << best();
}
