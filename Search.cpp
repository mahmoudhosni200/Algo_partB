// Seit Part
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int sequentialSearch(const vector<T>& v, T value) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int RecursiveSequentialSearch(const vector<T>& v, T value, int i = 0) {
    if (i == v.size()) {
        return -1;
    }
    if (v[i] == value) {
        return i;
    }
    return RecursiveSequentialSearch(v, value, i + 1);
}

template <typename T>
int binarySearch(const vector<T>& v, T value) {
    int l = 0;
    int r = v.size() - 1;

    while (l <= r) {
        int m = (l + r) / 2;
        if (v[m] == value) {
            return m;
        }
        if (v[m] < value) {
            l = m + 1;
        }else {
            r = m - 1;
        }
    }

    if (v[l] == value) {
        return l;
    }

    return -1;
}

template <typename T>
int RecursiveBinarySearch(const vector<T>& v, T value, int l, int r) {

    if (l > r) {
        return -1;
    }
    int m = (l + r) / 2;

    if (v[m] == value) {
        return m;
    }
    if (v[m] < value) {
        return RecursiveBinarySearch(v, value, m + 1, r);
    }
        
    return RecursiveBinarySearch(v, value, l, m - 1);
    
}

int main() {

    vector<int> v = {1, 5, 10, 7, 6, 2, 8, 4};

    while (true) {
        cout << "Enter the target value: ";
        int target;
        cin >> target;
        cout << "Choose your option:\n "
                "1) Sequential Search\n "
                "2) Recursive Sequential Search\n "
                "3) Binary Search\n "
                "4) Recursive Binary Search\n "
                "5) Exit\n"
                "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Your target is at index: " << sequentialSearch(v, target) << endl;
        }else if (choice == 2) {
            cout << "Your target is at index: " << RecursiveSequentialSearch(v, target) << endl;
        }else if (choice == 3) {
            sort(v.begin(), v.end());
            cout << "Your target is at index: " << binarySearch(v, target) << endl;
        }else if (choice == 4) {
            sort(v.begin(), v.end());
            cout << "Your target is at index: " << RecursiveBinarySearch(v, target, 0, v.size() - 1) << endl;
        }else {
            exit(0);
        }
    }


}
