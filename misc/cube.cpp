
template<class T>
struct cube
{
	T F, U, D, L, R, B;

	void rotX()
	{
		swap(D, B);
		swap(B, U);
		swap(U, F);
	} // FUBD -> DFUB

	void rotY()
	{
		swap(D, R);
		swap(R, U);
		swap(U, L);
	} // LURD -> DLUR

	void rotZ()
	{
		swap(B, R);
		swap(R, F);
		swap(F, L);
	} // LFRB -> BLFR
};
