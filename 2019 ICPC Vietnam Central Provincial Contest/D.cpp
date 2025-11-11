#include <bits/stdc++.h>
using namespace std;

const   int MaxN = 1e6+5;

int prime[MaxN], n, s[MaxN], a[MaxN];
void Sang(){
    for(int i = 2; i < MaxN; i++) prime[i] = i;
    for(int i = 2 ; i < 4000; i++)
        if (prime[i] == i)
            for(int j = i * i; j < MaxN; j+=i) prime[j] = i;
}

vector<int> c;
int m;
void Nen(){
    for(int i = 0; i <= n; i++)
        c.push_back(s[i]);
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    m = c.size();
}

int IT[MaxN * 4];

void update(int k, int l, int r, int u, int x){
    if (u < l || u > r) return;
    if (l == r){
        IT[k] += x;
        return;
    }
    int mid = (l+r) >> 1;
    update(k*2, l, mid, u, x);
    update(k*2+1, mid+1, r, u, x);
    IT[k] = IT[k*2] + IT[k*2+1];
}

int get(int k, int l, int r, int u, int v){
    if (v < l || u > r) return 0;
    if (u <= l && r <= v) return IT[k];
    int mid = (l + r) >> 1;
    int L = get(k*2, l, mid, u, v);
    int R = get(k*2+1, mid + 1, r, u, v);
    return L + R;
}

long long res;

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    Sang();
    for(int i = 1; i <= n; i++)
        a[i] = (prime[a[i]] == a[i]) ? (1) : (-1);
    for(int i = 1; i <= n; i++)
        s[i] = s[i - 1] + a[i];
    Nen();
    //for(int i = 1; i <= n; i++) cout << s[i] << " ";
    //cout << '\n';
    res = 0;
    for(int i = 0; i <= n; i++){
        int k = lower_bound(c.begin(), c.end(), s[i]) - c.begin();
        //cout << get(1, 0, m, 0, k) << '\n';
        res += get(1, 0, m, 0, k);
        ///if (i!=0 && prime[a[i]] == a[i]) res++;
        update(1, 0, m, k, 1);
    }
    cout << res;
}

int main (){
    //freopen("OB.inp","r",stdin);
    //freopen("OB.out","w",stdout);
    solve();
}
