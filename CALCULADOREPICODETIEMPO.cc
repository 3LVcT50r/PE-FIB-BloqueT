#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

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
} }


void merge_sort (vector<int>& v) {
merge_sort_1(v, 0, v.size() - 1);
}

int partition (vector<int>& v, int l, int r) {
int x = v[l];
int i = l - 1;
int j = r + 1;
for (;;) {
while (x < v[--j]);
while (v[++i] < x);
if (i >= j) return j;
swap(v[i], v[j]);
} }

void quick_sort_1 (vector<int>& v, int l, int r) {
if (l < r) {
int q = partition(v, l, r);
quick_sort_1(v, l, q);
quick_sort_1(v, q + 1, r);
} }


void quick_sort (vector<int>& v) {
quick_sort_1(v, 0, v.size() - 1);
}


int main() {

	int n,m;
    double x1, x2; 
    //double x3;
    x1 = x2 = 0;
    //x3 = 0;
    //cout << "Enter Number of Vectors : ";
	cin >> m;
	//cout << "Enter Size of Vectors : ";
	cin >> n;
    for(int j = 0; j < m; ++j){
        //cout << "Enter Elements of Vector : ";
        vector<int> v1(n);
        for (int i = 0; i < n; ++i) {
            cin >> v1[i];
        }
        vector<int> v2 = v1;
        //vector<int> v3 = v1;
    
        unsigned t0, t1, t2;
        //unsigned t3;
        t0 = clock();
        quick_sort(v2);
        t1 = clock();
        merge_sort(v1);
        t2 = clock();
        /*sort(v3.begin(), v3.end());
        t3 = clock();*/
        double time0 = (double(t1-t0)/CLOCKS_PER_SEC);
        double time1 = (double(t2-t1)/CLOCKS_PER_SEC);
        //double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
        cout /*<< "MergeSort Execution Time: " */<< time0 << endl;
        cout /*<< "QuickSort Execution Time: " */<< time1 << endl;
        //cout << "Sort Execution Time:      " << time2 << endl;
        cout << endl;
        x1 += time0;
        x2 += time1;
        //x3 += time2;
    }
    x1 /=m;
    x2 /=m;
    //x3 /=m;
    cout << "MergeSort Average Execution Time: " << x1 << endl;
    cout << "QuickSort Average Execution Time: " << x2 << endl;
    //cout << "Sort Average Execution Time:      " << x3 << endl;
    
}
