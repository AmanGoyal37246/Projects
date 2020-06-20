#include <iostream>
//#include<bits/stdc++.h>
#include<string>
using namespace std;

#define M 3


// HILL CIPHER ENCRYPT DECRYPT
void getKeyMatrix(string key, int keyMatrix[][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(int cipherMatrix[][1],
             int keyMatrix[][3],
             int messageVector[][1])
{
    int x, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;

             for (x = 0; x < 3; x++)
            {
                cipherMatrix[i][j] +=
                     keyMatrix[i][x] * messageVector[x][j];
            }

            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}


string HillCipher(string message, string key)
{

    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);

    int messageVector[3][1];


    for (int i = 0; i < 3; i++)
        messageVector[i][0] = (message[i]) % 65;

    int cipherMatrix[3][1];

    encrypt(cipherMatrix, keyMatrix, messageVector);

    string CipherText;

      for (int i = 0; i < 3; i++)
        CipherText += cipherMatrix[i][0] + 65;



    return CipherText;
}

        /* Decryption*/

int inverse(int b)
{
	int inv;
	int q, r, r1 = 26, r2 = b, t, t1 = 0, t2 = 1;

	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	if (r1 == 1) {
		inv = t1;
		if (inv < 0)
			inv = inv + 26;
		return inv;
	}

	return -1;
}

void inverseMatrix(int key[][3], int inv[][3])
{
	int C[3][3]; // matrix for cofactors of  key[][]
	int A[3][3]; // matrix for adjoint of C[][]

	C[0][0] = key[1][1] * key[2][2] - key[2][1] * key[1][2];
	C[0][1] = -(key[1][0] * key[2][2] - key[2][0] * key[1][2]);
	C[0][2] = key[1][0] * key[2][1] - key[1][1] * key[2][0];
	C[1][0] = -(key[0][1] * key[2][2] - key[2][1] * key[0][2]);
	C[1][1] = key[0][0] * key[2][2] - key[2][0] * key[0][2];
	C[1][2] = -(key[0][0] * key[2][1] - key[2][0] * key[0][1]);
	C[2][0] = key[0][1] * key[1][2] - key[0][2] * key[1][1];
	C[2][1] = -(key[0][0] * key[1][2] - key[1][0] * key[0][2]);
	C[2][2] = key[0][0] * key[1][1] - key[1][0] * key[0][1];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A[i][j] = C[j][i];
		}
	}

	int det = key[0][0] * C[0][0] + key[0][1] * C[0][1] + key[0][2] * C[0][2];

	if (det == 0 || det % 2 == 0 || det % 13 == 0) {
        cout<<"The text cannot be encrypted. Take valid key"<<endl;


	}

	int invs = inverse(det);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			inv[i][j] = A[i][j] * invs;
		}
	}

	//cout<<"\nInverse of a Key-\n"<<endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (inv[i][j] >= 0) {
				inv[i][j] = inv[i][j] % 26;
				//cout<<inv[i][j]<<" ";
			}
			else {
				for (int x = 0;; x++) {
					if (x * 26 + inv[i][j] > 0) {
						inv[i][j] = x * 26 + inv[i][j];
						break;
					}
				}
				//cout<<inv[i][j]<<" ";
			}
		}
		//cout<<endl;
	}
}


string decrypt(string s, int inv[][3])
{

	string d = "";
	int k = 0;
	int input[3];

	while (k < s.length()) {
		input[0] = s[k++] - 65;
		input[1] = s[k++] - 65;
		input[2] = s[k++] - 65;

		for (int i = 0; i < M; i++) {
			int decipher = 0;
			for (int j = 0; j < M; j++) {
				decipher += inv[i][j] * input[j];
			}
			d += (decipher % 26) + 65;
		}
	}
	return d;
}

//RAIL FENCE ENCRYPT DECRYPT

 string railfence(string ch,int k)
    {int n=ch.length();int j,d,t=0,i;
	string b;char a[k][n];
    for(i=0;i<k;i++)
    for(j=0;j<n;j++)
    a[i][j]='\0';;
    //actual function
    j=0;d=0;
    for(i=0;i<n;i++)
    {	if(t==0)
    	{
    	a[d][i]=ch[i];
    	d++;
    	if(d==k-1)
    	t=1;
		}
		else if(t==1)
		{
		a[d][i]=ch[i];
		d--;
		if(d==0)
		t=0;
		}

	}
    //
	for(i=0;i<k;i++)
    for(j=0;j<n;j++)
    {
    if(a[i][j]!='\0')
    b.push_back(a[i][j]);
	}
    return b;
}
string decryptRailFence(string cipher, int key)
{
    int len=cipher.length();
    char rail[key][len];

    for (int i=0; i < key; i++)
        for (int j=0; j < len; j++)
            rail[i][j] = '\n';

    bool flag;

    int row = 0, col = 0;

    for (int i=0; i < len; i++)
    {
        if (row == 0)
            flag = true;
        if (row == key-1)
            flag = false;

        rail[row][col++] = '*';

        flag?row++ : row--;
    }

    int index = 0;
    for (int i=0; i<key; i++)
        for (int j=0; j<len; j++)
            if (rail[i][j] == '*' && index<len)
                rail[i][j] = cipher[index++];

    string result;

    row = 0, col = 0;
    for (int i=0; i< len; i++)
    {
        if (row == 0)
            flag = true;
        if (row == key-1)
            flag = false;

        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        flag?row++: row--;
    }
    return result;
}

int main()
{


    cout<<endl;
    cout<<"\n------RAIL FENCE CIPHER------\n";
    string text;
    cout<<"\nEnter text to be encrypted:";
    getline(cin,text);
    //cin>>text;
    int k;
    cout<<"\nEnter Key: ";
    cin>>k;
    string b=railfence(text,k);
    cout<<"\nEncrypted text:"<<railfence(text,k);
    cout<<"\nDecrypted text: "<<decryptRailFence(b,k);

    cout<<endl;
    cout<<"\n------HILL CIPHER-------\n";
    string message;
    cout<<"\nEnter the text to be encrypted:";
    cin>>message;
    string key;
    cout<<"\nEnter the key:";
    cin>>key;
    string ciphertext = HillCipher(message, key);
    cout<<"\nEncrypted Text: "<<ciphertext<<endl;
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);
    int inv[3][3];
	inverseMatrix(keyMatrix, inv);
    cout << "\nDecrypted Text: " << decrypt(ciphertext, inv);

    return 0;
}
