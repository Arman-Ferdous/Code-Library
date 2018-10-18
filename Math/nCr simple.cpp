typedef long long ll;
const int maxn = 1e5, mod = 1e9+7;

ll egcd(ll a, ll b, ll &x, ll &y) {
  if(!a) { x = 0, y = 1; return b; }
  ll _x, _y, g = egcd(b%a,a,_x,_y);
  x = _y - (b/a) *  _x; y = _x;
  return g;
}
// we can also use n ^ (m - 2) % m [when m is prime]
// or, n ^ ( phi(m) - 1 ) % m  [when m is not prime]
ll modinv(ll n, ll m) {   
  ll inv, del;
  ll g = egcd(n,m,inv,del);
  return (inv + m)%m;
}

ll fact[maxn], inv[maxn];
ll ncr(int n, int r) {
  if(n < r) return 0;
  return fact[n] * (inv[r] * inv[n-r] % mod) % mod;
}

int main() { // pre-process
  fact[0] = 1;
  for(int i = 1; i < maxn; i++)
	  fact[i] = fact[i-1] * i % mod;
  inv[maxn-1] = modinv(fact[maxn-1],mod);
  for(int i = maxn-2; i >= 0; i--)
	  inv[i] = inv[i+1] * (i+1) % mod;
  // ^^ faster and easier than using modinv(fact[i], mod) everytime
}