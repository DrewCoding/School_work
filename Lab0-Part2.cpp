#include <iostream>

using namespace std;

int fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main() {

    int n;
    
    

    //for (int i = 0; i < n; i++) {
        std::cout << fibonacci(5) << " ";
    //}
    std::cout << std::endl;

    return 0;
}