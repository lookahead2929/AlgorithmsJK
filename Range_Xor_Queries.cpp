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
struct Update {
  int val;
  Update() {
    val = 0;
  }
  Update(int v) {
    val = v;
  }
  void merge(const Update &v) {
    val += v.val;
  }
};
struct Node {
  int sum;
  Node() {
    sum = 0;
  }
  Node(int val) {
    sum = val;
  }
  void merge(const Node &a, const Node &b) {
    sum = a.sum + b.sum;
  }
  void apply(const Update &u, const int32_t L, const int32_t R) {
    sum += (R - L + 1) * u.val;
  }
};
struct SegmentTree {
  int32_t n;
  vector<Node> seg;
  vector<Update> upd;
  vector<bool> lazy;
  SegmentTree(int32_t sz) {
    n = sz;
    seg.resize(1 << (1 + (int32_t)ceil(log2(n))));
    upd.resize(1 << (1 + (int32_t)ceil(log2(n))));
    lazy.resize(1 << (1 + (int32_t)ceil(log2(n))));
  }
  void build(const vector<int> &arr, const int32_t L, const int32_t R, const int32_t index) {
    if (L == R) {
      seg[index] = Node(arr[L]);
      return;
    }
    build(arr, L, (L + R) >> 1, index << 1);
    build(arr, ((L + R) >> 1) + 1, R, index << 1 | 1);
    seg[index].merge(seg[index << 1], seg[index << 1 | 1]);
  }
  void apply(const int32_t L, const int32_t R, const int32_t index, const Update &U) {
    if (L != R) {
      lazy[index] = true;
      upd[index].merge(U);
    }
    seg[index].apply(U, L, R);
  }
  void propagate(const int32_t L, const int32_t R, const int32_t index) {
    if (!lazy[index]) {
      return;
    }
    apply(L, (L + R) >> 1, index << 1, upd[index]);
    apply(((L + R) >> 1) + 1, R, index << 1 | 1, upd[index]);
    upd[index] = Update();
    lazy[index] = false;
  }
  void update(const int32_t l, const int32_t r, const int32_t L, const int32_t R, const int32_t index, const Update &U) {
    if (r < L || l > R) {
      return;
    }
    if (l <= L && R <= r) {
      apply(L, R, index, U);
      return;
    }
    propagate(L, R, index);
    update(l, r, L, (L + R) >> 1, index << 1, U);
    update(l, r, ((L + R) >> 1) + 1, R, index << 1 | 1, U);
    seg[index].merge(seg[index << 1], seg[index << 1 | 1]);
  }
  Node query(const int32_t l, const int32_t r, const int32_t L, const int32_t R, const int32_t index) {
    if (r < L || l > R) {
      return Node();
    }
    propagate(L, R, index);
    if (l <= L && R <= r) {
      return seg[index];
    }
    Node x = query(l, r, L, (L + R) >> 1, index << 1), y = query(l, r, ((L + R) >> 1) + 1, R, index << 1 | 1), z;
    z.merge(x, y);
    return z;
  }
  /* ------------- API ------------- */
  void build(const vector<int> &arr) {
    build(arr, 0, n - 1, 1);
  }
  void update(const int32_t l, const int32_t r, const Update &U) {
    update(l, r, 0, n - 1, 1, U);
  }
  Node query(const int32_t l, const int32_t r) {
    return query(l, r, 0, n - 1, 1);
  }
};
void solve()
{
    int n;
    cin>>n;
    int m;
    cin>>m;
    vi a(n);
    rep(i,0,n) cin>>a[i];
    SegmentTree st(n);
    st.build(a);
    rep(i,0,m)
    {
        int q;
        cin>>q;
        if(q==2)
        {
            int x,y,v;
            cin>>x;
            cout<<st.query(x-1,x-1).sum<<endl;
            
            //cout<<query(x-1,x)<<endl;
        }
        else
        {
            int x,y,v;
            cin>>x>>y>>v;
            
            st.update(x-1,y-1,v);
            // rep(i,0,n) cout<<tree[i+n]<<" ";
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

