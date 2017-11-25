#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<math.h>
using namespace std;
void user_input();
void fermat();
void secret_key(string name);

int main()
{
	
	user_input();
	//fermat();
	return 0;
}
void user_input()
{
	unsigned long long int  t_batemp, t_abtemp, shared_key, shared_keytemp, t_ba, t_ab;
	string n_user1, n_user2;
	int s_user1, s_user2;
	cout << "User 1 please enter your name: ";
	cin >> n_user1;
	cout << "User 2 please enter your name: ";
	cin >> n_user2;
/*
	cout << endl << "Hi " << n_user1 << ", please select your secret key = " << endl;
	cin >> s_user1;
	cout << "Hi " << n_user2 << ", please select your secret key = " << endl;
	cin >> s_user2;
	*/
	secret_key(n_user1);
	secret_key(n_user2);
}
void secret_key(string name)
{
int sum = 0, secret_key;
	int l = name.length();
	for (int i = 0; i <l; i++)
	{
		sum = sum + (int)name[i];
		cout << (int)name[i] << endl;
	}
	cout << "sum = " << sum << endl;
	secret_key = sum % 11; //need to use a random value for mod
	cout << name << " your sceret key is: " << secret_key<<endl;




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
			b = b / 2;
			cout << y << "^" << b << " * " << x << endl;
		}
		return x;
	}