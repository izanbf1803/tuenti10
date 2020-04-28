#include <bits/stdc++.h>
using namespace std;

map<int,int> parent; // representation of disjoint set

int find(int u) { // find set u belongs to
    if (parent[u] != u) parent[u] = find(parent[u]); // path compression
    return parent[u];
}

void join(int u, int v) { // join sets of u and v, keeping the set of u as parent
    u = find(u);  
    v = find(v);
    parent[v] = u;
}

int main() {
    int c;
    cin >> c;
    for (int tc = 1; tc <= c; ++tc) {
        parent.clear();
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int a, b, res;
            cin >> a >> b >> res;
            if (not parent.count(a)) parent[a] = a;
            if (not parent.count(b)) parent[b] = b;
            if (res == 1) {
                join(a, b);
            }
            else {
                join(b, a);
            }
        }
        for (auto it : parent) { // if there exists unique solution then this player is it's own parent
            if (find(it.first) == it.first) {
                cout << "Case #" << tc << ": " << it.first << endl;
            }
        }
    }
}