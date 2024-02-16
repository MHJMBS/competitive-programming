#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio ios::sync_with_stdio(0), cin.tie(nullptr)

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using tiii = tuple<int,int,int>;
using tlll = tuple<ll,ll,ll>;

using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;

vector<vector<int>> adjacencies;
vector<int> v, tin, eulerTour, subtreeSize;

struct SegmentTree {
    vector<ll> seg;
    int leafsBegin;
    int leafsCount;

    SegmentTree(vector<int>& v) {
        leafsCount = 1;
        while(leafsCount < v.size()) leafsCount *= 2;
        seg.resize(2*leafsCount-1, 0);
        leafsBegin = seg.size() - leafsCount;

        for(int i = 0; i < v.size(); i++) {
            seg[leafsBegin+i] = v[i];
        }

        for(int i = leafsBegin-1; i >= 0; i--) {
            seg[i] = seg[2*i+1] + seg[2*i+2];
        }
    }

    void upd(int i, ll val) {
        i = leafsBegin+i;
        seg[i] = val;

        while(i > 0) {
            i = (i-1)/2;
            seg[i] = seg[2*i+1] + seg[2*i+2];
        }
    }

    ll query(int l, int r) {
        return query(l, r, 0, leafsCount-1, 0);
    }

    ll query(int l, int r, int lx, int rx, int i) {
        if(rx < l || r < lx) return 0;
        if(l <= lx && rx <= r) return seg[i];
        int mid = (lx+rx)/2;
        return query(l, r, lx, mid, 2*i+1) + query(l, r, mid+1, rx, 2*i+2);
    }
};

void dfs(int node, int parent) {
    static int t = 0;
    tin[node] = t++;
    eulerTour[tin[node]] = node;

    subtreeSize[node] = 1;

    for(int adj : adjacencies[node]) {
        if(adj == parent) continue;
        dfs(adj, node);
        subtreeSize[node] += subtreeSize[adj];
    }
}

int main() {
    fastio;

    int n, q;
    cin >> n >> q;

    v.resize(n+1);
    for(int i = 1; i <= n; i++) cin >> v[i];

    adjacencies.resize(n+1);
    for(int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adjacencies[u].push_back(v);
        adjacencies[v].push_back(u);
    }

    tin.resize(n+1);
    eulerTour.resize(n);
    subtreeSize.resize(n+1);

    dfs(1, -1);

    vector<int> newV(n);
    for(int i = 1; i <= n; i++) newV[tin[i]] = v[i];

    SegmentTree seg(newV);

    while(q--) {
        int tq;
        cin >> tq;

        if(tq == 1) {
            int s, x;
            cin >> s >> x;
            seg.upd(tin[s], x);
        }else {
            int s;
            cin >> s;
            cout << seg.query(tin[s], tin[s]+subtreeSize[s]-1) << '\n';
        }
    }
}