#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio ios::sync_with_stdio(0), cin.tie(nullptr)

using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using tiii = tuple<int,int,int>;
using tlll = tuple<ll,ll,ll>;

using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());



int main() {
    fastio;

    int t;
    cin >> t;

    while(t--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        for(int& ai : a) cin >> ai;

        map<int,int> freq;
        for(int ai : a) freq[ai]++;

        vector<pii> freqa;
        for(auto [ai,f] : freq) {
            freqa.push_back({f,ai});
        }

        sort(freqa.begin(), freqa.end());

        freqa.pop_back();
    
        int ans = freq.size();

        for(auto [f, ai] : freqa) {
            if(k < f) break;
            k -= f;
            ans--;
        }

        cout << ans << '\n';
    }
}