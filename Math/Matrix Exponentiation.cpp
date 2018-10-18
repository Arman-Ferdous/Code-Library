typedef long long ll;
const int D = 10;      // set dimension size
const int mod = 1e9+7; // set mod value

struct Matrix{
  int d, v[D][D];
  Matrix(int _d = 0) {
	d = _d;
	memset(v,0,sizeof v);
  }
  void Identity() {
	for(int i = 0; i < d; ++i)
	  for(int j = 0; j < d; ++j)
		v[i][j] = (i==j);
  }
  Matrix operator *(Matrix b) const {
	Matrix ret(d);
	for(int i = 0; i < d; ++i)
	  for(int j = 0; j < d; ++j)
		for(int k = 0; k < d; ++k)
		  ret.v[i][j] = (ret.v[i][j] + (ll)v[k][i] * b.v[j][k]) % mod;
	return ret;
  }
  Matrix pow(int n) {
	Matrix b = *this;
	Matrix ret(d); ret.Identity();
	for(; n; n >>= 1, b = b*b)
	  if(n&1) ret = ret * b;
	  return ret; 
  }
};
/* do: [dp] x [matrix] = [new dp]
my multiplication style is not the used one
I like to write [dp] first then figure out [matrix]
so I follow this style :
|a b|\/|e f|--|ae+cf be+df|
|c d|/\|g h|--|ag+ch bg+dh|
*/