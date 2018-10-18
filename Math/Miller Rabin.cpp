typedef long long ll;
ll bigsum(ll a, ll b, ll m) {
  ll ret = 0, p = a%m;
  while(b) {
    if(b&1) ret = (ret + p) % m;
    p = (p<<1) % m, b >>= 1;
  } return ret % m;
} 
ll bigmod(ll a, ll b, ll m) {
  ll ret = 1, p = a;
  while(b) {
    if(b & 1) ret = bigsum(ret,p,m);
    p = bigsum(p,p,m), b >>= 1;
  } return ret % m;
}
bool Miller(ll p) {
  if(p < 2) return false;
  if(p != 2 && ~p&1) return false;
  ll d = p - 1;
  while(~d&1) d >>= 1;
  for(int i = 0; i < 10; i++) { // about 8-10 tests are good enough
    ll a = rand()%(p-1)+1, temp = d;
    ll mod = bigmod(a,temp,p);
    while(temp != p-1 && mod != 1 && mod != p-1)
      mod = bigsum(mod,mod,p), temp <<= 1; // try to avoid bigsum()
    if(mod != p-1 && ~temp&1)
      return false;
  } return true;
}