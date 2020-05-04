#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

// https://cp-algorithms.com/graph/dinic.html
struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        int F, G;
        cin >> F >> G;
        /*
            Flow graph nodes (a total of G+F+2 nodes):

            nodes (G) 0..G-1   :  employee groups
            nodes (F) G..G+F-1 :  floors
            s : G+F
            t : G+F+1            
        */
        int n = G+F+2;
        int s = G+F;
        int t = G+F+1;

        Dinic dinic(n, s, t);

        int Ei_sum = 0;

        for (int i = 0; i < G; ++i) {
            int Ei, Ni;
            cin >> Ei >> Ni;

            Ei_sum += Ei;

            dinic.add_edge(s, i, Ei);

            int floor;
            for (int j = 0; j < Ni; ++j) {
                cin >> floor;
                dinic.add_edge(i, G+floor, Ei);
            }
        }

        vector<FlowEdge> edges_copy = dinic.edges;
        vector<vector<int>> adj_copy = dinic.adj;
        int m_copy = dinic.m;

        int l = 0;
        int r = 1000000;
        int ans = -1;
        while (l <= r) { // binary search optimal capacity for floor (number of wc's)
            int cap = (l+r)/2;
            dinic.edges = edges_copy;
            dinic.adj = adj_copy;
            dinic.m = m_copy;
            for (int floor = 0; floor < F; ++floor) {
                dinic.add_edge(G+floor, t, cap);
            }
            if (dinic.flow() == Ei_sum) {
                ans = cap;
                r = cap-1;
            }
            else {
                l = cap+1;
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }    
}
