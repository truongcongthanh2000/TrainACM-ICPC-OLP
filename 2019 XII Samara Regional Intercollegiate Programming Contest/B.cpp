#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int d[100005],a[100005],b[5][10005];

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

void Print()
{
    int k = 0;
    k=d[0];
    for (int i = 1; i <= d[1]; i++)
        b[2][k++] = 1;
    for (int i = 1; i <= d[3]; i++) {
        b[1][k]=b[2][k] = 1;
        k++;
    }
    for (int i = 1; i <= d[2]; i++)
        b[1][k++] = 1;
    for (int i = 1; i < 3; i++) {
        for(int j = 0; j < s1.length(); j++)
            if (b[i][j] == 1) cout << '#';
            else cout << '.';
        cout << '\n';
    }

}

int main(){

    cin >> s1 >> s2;
    for (int i = 0; i < s1.length(); i++) {
        int t1 = 0,t2 = 0;
        if (s1[i] == '#') t1 = 1;
        if (s2[i] == '#') t2 = 1;
        d[t1*2+t2]++;
        a[i] = t1*2+t2;
    }
    bool check = true;
    if (d[3] != 0) check = true;
    else
        if (d[1]!=0 && d[2]!=0) check = false;
    if (check){
        cout << "YES" << '\n';
        Print();
    }
    else cout << "NO";
}
