#include <bits/stdc++.h>
using namespace std;
#include "debug.h" ///////////

const int INF = 5000;

vector<string> split(const string& s, char sep) {
    string curr = "";
    vector<string> res;
    for (char c : s) {
        if (c == sep) {
            res.push_back(curr);
            curr = "";
        }
        else {
            curr.push_back(c);
        }
    }
    res.push_back(curr);
    return res;
}

string join(const vector<string>& v, char sep) {
    string res = "";
    for (const string& s : v) {
        if (not s.empty()) res.push_back(sep);
        res += s;
    }
    return res;
}

string substr(const string& s, int l, int r) {
    return s.substr(l, r-l+1);
}

string replace_first(string s, char ch, char rep) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it == ch) {
            *it = rep;
            return s;
        }
    }
    return s;
}

string replace_last(string s, char ch, char rep) {
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        if (*it == ch) {
            *it = rep;
            return s;
        }
    }
    return s;
}

int diff(const string& s, const string& t) {
    assert(s.size() == t.size());
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) ++cnt;
    }
    return cnt;
}

int count(const string& s, char ch) {
    int cnt = 0;
    for (char c : s) {
        if (c == ch) ++cnt;
    }
    return cnt;
}

int n_lines(const string& s) {
    return count(s, '#') + 1;
}

bool valid_ESC(const string& s) {
    bool comma = false;
    for (char c : s) {
        if (c == ',') {
            comma = true;
        }
        else if (c == '#') {
            if (not comma) return false;
            comma = false;
        }
    }
    return comma;
}

int solve_ESC(string s) {
    int n = s.size();

    if (n <= 2) return INF;

    if (s[0] != '[') {
        s[0] = '[';
        s[n-1] = ']';
        return 2 + solve_ESC(s);
    }

    int m = n_lines(s);

    if (m == 1) {
        if (count(s, 'a') == 0) return INF;
        return 1;
    }
    else { // m > 1
        vector<string> lines = split(s, '#');
        int cnt = 0;
        bool last_erased_newline = false;
        for (int i = 0; i < m; ++i) {
            if (last_erased_newline) {
                last_erased_newline = false;
            }
            else {
                if (count(lines[i], ',')) {
                    last_erased_newline = false;
                }
                else {
                    last_erased_newline = true;
                    ++cnt;
                }
            }
        }
        return cnt;
    }
}

bool valid_LOLMAO(const string& s, bool check_envelope=true) {
    if (s.empty()) return true;
    if (count(s, '[') + count(s, ']') + count(s, ',') == 0) return true;

    int n = s.size();

    if (check_envelope) {
        if (s[0] != '[' or s[n-1] != ']') return false;
    }

    vector<string> elems;

    string curr = "";
    int open = 0;

    int l = 0;
    int r = n-1;

    if (check_envelope) {
        ++l;
        --r;
    }

    for (int i = l; i <= r; ++i) {
        char c = s[i];
        if (c == ',' and open == 0) {
            elems.push_back(curr);
            curr = "";
        }
        else {
            curr.push_back(c);
            if (c == '[') {
                ++open;
            }
            else if (c == ']') {
                if (open == 0) return false;
                --open;
            }
        }
    }
    elems.push_back(curr);

    if (open != 0) return false;
 
    for (const string& elem : elems) {
        if (not valid_LOLMAO(elem)) return false;
    }

    return true;
}

int dp[400][400][2][2];

int solve_LOLMAO_aux(const string& s, int l, int r, bool comma_l, bool comma_r) {
    int& ans = dp[l][r][comma_l][comma_r];
    if (ans != -1) return ans; // already computed

    ans = INF;

    if (l > r)
        return ans = ((comma_l or comma_r) ? 0 : INF);
    if (l == r) {
        char c = s[l];
        if (c != '[' and c != ']' and (comma_l or comma_r or c == ','))
            return ans = 0;
        return ans = 1;
    }
    if (valid_LOLMAO(substr(s, l, r), false) and valid_ESC(s.substr(l, r-l+1))) 
        return ans = 0;

    if (s[l] == '[' and s[r] == ']')
        ans = min(ans, solve_LOLMAO_aux(s, l+1, r-1, comma_l, comma_r));

    if (s[l] == ',') {
        ans = min(ans, solve_LOLMAO_aux(s, l+1, r, true, comma_r));
    }
    else if (s[l] == ']') {
        ans = min(ans, 1 + solve_LOLMAO_aux(s, l+1, r, true, comma_r)); // ] => ,

        for (int i = l+1; i <= r; ++i) { // s[i] => [, s[i] => ]
            if (s[i] == ',') continue;
            int cost = 1;
            if (s[i] != ']') ++cost;
            if (i < r and s[i+1] != ',') ++cost; // s[i+1] => ,

            if (count(substr(s, l+1, r), '#')) {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, comma_l, i < r) 
                                    + solve_LOLMAO_aux(s, i+2, r, true, comma_r));
            }
            else {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, true, i < r or comma_r) 
                                    + solve_LOLMAO_aux(s, i+2, r, true, i < r or comma_r));
            }

        }
    }
    else if (s[l] == '[') {
        ans = min(ans, 1 + solve_LOLMAO_aux(s, l+1, r, true, comma_r)); // [ => ,

        for (int i = l+1; i <= r; ++i) { // s[i] => ]
            if (s[i] == ',') continue;
            int cost = 0;
            if (s[i] != ']') ++cost;
            if (i < r and s[i+1] != ',') ++cost; // s[i+1] => ,

            if (count(substr(s, l+1, r), '#')) {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, comma_l, i < r) 
                                + solve_LOLMAO_aux(s, i+2, r, true, comma_r));
            }
            else {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, true, i < r or comma_r) 
                                + solve_LOLMAO_aux(s, i+2, r, true, i < r or comma_r));
            }
        }
    }
    else if (s[l] == 'a') {
        if (s[l+1] != '[' and s[l+1] != ']') {
            ans = min(ans, solve_LOLMAO_aux(s, l+1, r, comma_l, comma_r));
        }
        else {
            ans = min(ans, 1 + solve_LOLMAO_aux(s, l+2, r, true, comma_r)); // s[l+1] => ,
        }

        ans = min(ans, 1 + solve_LOLMAO_aux(s, l+1, r, true, comma_r)); // s[l] => ,

        for (int i = l+1; i <= r; ++i) { // s[l] => [, s[i] => ]
            if (s[i] == ',') continue;
            int cost = 1;
            if (s[i] != ']') ++cost;
            if (i < r and s[i+1] != ',') ++cost; // s[i+1] => ,

            if (count(substr(s, l+1, r), '#')) {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, comma_l, i < r)
                                + solve_LOLMAO_aux(s, i+2, r, true, comma_r));
            }
            else {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, true, i < r or comma_r)
                                + solve_LOLMAO_aux(s, i+2, r, true, i < r or comma_r));
            }
        }
    }
    else { // s[l] == #
        if (s[l+1] != '[' and s[l+1] != ']') {
            if (comma_l)
                ans = min(ans, solve_LOLMAO_aux(s, l+1, r, false, comma_r));
        }
        else {
            ans = min(ans, 1 + solve_LOLMAO_aux(s, l+2, r, true, comma_r)); // s[l+1] => ,
        }

        ans = min(ans, 1 + solve_LOLMAO_aux(s, l+1, r, true, comma_r)); // s[l] => ,

        for (int i = l+1; i <= r; ++i) { // s[l] => [, s[i] => ]
            if (s[i] == ',') continue;
            int cost = 1;
            if (s[i] != ']') ++cost;
            if (i < r and s[i+1] != ',') ++cost; // s[i+1] => ,

            if (count(substr(s, l+1, r), '#')) {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, comma_l, i < r)
                                    + solve_LOLMAO_aux(s, i+2, r, true, comma_r));
            }
            else {
                ans = min(ans, cost + solve_LOLMAO_aux(s, l+1, i-1, true, i < r or comma_r)
                                    + solve_LOLMAO_aux(s, i+2, r, true, i < r or comma_r));
            }
        }
    }

    return ans;
}

int solve_LOLMAO(string s) {
    if (valid_LOLMAO(s)) return 0;

    string s0 = s;

    int n = s.size();

    if (n < 2) return INF;

    int ans = INF;

    s[0] = '[';
    s[n-1] = ']';

    memset(dp, 0xff, sizeof(dp)); // fill dp with -1
    ans = min(ans, diff(s0, s) + solve_LOLMAO_aux(s, 1, n-2, false, false));

    return ans;
}


int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        int L;
        cin >> L;
        cin.ignore();
        string S;
        for (int l = 0; l < L; ++l) {
            string line;
            getline(cin, line);
            if (l > 0) S.push_back('#'); // line break representation
            for (char c : line) {
                if (c != '[' and c != ']' and c != ',')
                    S.push_back('a');
                else
                    S.push_back(c);
            }
        }
        bool ESC = valid_ESC(S);
        bool LOLMAO = valid_LOLMAO(S);
        int ans = INF;
        if (ESC and LOLMAO) {
            ans = 0;
        }
        else {
            if (ESC) {
                // make it valid LOLMAO
                ans = solve_LOLMAO(S);
            }
            else {
                // make it valid ESC
                ans = solve_ESC(S);
            }
        }
        if (ans >= INF)
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        else
            cout << "Case #" << tc << ": " << ans << endl;
    }
}