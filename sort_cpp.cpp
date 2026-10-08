#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

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
    sort(a.begin(), a.end());
    auto ketThuc = chrono::steady_clock::now();

    double thoiGian = chrono::duration<double, milli>(ketThuc - batDau).count();
    cout << "sort C++: " << thoiGian << " ms" << endl;
    cout << "Da tang dan: " << (is_sorted(a.begin(), a.end()) ? "Co" : "Khong") << endl;
    return 0;
}
