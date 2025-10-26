// Mahmoud Part

#include <bits/stdc++.h>
using namespace std;

// First Way to find Fibonacci Number using Recursion O(2^n)
int fibonacci_recursion(int n) {
    if (n <= 1) return n;
    return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

// Second Way to find Fibonacci Number using divide and conquer (matrix multiplication) O(log(n))
vector<vector<int>> multiply(const vector<vector<int>> &x, const vector<vector<int>> &y) {
    vector<vector<int>> res(2, vector<int>(2));

    res[0][0] = x[0][0] * y[0][0] + x[0][1] * y[1][0];
    res[0][1] = x[0][0] * y[0][1] + x[0][1] * y[1][1];
    res[1][0] = x[1][0] * y[0][0] + x[1][1] * y[1][0];
    res[1][1] = x[1][0] * y[0][1] + x[1][1] * y[1][1];
    return res;
}

int fibonacci_matrix(int n)
{
    if (n == 0) return 0;
    vector<vector<int>> x = {{1, 1}, {1, 0}},res = {{1, 0}, {0, 1}};
    int m = n - 1;
    while (m)
    {
        if (m & 1) res = multiply(res, x);
        x = multiply(x, x);
        m >>= 1;
    }
    x = res;
    return x[0][0];
}

// Third Way to find Fibonacci Number using DP O(n)
int fibonacci_dp(int n) {
    vector<int> fib(n+1, 0);
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i <= n ; i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib[n];
}


int main() {
    while (true) {
        cout << "\n==================== Fibonacci Calculator ====================\n";
        cout << "1. Fibonacci using Recursion\n";
        cout << "2. Fibonacci using Divide and Conquer (Matrix Multiplication)\n";
        cout << "3. Fibonacci using Dynamic Programming\n";
        cout << "4. Exit\n";
        cout << "==============================================================\n";
        cout << "Enter your option: ";

        int option;
        cin >> option;

        if (option == 4) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        if (option < 1 || option > 4) {
            cout << "Invalid option. Please try again.\n";
            continue;
        }

        cout << "Enter a number to find its Fibonacci: ";
        int n;
        cin >> n;

        switch (option) {
            case 1:
                cout << "Fibonacci of " << n << " (Recursion) = " << fibonacci_recursion(n) << endl;
                break;
            case 2:
                cout << "Fibonacci of " << n << " (Matrix Multiplication) = " << fibonacci_matrix(n) << endl;
                break;
            case 3:
                cout << "Fibonacci of " << n << " (Dynamic Programming) = " << fibonacci_dp(n) << endl;
                break;
        }
    }
    return 0;
}