//CODIGO QUE CALCULA EL TIEMPO DEL QUICK Y MERGE RESPECTO A UN DESORDEN ENTRE EL 40-60%

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
using namespace std;

ofstream prepare_file() {
    ofstream csv_file ("data_40-60.csv");
    csv_file << "inversiones,time_merge,time_quick" << endl;
    return csv_file;
}

void write_data_to_file(ofstream& csv_file, int inv, double time0, double time1) {
    csv_file << inv << ',' << time0 << ',' << time1 << endl;
}

void swap(vector<int> &v,int i, int j){
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void desordenar(vector<int> &v,int d){
    int i = rand()%(v.size()-1);
    int count = 0;

    while(count != d){
        i = rand()%(v.size()-1);
        if(v[i] < v[i+1]) {
            swap(v,i,i+1);
            ++count;
        }

    }
}

//CALCULA DISORDRE
int inversions(vector<int>& v, int l, int r) {
	if (l >= r) return 0;
	int m = (l+r)/2;
	int N1 = inversions(v,l,m);
	int N2 = inversions(v,m+1,r);
	vector<int> w(r-l+1);
	int i, j, k, N3;
	i = l; k = 0; j = m+1; N3 = 0;
	while(i <= m and j <= r) {
		if(v[i] <= v[j]) w[k++] = v[i++];
		else {
			w[k++] = v[j++];
			N3 += m+1 - i;
		}
	}
	while(i <= m) w[k++] = v[i++];
	while (j <= r) w[k++] = v[j++];
	for(k = 0; k < r-l+1; ++k) v[l+k] = w[k];
	return N1+N2+N3;
}

//MERGESORTE
void merge (vector<int>& v, int l, int m, int r) {
    vector<int> b(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m and j <= r) {
        if (v[i] <= v[j]) b[k++] = v[i++];
        else b[k++] = v[j++];
    }
    while (i <= m) b[k++] = v[i++];
    while (j <= r) b[k++] = v[j++];
    for (k = 0; k <= r - l; ++k) v[l + k] = b[k];
}

void merge_sort_1 (vector<int>& v, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_1(v, l, m);
        merge_sort_1(v, m + 1, r);
        merge(v, l, m, r);
    } 
}


void merge_sort (vector<int>& v) {
merge_sort_1(v, 0, v.size() - 1);
}

//QUICKSORT
    int partition (vector<int>& v, int l, int r) {
    int x = v[l];
    int i = l - 1;
    int j = r + 1;
    for (;;) {
        while (x < v[--j]);
        while (v[++i] < x);
        if (i >= j) return j;
        swap(v[i], v[j]);
    } 
}

void quick_sort_1 (vector<int>& v, int l, int r) {
    if (l < r) {
        int q = partition(v, l, r);
        quick_sort_1(v, l, q);
        quick_sort_1(v, q + 1, r);
    } 
}


void quick_sort (vector<int>& v) {
    quick_sort_1(v, 0, v.size() - 1);
}


int main() {
    ofstream csv_file = prepare_file();
    srand(unsigned(time(nullptr)));
    int n, r;
    cout << "Enter vector size:" << endl;
    cin >> n;
    cout << "Enter number of muestras" << endl;
    cin >> r;
    vector<int> v(n);
    long double max = (n*(n-1))/2;
    bool listo = false;
    int inici = max*0.4;
    int fin = max*0.6;
   
    long double maxo = (fin-inici)/r;
    
    cout << max << endl;
    for(int i = r; i >= 0 ; --i) {
        for(int b = 0; b < n; ++b){
            v[b] = b+1;
        }

        /*
        for(int k = 0; k < n; ++k){
            cout << v[k] << ' ';
        }
        cout << endl;
        */
        cout << "r: " << r << endl;
        cout << "i: " << i << endl;
        cout << maxo << 'l' << inici << endl;
        int inv = inici+i*maxo;
        cout << "inv: " << inv << endl;
        desordenar(v,inv);
        double time0 = 0;   //MERGE
        double time1 = 0;   //QUICK

        int random = rand()%2;

        vector<int> v1 = v;
        vector<int> v2 = v;

        //cout << "VECTOR HECHO" << endl;

        if (random == 0) {
            unsigned t0, t1, t2;
            t0 = clock();
            merge_sort(v1);
            //cout << "MERGE" << endl;
            t1 = clock();
            quick_sort(v2);
            //cout << "QUICK" << endl;
            t2 = clock();

            time0 = (double(t1-t0)/CLOCKS_PER_SEC);
            time1 = (double(t2-t1)/CLOCKS_PER_SEC);

            //cout << "rnd0" << endl;
        
        } else {
        
            unsigned t0, t1, t2;
            t0 = clock();
            quick_sort(v2);
            //cout << "QUICK" << endl;
            t1 = clock();
            merge_sort(v1);
            //cout << "MERGE" << endl;
            t2 = clock();

            time1 = (double(t1-t0)/CLOCKS_PER_SEC);
            time0 = (double(t2-t1)/CLOCKS_PER_SEC);
            //cout << "rnd1" << endl;
        }
        
        if (listo) {
        cout << "inversiones :" << inv << " Quicksort :" << time1 << "Mergesort: " << time0 << endl;
        write_data_to_file(csv_file, inv, time0*1000, time1*1000);
        }
        if (r-i == 40 and not listo) {
            listo = true;
            i = r;
        }
    }
}
