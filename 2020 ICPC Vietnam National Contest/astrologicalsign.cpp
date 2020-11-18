#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

void sol() {
    int d;
    string s;
    cin >> d >> s;
    if (s == "Jan") {
        if (d >= 21) cout << "Aquarius" << '\n';
        else cout << "Capricorn" << '\n';
        return;
    }
    if (s == "Feb") {
        if (d >= 20) cout << "Pisces" << '\n';
        else cout <<" Aquarius" << '\n';
        return;
    }
    if (s == "Mar") {
        if (d >= 21) cout << "Aries" << '\n';
        else cout << "Pisces" << '\n';
        return;
    }
    if (s == "Apr") {
        if (d >= 21) cout << "Taurus" << '\n';
        else cout << "Aries" << '\n';
        return;
    }
    if (s == "May") {
        if (d >= 21) cout << "Gemini" << '\n';
        else cout << "Taurus" << '\n';
        return;
    }
    if (s == "Jun") {
        if (d >= 22) cout << "Cancer" << '\n';
        else cout << "Gemini" << '\n';
        return;
    }
    if (s == "Jul") {
        if (d >= 23) cout << "Leo" << '\n';
        else cout << "Cancer" << '\n';
        return;
    }
    if (s == "Aug") {
        if (d >= 23) cout << "Virgo" << '\n';
        else cout << "Leo" << '\n';
        return;
    }
    if (s == "Sep") {
        if (d >= 22) cout << "Libra" << '\n';
        else cout << "Virgo" << '\n';
        return;
    }
    if (s == "Oct") {
        if (d >= 23) cout << "Scorpio" << '\n';
        else cout << "Libra" << '\n';
        return;
    }
    if (s == "Nov") {
        if (d >= 23) cout << "Sagittarius" << '\n';
        else cout << "Scorpio" << '\n';
        return;
    }
    if (s == "Dec") {
        if (d >= 22) cout << "Capricorn" << '\n';
        else cout << "Sagittarius" << '\n';
        return;
    }
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
