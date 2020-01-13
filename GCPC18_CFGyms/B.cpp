#include <bits/stdtr1c++.h>
#include <time.h>
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

using namespace std;
#define TASK "solve"

const int N = 3e5 + 100;
//const long long Base = 500000004;
const int module = 987654319;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

long long rand(long long l, long long r){
    return 1LL * (1LL * rnd() * RAND_MAX + rnd()) % (r - l + 1) + l;
}
struct Point{
    long double x, y;
    Point(){};
    Point(long double _x, long double _y) {
        x = _x;
        y = _y;
    }
};

Point A, B;
long double R;
void doc() {
    //freopen(TASK ".inp","r",stdin);
    //freopen(TASK ".out","w",stdout);
    cin >> A.x >> A.y >> B.x >> B.y;

}
long double Dist(Point A, Point B) {
    long double x = A.x - B.x;
    long double y = A.y - B.y;
    return sqrt(x * x + y * y);
}
Point Find_Point(Point A, Point B) {
    Point AB;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    long double HS = AB.x * AB.x + AB.y * AB.y;
    long double C = AB.x * A.x + AB.y * A.y;
    C = (long double)0 - C;
    long double T = C / HS;
    Point Res = Point(A.x + AB.x * T, A.y + AB.y * T);
    return Res;
}
bool Equal(long double A, long double B) {
    long double du = 1e-9;
    return abs(A - B) <= du;
}
bool Check(Point A, Point B) { ///AB co cat duong trong khong
    Point AB;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AB.y *= (long double)(0.0 - 1.0);
    swap(AB.x, AB.y);
    ///AB = nAB
    long double C = AB.x * (0.0 - A.x) + AB.y * (0.0 - A.y);
    long double D = abs(C) / sqrt(AB.x * AB.x + AB.y * AB.y);
    if (D >= R) return true;
    Point H = Find_Point(A, B);
    //cout << H.x << " " << H.y << '\n';
    return !Equal(Dist(A, H) + Dist(H, B), Dist(A, B));
}
long double Get_Dist(Point O) {
    return Dist(O, A) + Dist(O, B);
}
long double Get(long double x) {
    long double Y1 = sqrt(R * R - x * x);
    long double Y2 = 0.0 - sqrt(R * R - x * x);
    return min(Get_Dist(Point(x, Y1)), Get_Dist(Point(x, Y2)));
}
long double min_F(long double Left_x, long double Right_x) {
    for (int i = 0; i < 5000000; i++) {
        long double x1 = Left_x + (Right_x - Left_x) / 3.0;
        long double x2 = Right_x - (Right_x - Left_x) / 3.0;
        if (Get(x1) < Get(x2)) Right_x = x2;
        else Left_x = x1;
    }
    return Get(Left_x);
}
void Print(long double Res) {
    cout << fixed << setprecision(10) << Res;
}
void solve() {
    Point O;
    int R;
    cin >> O.x >> O.y >> R;
    cin >> O.x >> O.y >> R;
    long double AB = Dist(A, B);
    long double AO = Dist(A, O);
    long double BO = Dist(B, O);
    long double Cos = (AO * AO + BO * BO - AB * AB) / (2.0 * AO * BO);
    long double AOB = acos(Cos);
    long double AOH1 = acos(R / AO);
    long double BOH2 = acos(R / BO);
    long double H1OH2 = AOB - AOH1 - BOH2;
    long double AH1 = sqrt(AO * AO - R * R);
    long double BH2 = sqrt(BO * BO - R * R);
    long double H1H2 = H1OH2 * R;
    long double Res = AH1 + BH2 + H1H2;
    Print(Res);
}
int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
