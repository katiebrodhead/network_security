#include<iostream>
#include<cstdlib>
#include<ctime>
#include<math.h>
using namespace std;
void fermat();
int main()
{
	unsigned long int s_user1, s_user2,t_batemp,t_abtemp, t_ba,t_ab,shared_key, shared_keytemp;
	cout << "User 1, please select your secret key = ";
	cin >> s_user1;
	cout << "User 2, please select your secret key = ";
	cin >> s_user2;

	t_batemp = pow(7, s_user1);
	t_abtemp = pow(7, s_user2);
	t_ab = t_abtemp % 11; //mod 11, because there was some problem in generating random prime so took 11 as temp. 
	t_ba = t_batemp % 11;
	cout << "The session key for user 1 is T_ba = " <<t_ba<<"\n";
	cout << "The session key for user 2 is T_ab = " << t_ab << endl;
	shared_keytemp = pow(pow(11, s_user1),s_user2);
	shared_key = shared_keytemp % 11;
	cout << "The key to encrypt a message is : " << shared_key<<endl;

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
	