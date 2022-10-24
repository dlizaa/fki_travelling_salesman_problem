#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#define INF 30000000
#define N 19000
using namespace std;

int get_matrix(int n, double **m)
{
	int i, j;
	double *x, *y;
	long long int t = time(NULL);
	x = new double[n];
	y = new double[n];
	for (i = 0; i < n; i++)
	{
		cin >> x[i];
		cin >> y[i];
		if (time(NULL) > t + 60)
		{
			cout << "OOOPS" << endl;
			return -1;
		}
	}
//	cout << time(NULL) << endl;
	for (i = 0; i < n; i++)
	{
		if (time(NULL) > t + 60)
		{
			cout << "OOOPS" << endl;
			return -1;
		}
		m[i][i] = INF;
		for (j = i + 1; j < n; j++)
		{
			m[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			m[j][i] = m[i][j];
		}
	}
	return 0;
}

double start(int n, double **m, long int *order)
{
	int i, j, n_been = 2, nmn = 1, nmnbeen, *been;
	double len = INF, new_len;
	vector <int> v_been, v_not_been;
	long long int t = time(NULL);
//	cout << t << endl;
	been = new int[n];
	for (i = 0; i < n; i++)
		been[i] = 0;
	order[0] = 0;
	for (i = 1; i < n; i++)
		if (m[order[0]][i] < m[order[0]][nmn])
			nmn = i;
	order[1] = nmn;
	been[order[0]] = 0;
	been[order[1]] = 1;
	len = m[order[0]][order[1]];
	v_been.push_back(order[0]);
	v_been.push_back(order[1]);
	for (i = 0; i < n; i++)
		if (i != order[0] && i != order[1])
			v_not_been.push_back(i);
//	cout << n_been << "------------" << endl;
	while (n_been < n)
	{
		if (time(NULL) > 60 + t)
			return -1;
		nmn = order[n_been - 1];
//		nmn = 0;
//		cout << n_been << "------------" << endl;
		for (i = 1; i < v_not_been.size(); i++)
			if (m[order[n_been - 1]][i] < m[order[n_been - 1]][nmn] && been[i] == 0)
				nmn = i;
//		j = v_not_been[nmn];
//		v_not_been[nmn] = v_not_been[v_not_been.size() - 1];
//		v_not_been.pop_back();
//		nmn = j;
		nmnbeen = nmn;
//		cout << n_been << "------------" << endl;
		for (i = 1; i < n; i++)
		{
//			cout << i << endl;
			if (m[nmn][i] < m[nmn][nmnbeen] && been[i] > 0)
				nmnbeen = i;
		}
//		cout << n_been << "------------" << nmn << " " << nmnbeen << endl;
		new_len = len + m[nmnbeen][nmn] + m[nmn][order[been[nmnbeen]]] - m[nmnbeen][order[been[nmnbeen] - 2]];
		if (new_len < len + m[nmn][order[n_been - 1]] && new_len > 0)
		{
//			cout << n_been << "------------" << endl;
			for (i = n_been; i > been[nmnbeen]; i--)
			{
				order[i] = order[i - 1];
				been[order[i - 1]]++;
			}
			order[been[nmnbeen]] = nmn;
			n_been++;
			been[nmnbeen] = n_been;
			len = new_len;
		}
		else
		{	
			order[n_been] = nmn;
			len += m[nmn][order[n_been - 1]];
			n_been++;
			been[nmn] = n_been;
//			cout << n_been << "----+++-----" << order[n_been] << endl;
		}
//		cout << n_been << "------------" << endl;
//		for (i = 0; i < n; i++)
//			cout << been[i] << " ";
//		cout << endl;
//		cout << len << "------------" << endl;
//		for (i = 0; i < n; i++)
//			cout << order[i] << " ";
//		cout << endl;
	}
//	cout << n_been << "------------" << endl;
	len += m[order[n - 1]][order[0]];
	return len;
}

int main()
{
	int n, all, i, j;
	long int *order;
	double **m, len = 0;
	cin >> n;
	all = n;
	while (all > 0)
	{
		n = min(N, all);
		m = new double*[n];
		for (i = 0; i < n; i++)
			m[i] = new double[n];
		if (get_matrix(n, m) == -1)
			return 0;
		order = new long int[n];
		len += start(n, m, order);
		all -= n;
//		cout << time(NULL) << endl;
	}
	cout << len << endl;
//	for (i = 0; i < n; i++)
//	{
//		for (j = 0; j < n; j++)
//			cout << m[i][j] << " ";
//		cout << endl;
//	}
	return 0;
}

/*int findcheapest(int n, double **d, int i, int mask)
{
	int j;
	if (d[i][mask] != INF)
		return d[i][mask];
	for (j = 0; j < n; j++)
		; 
}

long long int find_m_mask(int n, bool *mask)
{
	int m_mask = 0, i, pw_base = 1;
	for (i = 0; i < pow(2, n); i++)
	{
		m_mask += pw_base * mask[i];
		pw_base *= 2;
	}
	return m_mask;
}

int main()
{
	int n = 10, i;
       	long long int m_mask, ninpw;
	double **d;
	bool *mask;
	d = new double*[n];
	cout << "111" << endl;
	ninpw = pow(2, n);
	cout << ninpw << endl;
	for (i = 0; i < n; i++)
		d[i] = new double[ninpw];
	cout << "111" << endl;
	cout << pow(2, n) << endl;
	cout << "111" << endl;
	mask = new bool[ninpw];
	cout << "111" << endl;
	for (i = 0; i < pow(2, n); i++)
		mask[i] = 1;
	m_mask = find_m_mask(n, mask);
	cout << m_mask << endl;
	d[0][m_mask] = 2;
	cout << d[0][m_mask] << endl;
	return 0;
}*/
