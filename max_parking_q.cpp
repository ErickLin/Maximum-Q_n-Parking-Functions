#include <iostream>
#include <set>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;

// Whether or not f is a Q_n-parking function
bool dhar_q(int n, vi &f) {
    vb isMarked(1 << n);
    set<int> marked;
    bool canMark = true;
    while (canMark && marked.size() < (1 << n)) {
        canMark = false;
        for (int i = 0; i < (1 << n); i++) {
            if (!isMarked[i]) {
                int numMarkedNeighbors = 0;
                for (int j = 0; j < n; j++) {
                    if (isMarked[i ^ (1 << j)]) {
                        numMarkedNeighbors++;
                    }
                }
                if (numMarkedNeighbors > f[i]) {
                    isMarked[i] = true;
                    marked.insert(i);
                    canMark = true;
                }
            }
        }
    }
    return canMark;
}

// Number of maximum Q_n-parking functions dominating f
int num_dom_max_parking_q(int n, vi &f, set<vi> &visited, set<vi> &parking) {
    int ret = 0;
    if (dhar_q(n, f)) {
        parking.insert(f);
        bool isMax = true;
        for (int i = 0; i < (1 << n); i++) {
            f[i]++;
            if (visited.find(f) == visited.end()) {
                visited.insert(f);
                ret += num_dom_max_parking_q(n, f, visited, parking);
            }
            if (parking.find(f) != parking.end()) {
                isMax = false;
            }
            f[i]--;
        }
        // If no greater parking functions, then f is maximum
        if (isMax) {
            ret = 1;
            for (int i = 0; i < (1 << n); i++) {
                cout << "f(";
                for (int j = n - 1; j >= 0; j--) {
                    cout << ((i & (1 << j)) >> j);
                }
                cout << ")=" << f[i] << " ";
            }
            cout << "\n";
        }
    }
    return ret;
}

int main() {
    /*
    if (n == 3) {
        f[0b000] = -1;
        f[0b010] = 0;
        f[0b100] = 0;
        f[0b101] = 0;
        f[0b001] = 1;
        f[0b011] = 1;
        f[0b111] = 1;
        f[0b110] = 2;
        cout << dhar_q(n, f) << '\n';
    }
    */
    int n;
    cout << "Enter n for which the maximum parking functions on Q_n are needed: ";
    cin >> n;
    vi f(1 << n);
    f[0] = -1;
    for (int i = 1; i < (1 << n); i++) {
        f[i] = 0;
    }
    set<vi> visited, parking;
    visited.insert(f);
    cout << "Total for n=" << n << ": " << num_dom_max_parking_q(n, f, visited, parking) << '\n';
    return 0;
}
