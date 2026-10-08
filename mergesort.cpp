#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

void tron(vector<double>& a, vector<double>& tam, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tam[k++] = a[i++];
        } else {
            tam[k++] = a[j++];
        }
    }

    while (i <= mid) tam[k++] = a[i++];
    while (j <= right) tam[k++] = a[j++];

    for (int t = left; t <= right; t++) {
        a[t] = tam[t];
    }
}

void mergeSort(vector<double>& a, vector<double>& tam, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(a, tam, left, mid);
    mergeSort(a, tam, mid + 1, right);
    tron(a, tam, left, mid, right);
}

int main() {
    string tenFile;
    cout << "Nhap ten file (vi du data1.txt): ";
    getline(cin, tenFile);
    ifstream fin(tenFile);

    int n;
    if (!(fin >> n) || n < 0) {
        cout << "Khong doc duoc file!" << endl;
        return 1;
    }

    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        if (!(fin >> a[i])) {
            cout << "Du lieu khong hop le!" << endl;
            return 1;
        }
    }
    fin.close();

    auto batDau = chrono::steady_clock::now();
    {
        // Tinh ca thoi gian tao va giai phong mang phu.
        vector<double> tam(n);
        mergeSort(a, tam, 0, n - 1);
    }
    auto ketThuc = chrono::steady_clock::now();

    double thoiGian = chrono::duration<double, milli>(ketThuc - batDau).count();
    cout << "MergeSort: " << thoiGian << " ms" << endl;
    cout << "Da tang dan: " << (is_sorted(a.begin(), a.end()) ? "Co" : "Khong") << endl;
    return 0;
}
