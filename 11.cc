#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool allowed[101];
ll cache[101][101];
int N;

ll solve(int n, int l) {
    if (n == 0) return 1; // base case

    ll& ans = cache[n][l];
    if (ans == -1) { // not computed yet
        ans = 0;
        for (int i = l; i <= min(n, N-1); ++i) {
            if (allowed[i]) ans += solve(n-i, i);
        }
    }

    return ans;
}

int main() {
    int t;
    cin >> t; cin.ignore();
    for (int tc = 1; tc <= t; ++tc) {
        memset(allowed, true, sizeof(allowed));
        memset(cache, 0xff, sizeof(cache)); // fill cache with -1's
        string line;
        getline(cin, line);
        stringstream ss(line);
        ss >> N;
        int m;
        while (ss >> m) {
            allowed[m] = false;
        }
        cout << "Case #" << tc << ": " << solve(N, 1) << endl;
    }
}