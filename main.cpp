#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <malloc.h>
#include <fcntl.h>
#define INF 30000

using namespace std;

struct edge
{
    int first;
    int second;
    double cost;
};

struct edge *input_data(struct edge *e, int n, double *x1, double *y1, vector <double> *xs, vector <double> *ys)
{
	int i, j, cur = 0;
	double *x, *y;
//	cout << n << "(((((((((" << endl;
	x = new double[n];
	y = new double[n];
//	cout << "(((((((((" << endl;
	for (i = 1; i < n; i++)
	{
		cin >> x[i];
		cin >> y[i];
		(*xs).push_back(x[i]);
		(*ys).push_back(y[i]);
	}
	x[0] = *x1;
	y[0] = *y1;
//	cout << "(********(" << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (i != j)
			{
				e[cur].first = i;
				e[cur].second = j;
				e[cur].cost = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
				cur++;
			}
		}
	if (n > 1)
	{
		*x1 = x[n - 2];
		*y1 = y[n - 2];
	}
//	for (i = 0; i < n; i++)
//		cout << y[i];
//	delete(x);
//	delete(y);
	return e;
}

int ford_bellman(int n, struct edge *e, double *length, vector <int> been, double *d)
// return [mn, nmn], where nmn - number of nearest vertice, mn - min path lenght
{
	int i, nmn, any = 1;
	double mn;
	d[0] = 0;
	for (i = 1; i < n; i++)
		d[i] = INF;
	while (any)
	{
        	any = 0;
        	for (i = 0; i < (n * (n - 1)); i++)
        		if (d[e[i].first] < INF)
       				if (d[e[i].second] > d[e[i].first] + e[i].cost)
       				{
        				any = 1;
                			d[e[i].second] = d[e[i].first] + e[i].cost;
				}
 	}
//	for (i = 0; i < n; i++)
//		cout << d[i] << "	";
//	cout << endl;
	for (i = 0; i < been.size(); i++)
	{
		d[been[i]] = INF;
	}
	mn = INF;
	for (i = 1; i < n; i++)
	{
		if (d[i] < mn)
		{
			mn = d[i];
			nmn = i;
		}
	}
	if (mn == INF)
		return -1;
	*length = *length + mn;
//	cout << mn << ":::::::" << nmn << endl;
	return nmn;
}	

struct edge *change(int n, struct edge *e, int cur)
{
	int i;
	if (cur <= 0 || cur >= n)
		return e;
	for (i = 0; i < n * (n - 1); i++)
	{
		if (e[i].first == 0)
			e[i].first = cur;
		else if (e[i].first == cur)
			e[i].first = 0;
		if (e[i].second == 0)
			e[i].second = cur;
		else if (e[i].second == cur)
			e[i].second = 0;
	}
	return e;
}

/*
struct edge *change(int n, struct edge *e, int cur)
{
	int i;
	double c, *x, *y;
	x = new double[n - 1];
	y = new double[n - 1];
//	cout << "((^^^^^^((" << endl;
	for (i = 0; i < n - 1; i++)
		x[i] = e[i].cost;
	for (i = (cur) * (n - 1); i < (n - 1) * cur + n - 1; i++)
		y[i - cur * (n - 1)] = e[i].cost;

	c = x[cur - 1];
	for (i = cur - 1; i > 0; i--)
		x[i] = x[i - 1];
	x[0] = c;

	c = y[0];
	for (i = 0; i < cur - 1; i++)
		y[i] = y[i + 1];
	y[cur - 1] = c;

//	cout << "((^88888((" << endl;
	for (i = 0; i < n - 1; i ++)
		e[i].cost = y[i];
	
	for (i = (cur) * (n - 1); i < (n - 1) * cur + n - 1; i++)
		e[i].cost = y[i - cur * (n - 1)];

//	cout << "((^888lllll8((" << endl;
	for (i = 1; i < n - 1; i++)
	{
		if (i < cur)
			e[n * i - 1 + cur - 1].cost = x[i];
//		cout << i << "((^888lllll8((" << endl;
		if (i > cur)
			e[n * i + cur - 1].cost = x[i - 1];
//		cout << i << cur << " " << n << "((^888lllll8((" << endl;
		e[n * i - 1].cost = y[i - 1];
//		cout << i << cur << " " << n << "((^888lllll8((" << endl;
	}
	for (i = 0; i < n - 1; i++)
		cout << x[i] << " " << endl;
	for (i = 0; i < n - 1; i++)
		cout << y[i] << " " << endl;
*///	delete [] x;
//	delete [] y;
//	cout << "((^888lllll8((" << endl;
//	return e;
//}

double start()
{
	int cnst = 150, i, n, all, cur, first = 0, counter = -1;
	double x, y, x0, y0;
	vector <int> been;
	double length, *d;
	struct edge *e;
	vector <double> xs, ys;
	cin >> all;
	cout << "!!!!!!!!" << all << endl;
	cin >> x;
	cin >> y;
	x0 = x;
	y0 = y;
	xs.push_back(x);
	ys.push_back(y);
	n = cnst;
	d = new double[n];
		e = new edge[n * (n - 1)];
	while (all > 0)	
	{
		n = min(cnst, all);
		all -= n - 1;
		if (all <= cnst)
			all--;
		if (n != cnst)
		{
			e = new edge[n * (n - 1)];
			d = new double[n];
		}
		e = input_data(e, n, &x, &y, &xs, &ys);
//		cout << "(((&&&(" << endl;
		if (first == 1)
		{
			been.clear();
			been.push_back(n - 1);
		}
		for (i = 0; i < n - 1; i++)
		{
		       cur = ford_bellman(n, e, &length, been, d);
//		       cout << "((===((" << endl;
		       if (cur == -1)
			       break;
		       e = change(n, e, cur);
		       been.push_back(cur);
//		       cout << "))))" << endl;
		}
//		for (i = 0; i < been.size(); i++)
//			cout << been[i] << " ! " << length << endl;
//		cout << "######" << endl;
	//	delete[] d;
//		delete e;
		first = 1;
		counter++;
	}
	x = xs[cur + counter * cnst];
	y = ys[cur + counter * cnst];
	cout << length << endl;
	length += sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
	cout << length << endl;
//	cout << x0 << " " << y0 << endl;
//	cout << x << " " << y << endl;
//	cout << xs[cur] << " " << ys[cur] << endl;
//	for (i = 0; i < n * (n - 1); i++)
//		cout << e[i].cost << endl;
//	cout << "*****" << endl;
//	cout << "*****" << endl;
//	for (i = 0; i < n * (n - 1); i++)
//		cout << e[i].cost << endl;
	return length;
}

void sort_by_x(int n, double *x, double *y)
{
	int i, j, n_min;
	double c;
	for (i = 0; i < n; i++)
	{
		n_min = i;
		for (j = i + 1; j < n; j++)
			if (x[j] < x[n_min] || (x[j] == x[n_min] && y[j] < y[n_min]))
				n_min = j;
		c = x[n_min];
		x[n_min] = x[i];
		x[i] = c;
		c = y[n_min];
		y[n_min] = y[i];
		y[i] = c;
	}
	return;
}

void sort_by_y(int n, double *x, double *y)
{
	int i, j, n_min;
	double c;
	for (i = 0; i < n; i++)
	{
		n_min = i;
		for (j = i + 1; j < n; j++)
			if (y[j] < y[n_min] || (y[j] == y[n_min] && x[j] < x[n_min]))
				n_min = j;
		c = x[n_min];
		x[n_min] = x[i];
		x[i] = c;
		c = y[n_min];
		y[n_min] = y[i];
		y[i] = c;
	}
	return;
}

void round_sort_by_x(int n, double *x, double *y)
{
	double *d, c;
	int i, j, n_min;
	d = new double[n];
	for (i = 1; i < n; i++)
		d[i] = sqrt((x[0] - x[i]) * (x[0] - x[i]) + (y[0] - y[i]) * (y[0] - y[i]));
	for (i = 1; i < n; i++)
	{
		n_min = i;
		for (j = 0; j < n; j++)
		{
			if (d[j] < d[n_min])
				n_min = j;
			else
			{
				if (d[j] == d[n_min])
				{
					if (x[j] < x[n_min] || (x[j] == x[n_min] && y[j] < y[n_min]))
						n_min = j;
				}
			}
		}
	}
	return;
}

void round_sort_by_y(int n, double *x, double *y)
{
	double *d, c;
	int i, j, n_min;
	d = new double[n];
	for (i = 1; i < n; i++)
		d[i] = sqrt((x[0] - x[i]) * (x[0] - x[i]) + (y[0] - y[i]) * (y[0] - y[i]));
	for (i = 1; i < n; i++)
	{
		n_min = i;
		for (j = 0; j < n; j++)
		{
			if (d[j] < d[n_min])
				n_min = j;
			else
			{
				if (d[j] == d[n_min])
				{
					if (y[j] < y[n_min] || (y[j] == y[n_min] && x[j] < x[n_min]))
						n_min = j;
				}
			}
		}
	}
	cout << "!!!" << endl;
	return;
}

void sort(char *name, char c)
//if c == 'x' then sort by x else by'y'; 
//if it's capital then  by distance to first point, and after by x or y
{
	int n, i, j;
	double *x, *y;
	ofstream fout;
	fstream fin(name);
	fin >> n;
	x = new double[n];
	y = new double[n];
	for (i = 0; i < n; i++)
	{
		fin >> x[i];
		fin >> y[i];
	}
	fin.close();
	if (c == 'x')
		sort_by_x(n, x, y);
	if (c == 'y')
		sort_by_y(n, x, y);
	if (c == 'X')
		round_sort_by_x(n, x, y);
	if (c == 'Y')
		round_sort_by_y(n, x, y);
	fout.open(name);
	fout << n << endl;
	for (i = 0; i < n; i++)
	{
		fout << x[i] << " " << y[i] << endl;
	}
	fout.close();
	return;
}

int main()
{
	char h, *name = "new_file.txt", *for_sort = " xyXY";
	ofstream fout(name);
	double c, len[5];
	int n, fd, i, save0;
	cin >> n;
	fout << n << endl;
	for (i = 0; i < n; i++)
	{
		cin >> c;
		fout << c << " ";
		cin >> c;
		fout << c << endl;
	}
	fout.close();
	save0 = dup(0);
	for (i = 0; i < 5; i++)
	{
		if (i > 0)
			sort(name, for_sort[i]);
		fflush(stdin);
		fd = open(name, O_RDONLY);
		if (fd == -1)
			return 0;
		dup2(fd, 0);
		close(fd);
		len[i] = start();
	}
	c = len[0];
	for (i = 1; i < 5; i++)
		if (c > len[i])
			c = len[i];
	cout << c << endl;
/*	fflush(stdin);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;
	dup2(fd, 0);
	close(fd);
	c = start();
//	cout << "*****" << endl;
	cout << c << endl;
	sort(name, 'x');
	fflush(stdin);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;
	dup2(fd, 0);
	close(fd);
	c = start();
	sort(name, 'y');
	fflush(stdin);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;
	dup2(fd, 0);
	close(fd);
	c = start();
	sort(name, 'X');
	fflush(stdin);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;
	dup2(fd, 0);
	close(fd);
	c = start();
	sort(name, 'Y');
	fflush(stdin);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;
	dup2(fd, 0);
	close(fd);
	c = start();*/
	return 0;
}
