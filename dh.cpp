
// Katie Brodhead, Raghav Rathi, Emerson Small
// Diffie Hellman Key Exchange
// Network Security, Fall 2017

#include<iostream>
#include<cmath>
using namespace std;


/* calculates (a^b)%MOD */
int pow(int a, int b, int MOD);



int main()
{
	cout << pow(2, 9166, 9167) <<endl;

	return 0;
}


/* calculates (a^b)%MOD */
int pow(int a, int b, int MOD) {
    int x = 1, y = a;
	cout << y << "^" << b << " * " << x << "^" << b << endl;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y);
            if (x > MOD) x = x% MOD;
        }
        y = (y * y);
        if (y > MOD) y = y % MOD;
        b =b/ 2;
        cout << y << "^" << b << " * " << x << endl;
    }
    return x;
}