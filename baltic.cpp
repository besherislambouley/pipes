/*
 * there are just to cases n = m & m = n -1 ( tree, tree+cycle ) , its easy to solve the tree case , the n = m case you can solve it for all thenodes
 * then you will be left with one cycle if it is even lenght then there is no anwer , otherwise you can fill the answer easily for one cycle 
 * 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
        #include <bits/stdc++.h>
        using namespace std;
        #define sqr 340
        #define mid (l+r)/2
        #define pb push_back
        #define ppb pop_back
        #define fi first
        #define se second
        #define lb lower_bound
        #define ub upper_bound
        #define ins insert
        #define era erase
        #define C continue
        #define mem(dp,i) memset(dp,i,sizeof(dp))
        #define mset multiset
        typedef long long ll;
        typedef short int si;
        typedef long double ld;
        typedef pair<int,int> pi;
        typedef pair<ll,ll> pll;
        typedef vector<int> vi;
        typedef vector<ll> vll;
        typedef vector<pi> vpi;
        typedef vector<pll> vpll;
        const ll inf=1e18;
        const ld pai=acos(-1);
        int n , m , start ;
        vpi v[100009];
        ll a[100009] , deg[100009] , ans[100009] , done[100009];
        ll sum ( int node ) {
                done [ node ] = 1 ;
                ll ret = 0 ;
                for ( auto u : v[node] ) {
                        if ( done [u.fi] ) C ;
                        ret = sum ( u.fi ) ;
                        break ;
                }
                done [ node ] = 0 ;
                return ret + a[node] ;
        }
        ll go ( int node , ll p ) {
                done [ node ] = 1 ;
                ll ret = 0 ;
                for ( auto u : v[node] ) {
                        if ( done [u.fi] ) C ;
                        ret = go ( u.fi , a[ u.fi ] - p ) ;
                        break ;
                }
                done [ node ] = 0 ;
                return ret + p ;
        }
        void solve ( int node ) {
                done [node] = 1 ;
                ll out = 0 ;
                for ( auto u : v[node] ) {
                        if ( done [u.fi] ) C ;
                        a [ u.fi ] -= a[node] ;
                        ans [ u.se ] = a[node];
                        solve( u.fi ) ;
                        out = 1 ;
                        break;
                }
                if ( !out ) {
                        for ( auto u :v[node] ) {
                                if ( u.fi == start ) {
                                        ans [ u.se ] = a[ node ];
                                        break ;
                                }
                        }
                }
          		done [ node ] = 0 ;
        }
        int main () {
                cin >> n >> m ;
                for ( int i = 0 ; i < n ; i ++ ) cin >> a[i] ;
                for ( int i = 0 ; i < m ; i ++ ) {
                        int a , b ;
                        cin >> a >> b ;
                        a -- , b -- ;
                        v[a] .pb ( { b , i } ) ;
                        v[b] .pb ( { a , i } ) ;
                }
                if ( m > n ) cout << 0 << endl , exit ( 0 ) ;
                queue <int> q ;
                for ( int i = 0 ; i < n ; i ++ ) {
                        deg[i] = v[i].size() ;
                        if ( deg[i] == 1 ) q.push ( i ) ;
                }
                int N = n ;
                while ( q.size() ) {
                        N -- ;
                        int node = q.front () ;
                        q.pop () ;
                        done [ node ] = 1 ;
                        for ( auto U : v [node] ) {
                                int u = U.fi ;
                                int id= U.se ;
                                if ( done [u] ) C ;
                                ans [id] = a [node] ;
                                a [u] -= ans [id] ;
                                deg[u] -- ;
                                if ( deg [u] == 1 ) q.push ( u ) ;
                        }
                }
                if ( N && N%2==0 ) cout << 0 << endl , exit ( 0 ) ;
                for ( int i = 0 ; i < n ; i ++ ) {
                        if ( done [i] ) C ;
                        start = i ;
                        ll all = sum ( i ) / 2 ;
                        ll ret = go ( i , 0 ) ;
                        a [ start ] = all - ret ; ;
                        solve ( i ) ;
                        break ;
                }
                for ( int i = 0 ; i < m ; i ++ ) cout << ans [i] *2ll << endl ;
        }
