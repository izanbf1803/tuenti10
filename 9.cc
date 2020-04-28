#include <bits/stdc++.h>
using namespace std;

int hex_c(char c) {
    if ('0' <= c and c <= '9') return c - '0';
    if (c == 'A') return 10;
    if (c == 'B') return 11;
    if (c == 'C') return 12;
    if (c == 'D') return 13;
    if (c == 'E') return 14;
    return 15;
}

int parse_hex(string s) {
    int res = 0;
    for (char c : s) {
        res *= 16;
        res += hex_c(c);
    }
    return res;
}

int main() {
    string s1 = "3633363A33353B393038383C363236333635313A353336";
    string msg1 = "514;248;980;347;145;332";
    string key = "";
    int n = s1.size()/2;
    for (int i = 0; i < n; ++i) {
        int v1 = msg1[i];
        int v2 = parse_hex(s1.substr(2*i, 2));
        key.push_back(char(v1 ^ v2));
    }

    string s2 = "3A3A333A333137393D39313C3C3634333431353A37363D";
    n = s2.size()/2;
    string msg2 = "";
    for (int i = 0; i < n; ++i) {
        int v1 = key[i];
        int v2 = parse_hex(s2.substr(2*i, 2));
        msg2.push_back(char(v1 ^ v2));
    }
    cout << msg2 << endl;
}