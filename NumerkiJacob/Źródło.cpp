


#include <iostream>

using namespace std;

double** L(double ** tab, double n);

double** D(double ** tab, double n);

double** U(double ** tab, double n);

double** N(double ** tab, double n);

double** obliczSume(double **tab1, double **tab2, int n);

double** obliczIloczyn(double **tab1, double ** tab2, int n);

double* Jacob(double **wsp, double *roz, int n, int iloscIteracji);

double** obliczPrzeciwna(double **tab, int n);



int main()
{
	
	int n = 4;
	cout << "Ilosc niewiadonych i zmiennych: ";
	cin >> n;

	//tworzenie tablicy wspolczynnikow
	double **wsp = new double*[n];
	for (int i = 0; i < n; i++)
		wsp[i] = new double[n];

	//wczytanie wspolczynnikow
	cout << "Podaj kolejne wspolczynniki: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Wiersz: " << i + 1 << endl;
		for (int j = 0; j < n; j++)
		{
			cin >> wsp[i][j];
		}
	}

	/*wsp[0][0] = 4;
	wsp[0][1] = -1;
	wsp[0][2] = -0.2;
	wsp[0][3] = 2;
	wsp[1][0] = -1;
	wsp[1][1] = 5;
	wsp[1][2] = 0;
	wsp[1][3] = -2;
	wsp[2][0] = 0.2;
	wsp[2][1] = 1;
	wsp[2][2] = 10;
	wsp[2][3] = -1;
	wsp[3][0] = 0;
	wsp[3][1] = -2;
	wsp[3][2] = -1;
	wsp[3][3] = 4;*/


	//wczytywanie rozwiazan
	double *rozwiazania = new double[n];
	cout << "Podaj kolejne rozwiazania: " << endl;
	for (int i = 0; i < n; i++)
		cin >> rozwiazania[i];
	cout << endl;

	
	int iteracje = 2;

	while (true)
	{
		cout << "Podaj ilosc iteracji: ";
		cin >> iteracje;

		double *wyniki = Jacob(wsp, rozwiazania, n, iteracje);
		for (int i = 0; i < n; i++)
			cout << "x" << i + 1 << " = " << wyniki[i] << endl;
	}



	system("pause");

	return 0;
}

double ** L(double ** tab, double n)
{
	//stworz tablice
	double **l = new double*[n];
	for (int i = 0; i < n; i++)
		l[i] = new double[n];

	//uzupelnij zerami
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			l[i][j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			l[i][j] = tab[i][j];


	return l;
}

double ** D(double ** tab, double n)
{
	//stworz tablice
	double **d = new double*[n];
	for (int i = 0; i < n; i++)
		d[i] = new double[n];

	//uzupelnij zerami
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			d[i][j] = 0;

	for (int i = 0; i < n; i++)
		d[i][i] = tab[i][i];

	return d;
}

double ** U(double ** tab, double n)
{
	//stworz tablice
	double **u = new double*[n];
	for (int i = 0; i < n; i++)
		u[i] = new double[n];

	//uzupelnij zerami
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			u[i][j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			u[j][i] = tab[j][i];


	return u;
}

double ** N(double ** tab, double N)
{
	//stworz tablice
	double **n = new double*[N];
	for (int i = 0; i < N; i++)
		n[i] = new double[N];

	//uzupelnij zerami
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			n[i][j] = 0;

	for (int i = 0; i < N; i++)
		n[i][i] = pow(tab[i][i], -1);

	return n;
}

double ** obliczSume(double ** tab1, double ** tab2, int n)
{
	//stworz tablice
	double **tab = new double*[n];
	for (int i = 0; i < n; i++)
		tab[i] = new double[n];

	//sumuj
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tab[i][j] = tab1[i][j] + tab2[i][j];

	return tab;
}

double ** obliczIloczyn(double ** tab1, double ** tab2, int n)
{
	//stworz tablice
	double **tab = new double*[n];
	for (int i = 0; i < n; i++)
		tab[i] = new double[n];

	double s;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			s = 0;
			for (int k = 0; k < n; k++)
				s += tab1[i][k] * tab2[k][j];
			tab[i][j] = s;
		}

	return tab;
}

double ** obliczPrzeciwna(double ** tab, int n)
{
	double **u = new double*[n];
	for (int i = 0; i < n; i++)
		u[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			u[i][j] = -1 * tab[i][j];
	return u;
}

double * Jacob(double ** wsp, double * roz, int n, int rzad)
{
	//tworzenie i inicjalizacja wynikow
	double *wyniki = new double[n];
	for (int i = 0; i < n; i++)
		wyniki[i] = 0;

	double *tmp = new double[n];
	for (int i = 0; i < n; i++)
		tmp[i] = 0;

	double **macierzD = D(wsp, n);
	double **macierzN = N(macierzD, n);
	double **macierzU = U(wsp, n);
	double **macierzL = L(wsp, n);
	double **macierz_N_przeciwna = obliczPrzeciwna(macierzN, n);

	double **macierzSumaLU = obliczSume(macierzU, macierzL, n);
	double **macierzM = obliczIloczyn(macierz_N_przeciwna, macierzSumaLU, n);


	for (int k = 0; k < rzad; k++)
	{
		for (int i = 0; i < n; i++)
		{
			tmp[i] = macierzN[i][i] * roz[i];
			for (int j = 0; j < n; j++)
			{
				tmp[i] += macierzM[i][j] * wyniki[j];
			}
		}

		for (int i = 0; i < n; i++)
			wyniki[i] = tmp[i];
	}

	return wyniki;
}


double ** mnozenie(double **tab1, double ** tab2, int n)
{
	double **tab = new double*[n];
	for (int i = 0; i < n; i++)
		tab[i] = new double[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tab[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				tab[i][j] += tab1[i][k] * tab2[k][j];
			}
		}
	}

	return tab;
}