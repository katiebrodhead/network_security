#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
using namespace std;
void fermat();
int main()
{

/*	int random;
	srand((unsigned)time(0));
	random = rand() % 999;
	cout << random << endl;
	int p = 11;
	int temp = pow(p, random - 1);

	if ((temp % random == 1))
		cout << random << " is prime" << endl;

	else
		cout << random << " is not prime" << endl;
	
int a = 6, n = 10,prime;
prime = pow(a, n - 1);
if(prime % n == 1)
	cout<< " 'n' is prime" << n << endl;

else
	cout << " 'n' is not prime" << endl;
*/
	fermat();
	return 0;
}

	void fermat()
	{
		
		unsigned long long int random, p = 7, expo, check;
		do

		{
			
		srand((unsigned)time(0));
		random = rand() % 30;
		if (random % 2 == 0)
			random = random + 1;
		//prime testing
		expo = pow(p, (random - 1)); // p^r-1
		check = expo % random;
		cout << "the number generated is " << random << "\n";
		cout << "p = 7, a = " << random << " p^a-1 = " << expo << " mod is = " << check << "\n";
	
		} while (check != 1);
		cout << random << " is  prime"<< endl;
		
	}
