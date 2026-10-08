#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

void vunDong(vector<double>& a, int n, int i) {
    int lonNhat = i;
    int trai = 2 * i + 1;
    int phai = 2 * i + 2;

    if (trai < n && a[trai] > a[lonNhat]) lonNhat = trai;
    if (phai < n && a[phai] > a[lonNhat]) lonNhat = phai;

    if (lonNhat != i) {
        swap(a[i], a[lonNhat]);
        vunDong(a, n, lonNhat);
    }
}

void heapSort(vector<double>& a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        vunDong(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        vunDong(a, i, 0);
    }
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
    heapSort(a, n);
    auto ketThuc = chrono::steady_clock::now();

    double thoiGian = chrono::duration<double, milli>(ketThuc - batDau).count();
    cout << "HeapSort: " << thoiGian << " ms" << endl;
    cout << "Da tang dan: " << (is_sorted(a.begin(), a.end()) ? "Co" : "Khong") << endl;
    return 0;
}
