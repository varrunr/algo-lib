#include<iostream>

using namespace std;

int z_process(string&);
int match(string&, int, int, int);
void printarr(int*, int, string);
void initZ(int *,int);

int main(int argc, char const *argv[])
{
	int n_testcase;
	string str;
	cin>>n_testcase;
	for(int i = 0;i < n_testcase; i++)
	{
		cin>>str;
		cout<<z_process(str)<<endl;	
	}
	return 0;
}

int match(string &str, int base1, int base2, int end)
{
	int ct = 0;
	for(int i=base1,j=base2 ; i<end && j<end; i++,j++ )
	{
		if(str[i] == str[j])
			ct++;
		else break;
	}
	return ct;
}

int z_process(string &str)
{
	int slen = str.size();
	int Z[slen+1];
	int left=0, right=0, boxr = 0, boxl = 0, maxmatch = 0;
	initZ(Z, slen+1);
	int final = slen;
	for(int i = 2;i <= slen;i++)
	{
		if(i > right)
		{
			Z[i] = match(str, i -1, 0, slen);
			if(Z[i] > 0)
			{
				left = i;
				right = i + Z[i] - 1;
			}
		}
		else
		{
			boxr = right - i + 1;
			boxl = i - left + 1;
			if(Z[boxl] < boxr)
			{
				Z[i] = Z[boxl];
			}
			else
			{
				maxmatch = match(str, right, boxr, slen);
				Z[i] = boxr + maxmatch;
				right += maxmatch;
				left = i;
			}
		}
		final += Z[i];
	}
	return final;
	//printarr(Z, slen, "Z");
}

void printarr(int* arr, int size, string headline)
{
	cout<<headline<<endl;
	for(int i=1;i<=size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void initZ(int* arr, int size)
{
	for(int i=0;i<size;i++)
	{
		arr[i] = 0;
	}
}