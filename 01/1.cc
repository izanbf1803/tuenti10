#include <bits/stdc++.h>
using namespace std;

int main() {
    map<char,char> beats;
    beats['S'] = 'P';
    beats['P'] = 'R';
    beats['R'] = 'S';
    int n;
    cin >> n;
    for (int tc = 1; tc <= n; ++tc) {
        char l, r;
        cin >> l >> r;
        cout << "Case #" << tc << ": ";
        if (l == r) {
            cout << '-' << endl;
        }
        else if (beats[l] == r) {
            cout << l << endl;
        }
        else {
            cout << r << endl;
        }
    }
}