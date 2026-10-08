#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

void quickSort(vector<double>& a, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    double pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
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

    // Chi do thoi gian sap xep, khong tinh thoi gian doc file.
    auto batDau = chrono::steady_clock::now();
    quickSort(a, 0, n - 1);
    auto ketThuc = chrono::steady_clock::now();

    double thoiGian = chrono::duration<double, milli>(ketThuc - batDau).count();
    cout << "QuickSort: " << thoiGian << " ms" << endl;
    cout << "Da tang dan: " << (is_sorted(a.begin(), a.end()) ? "Co" : "Khong") << endl;
    return 0;
}
