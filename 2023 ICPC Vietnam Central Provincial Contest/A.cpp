#include <iostream>
#include <vector>
#include <climits>
#define ll long long
using namespace std;

void solve()
{
  int n;
  cin >> n;
  vector<int> m(n, 0);
  for (int i = 0; i < n; i++)
  {
    cin >> m[i];
  }

  int max_so_far = INT_MIN, max_ending_here = 0, max_ele = INT_MIN, ans = 0;

  for (int i = 0; i < n; i++)
  {
    max_ending_here = max_ending_here + m[i];
    max_ele = max(max_ele, m[i]);

    if (max_so_far < max_ending_here)
    {
      max_so_far = max_ending_here;
      ans = max_so_far - max_ele;
    }

    if (max_ending_here < 0)
    {
      max_ending_here = 0;
      max_ele = INT_MIN;
    }
  }

  cout << ans;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}
