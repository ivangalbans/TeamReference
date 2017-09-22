/*
	Check wether there is a point in the intersection of
	several semi-planes. if p lies in the border of some
	semiplane it is considered to belong to the semiplane.

	Expected Running time: linear

	Tested on Triathlon [Cuban Campament Contest]
*/

bool intersect( vector<line> semiplane ){

	function<bool(line&,point&)> side = [](line &l, point &p){
		// IMPORTANT: point p belongs to semiplane defined by l
		// iff p it's clockwise respect to segment < l.p, l.q >
		// i.e. (non negative cross product)

		return cross( l.q - l.p, p - l.p ) >= 0;
	};

	function<bool(line&, line&, point&)> crosspoint = [](const line &l, const line &m, point &x){
		double A = cross(l.q - l.p, m.q - m.p);
		double B = cross(l.q - l.p, l.q - m.p);
		if (abs(A) < eps) return false;
		x = m.p + B / A * (m.q - m.p);
		return true;
	};

	int n = (int)semiplane.size();

	random_shuffle( semiplane.begin(), semiplane.end() );

	point cent(0, 1e9);

	for (int i = 0; i < n; ++i){
		line &S = semiplane[ i ];

		if (side(S, cent)) continue;

		point d = S.q - S.p; d /= abs( d );

		point A = S.p - d * 1e8, B = S.p + d * 1e8;

		for (int j = 0; j < i; ++j){
			point x;
			line &T = semiplane[j];

			if ( crosspoint(T, S, x) ){
				int cnt = 0;


				if (!side(T, A)){
					A = x;
					cnt++;
				}

				if (!side(T, B)){
					B = x;
					cnt++;
				}

				if (cnt == 2)
					return false;
			}
			else{
				if (!side(T, A)) return false;
			}
		}

		if (imag(B) > imag(A)) swap(A, B);
		cent = A;
	}

	return true;
}
