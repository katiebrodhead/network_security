
// Katie Brodhead, Raghav Rathi, Emerson Small
// Diffie Hellman Key Exchange
// Network Security, Fall 2017

#include<iostream>
#include<string>
#include <utility>      // std::pair
using namespace std;

//const int LOW_LIMIT = 45000;
//const int MAX_LIMIT = 50000; 

// calculates (a^b)%MOD using the doubling method
int pow(int a, int b, int MOD);

// "primes_generater" returns an array of all Sophie Germain primes between 
// low and high inclusive, as well as the the size of the array;
// Sophie Germain primes are safe primes needed for the Diffie Hellman Algorithm
pair <int*,int> primes_generator(int low, int high);


int main()
{

	int LOW_LIMIT = 45000,  MAX_LIMIT = 50000;

	cout << "Please enter a range [low, high] (e.g. [45000, 50000]) " << endl;
	cout << "from which to select a safe prime." << endl;
	cout << "low = ";
	cin >> LOW_LIMIT;
	cout << "high = ";
	cin >> MAX_LIMIT;

	pair <int*,int> result = primes_generator(LOW_LIMIT, MAX_LIMIT);
	int* primes = result.first;
	int size = result.second;

	//For testing
	//for(int i; i<size;i++)
	//	cout << primes[i] << " ";
	//cout << endl;
	//cout << "size is " << size << endl;

	srand((unsigned)time(0));
	int p = primes[rand()%size];
	int g = rand()%p;

	string user1, user2;
	int user1_private, user1_public;
	int user2_private, user2_public;
	int shared_key;

	cout << "The public key <g,p> is < " << g << ", " << p << " >" << endl << endl;

	cout << "User 1 please enter your name: ";
	cin >> user1;
	user1_private = rand()%p;
	user1_public = pow(g, user1_private, p);

	cout << "Your mod " << p << " <private key, public key> = <a,g^a> = < " 
		<< user1_private << ", " << user1_public << " >" << endl << endl;
		

	cout << "User 2 please enter your name: ";
	cin >> user2;
	user2_private = rand()%p;
	user2_public = pow(g, user2_private, p);

	cout << "Your mod " << p << " <private key, public key> = <b,g^b> = < " 
		<< user2_private << ", " << user2_public << " >" << endl << endl;

	shared_key = pow(user2_public, user2_private, p);

	cout << "The mod " << p << " shared key g^(ab) is " << shared_key << endl;

	int message;
	cout << user1 << ", give the numerical message you wish to send " << user2 << ": " << endl;
	cin >> message;

	//CONTINUE coding here


	return 0;
}

pair <int*,int> primes_generator(int low, int high)
{
	int remainder=0;

	int* primes = new int[high/2];

	for(int i=1; i<high/2;i++)
		primes[i]=0;

	int primes_counter;
	if(low<=2)
	{
		primes[0]=2;
		primes_counter=1;
	}
	else
		primes_counter=0;

	int starting_index;
	if (low%2==1)
		starting_index=low;
	else
		starting_index=low+1;


	for (int i = starting_index; i <= high; i+=2) 
	{
		//Use Sieve of Eratosthenes
		//With Fermat's Theorem to Help Eliminate
		int j = 3; 
		do{ 
			//Eliminate via Fermat's Theorem
			if (j!=i && pow(j, i-1, i)!=1)
				break;
			remainder = i%j;
			j+=2;	
		} while (remainder != 0);	

		if (j-2 == i)//i is Prime
		{
			int Sophie_check = 0, k=0, sophie_i=0;

			//Check if (i-1)/2 is prime
			sophie_i = (i-1)/2;
			k = 3; 
			do{ 
				//Eliminate via Fermat's Theorem
				if (k!=sophie_i && pow(k, sophie_i-1, sophie_i)!=1)
					break;
				remainder = sophie_i%k;
				k+=2;	
			} while (remainder != 0);	
			if (k-2 == sophie_i)//i is a Sophie Germain Prime
				Sophie_check=1;

			if (Sophie_check==0)
			{
				//Check if 2i+1 is prime
				sophie_i = 2*i+1;
				k = 3; 
				do{ 
					//Eliminate via Fermat's Theorem
					if (k!=sophie_i && pow(k, sophie_i-1, sophie_i)!=1)
						break;
					remainder = sophie_i%k;
					k+=2;	
				} while (remainder != 0);	
				if (k-2 == sophie_i)//i is a Sophie Germain Prime
					Sophie_check=1;
			}
			
			if(Sophie_check==1)
			{
				primes[primes_counter]=i;
				primes_counter++;
			}
			
		}
	}
	int* primes_list = new int[primes_counter];
	for(int i=0; i<primes_counter;i++)
		primes_list[i]=primes[i];
	delete [] primes;
	
	return make_pair(primes_list, primes_counter);
	
}

// calculates (a^b)%MOD using the doubling method
// The cout statements show the progress being made 
int pow(int a, int b, int MOD) {
    int x = 1, y = a;
	//cout << y << "^" << b << " * " << x << "^" << b << endl;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y);
            if (x > MOD) x = x% MOD;
        }
        y = (y * y);
        if (y > MOD) y = y % MOD;
        b =b/ 2;
        //cout << y << "^" << b << " * " << x << endl;
    }
    return x;
}


