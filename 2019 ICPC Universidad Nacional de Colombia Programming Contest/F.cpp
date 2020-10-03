#include<bits/stdc++.h>
#define ll long long
#define frac pair<ll, ll>
using namespace std;

ll gcd(ll a, ll b){
    if(b==0)return a;
    return gcd(b, a%b);
}

frac add(frac p1, frac p2){
    ll div = gcd(abs(p1.second), abs(p2.second));
    ll den = (p1.second / div) * p2.second;
    ll num = p1.first * (p2.second / div) + p2.first * (p1.second / div);
    div = gcd(abs(num), abs(den));
    return {num/div, den/div};
}

int main(){
    string line;
    ll aux;
    bool currentneg, acumneg;
    while(getline(cin, line)){
        stack<bool> signs;
        vector<frac> formula;
        aux = 0;
        currentneg = false;
        acumneg = false;
        for(int i = 0 ; i < line.length(); i++){
            if(line[i] == '('){
                acumneg = acumneg ^ currentneg;
                signs.push(currentneg);
                currentneg = false;
                continue;
            }
            if(line[i] == ')'){
                acumneg = acumneg ^ signs.top();
                signs.pop();
                continue;
            }
            if(line[i] == '+'){
                formula.back().second = aux;
                aux = 0;
                currentneg = false;
                continue;
            }
            if(line[i] == '-'){
                formula.back().second = aux;
                aux = 0;
                currentneg = true;
                continue;
            }
            if(line[i] == '/'){
                if(acumneg ^ currentneg)aux = -aux;
                formula.push_back({aux, 0});
                aux = 0;
                continue;
            }
            aux = aux * 10 + (line[i] - '0');
        }
        formula.back().second = aux;
        frac res = {0, 1};
        for(int i=0;i<formula.size();i++){
            res = add(res, formula[i]);
        }
        cout<<res.first<<"/"<<res.second<<endl;
    }
}
