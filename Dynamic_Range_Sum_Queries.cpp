#include<bits/stdc++.h>
#include<math.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back 
#define int long long int 
typedef unsigned long long ull;
#define mod 1000000007LL
#define xx first
#define yy second
#define codec ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(0);;
typedef vector<int> vi;
#define deb(x) cout<<#x<<" "<<x<<endl;
#define all(t) (t).begin(),(t).end()
typedef pair<int, int> pi;
#define pie 3.1415926535
#define output(x) cout << ( x ? "Yes" : "No" ) << '\n' ;
bool sortbysec(const pair<int,int> &a,const pair<int,int> &b) 
{ 
   if(a.yy== b.yy) return a.xx<b.xx;
    return (a.second < b.second);
} 
int tt=1;
const int N = 200005; 
  
int n; // array size
  
// Max size of tree
int tree[2 * N];
  
// function to build the tree
void build(vi arr) 
{ 
    // insert leaf nodes in tree
    for (int i=0; i<n; i++)    
        tree[n+i] = arr[i];
      
    // build the tree by calculating parents
    for (int i = n - 1; i > 0; --i)     
        tree[i] = tree[i<<1] + tree[i<<1 | 1];    
}
  
// function to update a tree node
void updateTreeNode(int p, int value) 
{ 
    // set value at position p
    tree[p+n] = value;
    p = p+n;
      
    // move upward and update parents
    for (int i=p; i > 1; i >>= 1)
        tree[i>>1] = tree[i] + tree[i^1];
}
  
// function to get sum on interval [l, r)
int query(int l, int r) 
{ 
    int res = 0;
      
    // loop to find the sum in the range
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l&1) 
            res += tree[l++];
      
        if (r&1) 
            res += tree[--r];
    }
      
    return res;
}
void solve()
{
   // int n;
    cin>>n;
    int m;
    cin>>m;
    vi a(n);
    rep(i,0,n) cin>>a[i];
    build(a);
    rep(i,0,m)
    {
        int q;
        cin>>q;
        if(q==2)
        {
            int x,y;
            cin>>x>>y;
            cout<<query(x-1,y)<<endl;
        }
        else
        {
            int x,y;
            cin>>x>>y;
            updateTreeNode(x-1,y);
        }
        
    }



}

signed main()
{
    codec;
    int t=1;
//   freopen("input.txt","r",stdin);
//   freopen("input.txt","w",stdout);
   //cin>>t;
   cout<<fixed<<setprecision(8);
       while(t--)
    {
        solve();
        tt++;
    }
}