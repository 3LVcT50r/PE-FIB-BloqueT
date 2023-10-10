#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

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

int main(){
    srand(unsigned(time(nullptr)));
    int n,m,d;
    cout << "Enter vector size:" << endl;
    cin >> n;
    cout << "Enter number of vectors" << endl;
    cin >> m;
    cout << "Enter number of iversions" << endl;
    cin >> d;
    for(int i = 0; i < m; ++i){
        cout << "#" << i << " = ";
        vector<int> v(n);
        generate(v.begin(), v.end(), rand);
        while(inversions(v,0,n-1) != d){
            generate(v.begin(), v.end(), rand);
        }
        for(int j = 0; j < n; ++j){
        cout << v[j] << ' ';
        }
        cout << endl;
    }
}
