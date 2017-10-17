#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

using namespace std;

/*�@�̩m�W: B013040049 ����*/
/*���g���: Oct.18,2013*/
/*�ت�: Use C++ to make a set class that can do union�Aintersection�Adifference�Acontain */

class mike /*�ŧi�@�ӥs��mike��class*/
{

	private:
		int _string[256];
	public:
		mike();
		mike operator+(mike point); /*�����B��l+*/
		mike operator*(mike point); /*�����B��l**/
		mike operator-(mike point); /*�����B��l-*/
		int operator>=(mike point); /*�����B��l>=*/
		unsigned int innotin(int num); /*�P�_contain or no*/

		void get_string(unsigned char tempmike); /*�o��r��*/
		void print(); /*�L�X*/
		void initial(); /*��l��*/

};

int main(void)
{
	mike A,B,C,D,E,F,G;
	char temp[2];
    unsigned char a,b;
	int contain,time,i; /*time��ܭn��J�X�մ���*/

    cout<< "Times: ";
	cin >> time; /*��J�ռ�*/

	for(i=0;i<time;i++)
	{
	    cin.ignore();

	    while(scanf("%c",&a)!= EOF && a!='\n'){
            A.get_string(a);
	    }

	    while(scanf("%c",&b)!= EOF && b!='\n'){
            B.get_string(b);
	    }

	    cin.get(temp[0]);

		C = A+B; /*OR�޿�B��*/
		D = A*B; /*And�޿�B��*/
		E = A-B; /*And Not B�޿�B��*/
		F = B-A; /*And Not A�޿�B��*/

        cout << "TestCase" << i+1 << ":" << endl;
		cout << "A:"; /*��X���XA*/
		A.print();
		cout << "B:"; /*��X���XB*/
		B.print();
		cout << "A+B:"; /*��X�ⶰ�X���p��*/
		C.print();
		cout << "A*B:"; /*��X�ⶰ�X���涰*/
		D.print();
		cout << "A-B:"; /*��X�ⶰ�X���t��*/
		E.print();
		cout << "B-A:"; /*��X�ⶰ�X���t��*/
		F.print();

	    contain=A>=B; /*�P�_A�O�_�]�tB*/
        if(contain==-1)
            cout << "A contains B" << endl;
	    else
	        cout << "A does not contain B" << endl;

    	contain=B>=A; /*�P�_B�O�_�]�tA*/
    	if(contain==-1)
    		cout << "B contains A" << endl;
    	else
    		cout << "B does not contain A" << endl;

    	if(A.innotin((int)temp[0])==1) /*�P�_����C�O�_�bA��*/
    		cout << "'" << temp[0] << "'" << " is in A" << endl;
    	else
    		cout << "'" << temp[0] << "'" << " is not in A" << endl;

    	if(B.innotin((int)temp[0])==1) /*�P�_����C�O�_�bB��*/
    		cout << "'" << temp[0] << "'" << " is in B" << endl;
    	else
    		cout << "'" << temp[0] << "'" << " is not in B" << endl;

        cout << endl;

    	A.initial(); /*��l��*/
    	B.initial(); /*��l��*/

	}

    return 0;
}

mike::mike()
{
    int i;
	for(i=0;i<256;i++)
		_string[i]=0;
}

void mike::print() /*��X*/
{
	unsigned char temp;
	int i;
    cout << "{";
	for(i=0;i<256;i++){
		if(_string[i]==1){
			temp=i;
			cout << temp;
		}
	}
	cout << "}" << endl;
}

void mike::get_string(unsigned char tempmike) /*��J���r��*/
{
    _string[(int)tempmike]=1; /*��ASCII CODE�X�ƦC*/
}

mike mike::operator+(mike point) /*�����B��l+*/
{
	int i;
	mike temp;

	for(i=0;i<256;i++){
		if ((_string[i]==1) || (point._string[i]==1)){ /*��OR(��)*/
			temp._string[i]=1;
		}
	}
	return temp;
}

mike mike::operator*(mike point) /*�����B��l**/
{
	int i;
	mike temp;

	for(i=0;i<256;i++){
		if((_string[i]==1) && (point._string[i]==1)){ /*��AND(�B)*/
			temp._string[i]=1;
		}
	}
	return temp;
}

mike mike::operator-(mike point) /*�����B��l-*/
{
	int i;
	mike temp;

	for(i=0;i<256;i++){
		if(_string[i]==1){
			temp._string[i]=1;
		}
		if(point._string[i]==1){
			temp._string[i]=0;
		}
	}
	return temp;
}

int mike::operator>=(mike point) /*�����B��l>=*/
{
    int i;
	int j=0;

	for(i=0;i<256;i++){
		if(point._string[i]==1){
        if(_string[i]!=1){
				j=1;
        }
		}
	}
	if(j==1){
		return 1;
	}
	else if(j==0){
		return -1;
	}
	else
	return 0;
}

void mike::initial() /*class��l��*/
{
    int i;

	for(i=0;i<256;i++){
		_string[i]=0;
	}
}

unsigned int mike::innotin( int num) /*�^�ǬO�_�b�䤤*/
{
    unsigned char num1;
    if(num<0){
    num1 = num +256;
    num = num1;
    }
    if(_string[num]==1){
                return 1;
                }
                else{
                    return 0;
                }
}
