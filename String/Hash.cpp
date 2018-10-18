// Credit to RezwanArefin01 for teaching it :)
typedef long long ll;			
const int maxn = 5e3+10;                     // Change bounds

struct Hash {
  ll h[maxn][2], pow[maxn][2], n, b[2] = {(ll)101, (ll)103}, // primes 419, 421, 499
         mod[2] = {(ll)1e9+7, (ll)1e9+9};           //primes 916969619 998244353 1234567891
  hash() {}
  void init(string &str) {
	n = str.size();
	pow[0][0] = pow[0][1] = 1; h[0][0] = h[0][1] = 0;
	for(int i = 1; i <= n; i++) for(int j = 0; j < 2; j++) {  // notice we work with 1 indexed
   	  pow[i][j] = pow[i-1][j] * b[j] % mod[j];
	  h[i][j] = (h[i-1][j] * b[j] + str[i] - 'a' + 1)% mod[j];
	}
  }
  pair<ll,ll> hash(int l, int r) {				   // send 1 indexed values because we do [l - 1]
	ll ret[2];
	for(int i = 0; i < 2; i++) 
	  ret[i] =  (h[r][i] - (pow[r-l+1][i] * h[l-1][i] % mod[i]) + mod[i]) % mod[i];
	  return pair<ll,ll>(ret[0],ret[1]);
  }
}ds;

/* Extra : To avoid hacks in cf one can keep a list of
 * 20 primes for base and mod. Then everytime use : */

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); // use mt19937 for 32 bit only
ll Rand(ll l, ll r) { return uniform_int_distribution<int>(l, r)(rng); }

/* (contd..) Rand(0,19) and get a random prime for base and mod separately.
 * This way the hacker wont know which base and mod value he is up agains :) */