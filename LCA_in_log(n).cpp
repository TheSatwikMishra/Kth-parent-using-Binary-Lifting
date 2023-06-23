/* Author - Satwik Mishra */
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long int ll;
typedef unsigned long long ull;
typedef long double lld;
#define pb                push_back
#define ppb               pop_back
#define pf                push_front
#define ppf               pop_front
#define all(x)            (x).begin(),(x).end()
#define uniq(v)           (v).erase(unique(all(v)),(v).end())
#define sz(x)             (int)((x).size())
#define fr                first
#define sc                second
#define INF               1e18
typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}
ll msb(ll N) {return (64 - __builtin_clzll(N) - 1);}
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.fr); cerr << ","; _print(p.sc); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
inline ll modadd (ll a , ll b , ll mod = (ll)(1e9 + 7)) { return (a + b) - (a + b >= mod ? mod : 0); }
//vector<vector<ll>> adj(2e5 + 100);
//vector<bool> vis(2e5 + 100, 0);
//vector<ll> dis(2e5 + 100, 0);
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
bool is_Ancestor(ll child, ll par, vector<ll> &intime, vector<ll> &outime) {
    return intime[par] < intime[child] && outime[child] < outime[par];
}
void dfs(ll src, ll par, vector<vector<ll>> &adj,
         vector<vector<ll>> &parent, vector<ll> &intime, vector<ll> &outime, ll &global_time) {
    intime[src] = global_time++;
    if (par != -1) parent[0][src] = par;
    for (ll x : adj[src]) {
        if (x != par) dfs(x, src, adj, parent, intime, outime, global_time);
    }
    outime[src] = global_time++;
}
ll kthparent(ll src, ll k, vector<vector<ll>> &par) {
    ll i = 0;
    while (k > 0) {
        if (k % 2) src = par[i][src];
        k /= 2;
        i++;
        if (src == -1) break;
    }
    return src;
}
void precomputationforkthparent(ll N, vector<vector<ll>> &par) {
    for (ll i = 1; i <= log2(N); i++) {
        for (ll j = 1; j <= N; j++) {
            if (par[i - 1][j] != -1) {
                par[i][j] = par[i - 1][par[i - 1][j]];
            }
        }
    }
}
ll lca(ll a, ll b, ll N, vector<vector<ll>> &par, vector<ll> &intime, vector<ll> &outime) {
    if (a == b) {
        return a;
    }
    if (is_Ancestor(a, b, intime, outime)) {
        return b;
    }
    else if (is_Ancestor(b, a, intime, outime)) {
        return a;
    }
    else {
        ll start_bit = log2(N);
        for (ll i = start_bit; i >= 0; i--) {
            ll kth_anc_of_a = par[i][a];
            if (kth_anc_of_a == -1) continue;
            if (!is_Ancestor(b, kth_anc_of_a, intime, outime)) a = kth_anc_of_a;
        }
        return par[0][a];
    }
}
void Jai_shree_ganesh(ll tt) {
    ll N, Q;
    cin >> N >> Q;
    vector<vector<ll>> adj(N + 1);
    for (ll i = 2; i <= N; i++) {
        ll a, b;
        cin >> a;
        adj[a].pb(i);
        adj[i].pb(a);
    }
    vector<vector<ll>> par(log2(N) + 1, vector<ll>(N + 1, -1));
    vector<ll> intime(N + 2, 0);
    vector<ll> outime(N + 2, 0);
    ll global_time = 0;
    dfs(1, -1, adj, par, intime, outime, global_time);
    precomputationforkthparent(N, par);
    while (Q--) {
        ll a, b;
        cin >> a >> b;
        cout << lca(a, b, N, par, intime, outime) << "\n";
    }
}
int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    freopen("Error.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        //cout << "Case #" << t << ": ";
        Jai_shree_ganesh(i);
    }
    return (0);
}