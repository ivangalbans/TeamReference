const int
	MaxN = 10000;

int n, m;
int g[MaxN][MaxN];
int dist[MaxN][MaxN];

void Floyd_Warshall()
{
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int init()
{
	REP(i, n)	REP(j, n)
	{
		if(dist[i][j] == 0)
		{
			dist[i][j] = oo;
			g[i][j] = oo;
		}
	}

	for(int i = 0; i < n; ++i)
		dist[i][i] = 0;
}
