
// TODO: Change vec3 to use point3d from team reference

template<typename vtype>
struct vec3 {
  vec3() { X[0] = X[1] = X[2] = 0; }
  vec3(vtype x, vtype y, vtype z) { X[0] = x; X[1] = y; X[2] = z; }

  /* 3D cross product */
  vec3 operator*(const vec3& v) const {
    return vec3(X[1] * v.X[2] - X[2] * v.X[1],
                X[2] * v.X[0] - X[0] * v.X[2],
                X[0] * v.X[1] - X[1] * v.X[0]);
  }

  vec3 operator-(const vec3& v) const {
    return vec3(X[0] - v.X[0], X[1] - v.X[1], X[2] - v.X[2]);
  }

  vec3 operator+(const vec3& v) const {
    return vec3(X[0] + v.X[0], X[1] + v.X[1], X[2] + v.X[2]);
  }

  vec3 operator-() const {
    return vec3(-X[0], -X[1], -X[2]);
  }

  vec3 operator*(vtype d) const{
	  return vec3(X[0] * d, X[1] * d, X[2] * d);
  }

  vtype dot(const vec3& v) const {
    return X[0] * v.X[0] + X[1] * v.X[1] + X[2] * v.X[2];
  }

  bool operator !=(const vec3 v){
	  return X[0] != v.X[0] || X[1] != v.X[1] || X[2] != v.X[2];
  }

  void print(){
	  cout << X[0] << " " << X[1] << " " << X[2] << endl;
  }

  bool zero(){
	  return abs(X[0]) < eps && abs(X[1]) < eps && abs(X[2]) < eps;
  }

  bool notZero(){
	  return abs(X[0]) > eps || abs(X[1]) > eps || abs(X[2]) > eps;
  }

  vtype X[3];
};

typedef vec3<double> point;

struct face{
	int idx[3];

	face(){}
	face(int i, int j, int k){
		idx[0] = i, idx[1] = j, idx[2] = k;
	}

	int& operator[](int u) { return idx[u]; }
};

vector<point> read(){
	int n; cin >> n;
	vector<point> P(n);

	for (int i = 0; i < n; ++i){
		double x, y, z; cin >> x >> y >> z;
		P[i] = point(x, y, z);
	}

	return P;
}

vector<face> convex_hull( vector<point> &cloud ){
	// bad

	int n = (int)cloud.size();

	point a = cloud[0], b = cloud[1];

	for (int i = 2; i < n; ++i){
		point nr = (b - a) * (cloud[i] - a);

		if (nr.notZero()){
			swap(cloud[i], cloud[2]);
			break;
		}
	}

	point c = (b - a) * (cloud[2] - a);

	for (int i = 3; i < n; ++i){
		if (abs( c.dot( cloud[i] - a ) ) > eps){
			swap(cloud[i], cloud[3]);
			break;
		}
	}

	vector<face> faces;

	function<point(face&)> normal = [&](face &f){
		point a = cloud[ f[1] ] - cloud[ f[0] ];
		point b = cloud[ f[2] ] - cloud[ f[0] ];
		return a * b;
	};

	function<void(int,int,int)> add_face = [&](int x, int y, int z){
		point a = cloud[x] * n, b = cloud[y] * n, c = cloud[z] * n;

		point nr = (b - a) * (c - a);

		for (int i = 0; i < n; ++i){
			point d = cloud[i] - a;

			auto value = d.dot( nr );

			if (abs(value) > eps){
				if (value > 0) swap(y, z);
				break;
			}
		}

		faces.push_back( face(x, y, z) );
	};

	for (int i = 0; i < 4; ++i)
		for (int j = i + 1; j < 4; ++j)
			for (int k = j + 1; k < 4; ++k)
				add_face(i, j, k);

	for (int i = 4; i < n; ++i){
		point x = cloud[i];

		vector<vi> seen(n, vi(n));
		vector<face> next_faces;

		for (auto f : faces){
			if ( (x - cloud[ f[0] ]).dot( normal(f) ) > eps ){
				for (int u = 0; u < 3; ++u)
					for (int v = 0; v < 3; ++v)
						seen[ f[u] ][ f[v] ]++;
			}
			else
				next_faces.push_back( f );

		}

		faces.swap( next_faces );

		for (int j = 0; j < i; ++j)
			for (int k = j + 1; k < i; ++k){
				if (seen[j][k] == 1)
					add_face(i, j, k);
			}
	}

	return faces;
}

int L[ 100 ];

vector<face> convex_hull_slow( vector<point> &cloud ){
	// good O(n^4)

	int n = (int)cloud.size();

	vector<face> faces;

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			for (int k = j + 1; k < n; ++k){

				point a = cloud[i], b = cloud[j], c = cloud[k];
				point nr = (b - a) * (c - a);

				int pnt = 0;
				L[ pnt++ ] = j;
				L[ pnt++ ] = k;

				bool proc = true;

				int v = 0, V = 0;

				for (int l = 0; l < n && proc; ++l){
					if (l == i || l == j || l == k) continue;

					double t = nr.dot( cloud[l] - a );
					if ( abs(t) < eps){
						if (l < k) proc = false;
						else L[ pnt++ ] = l;
					}
					else{
						if (t < 0) v = -1;
						else       V = +1;
					}
				}

				if (!proc || v * V == -1) continue;

//				cout << "tri: " << i << " " << j << " " << k << endl;
//				for (int l = 0; l < pnt; ++l)
//					cout << L[ l ] << " ";
//				cout << endl;

				function<bool(int,int)> compare = [&](int u, int v){
					return nr.dot( (cloud[u] - a) * (cloud[v] - a) ) > 0;
				};

				sort(L, L + pnt, compare);

				for (int l = 0; l + 1 < pnt; ++l)
					faces.push_back( face(i, L[l], L[l + 1]) );
			}

	return faces;
}

void mass_center( vector<point> &cloud, vector<face> &faces ){
	point pivot = cloud[0];

	double x = 0, y = 0, z = 0, v = 0;

	for (auto f : faces){
		auto value = 	( cloud[f[0]] - pivot ).dot(
						( cloud[f[1]] - pivot) * (cloud[f[2]] - pivot)
						);

		point sum = cloud[f[0]] + cloud[f[1]] + cloud[f[2]] + pivot;
		double cvol = abs( 1. * value / 6 );

		v += cvol;

		cvol /= 4;

		x += cvol * sum.X[0];
		y += cvol * sum.X[1];
		z += cvol * sum.X[2];
	}

	x /= v, y /= v, z /= v;

	// Mass center of a polyhedron at (x, y, z)
}
