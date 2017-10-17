#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

using namespace std;

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Oct.18,2013*/
/*目的: Use C++ to make a set class that can do union，intersection，difference，contain */

class mike /*宣告一個叫做mike的class*/
{

	private:
		int _string[256];
	public:
		mike();
		mike operator+(mike point); /*重載運算子+*/
		mike operator*(mike point); /*重載運算子**/
		mike operator-(mike point); /*重載運算子-*/
		int operator>=(mike point); /*重載運算子>=*/
		unsigned int innotin(int num); /*判斷contain or no*/

		void get_string(unsigned char tempmike); /*得到字串*/
		void print(); /*印出*/
		void initial(); /*初始化*/

};

int main(void)
{
	mike A,B,C,D,E,F,G;
	char temp[2];
    unsigned char a,b;
	int contain,time,i; /*time表示要輸入幾組測資*/

    cout<< "Times: ";
	cin >> time; /*輸入組數*/

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

		C = A+B; /*OR邏輯運算*/
		D = A*B; /*And邏輯運算*/
		E = A-B; /*And Not B邏輯運算*/
		F = B-A; /*And Not A邏輯運算*/

        cout << "TestCase" << i+1 << ":" << endl;
		cout << "A:"; /*輸出集合A*/
		A.print();
		cout << "B:"; /*輸出集合B*/
		B.print();
		cout << "A+B:"; /*輸出兩集合之聯集*/
		C.print();
		cout << "A*B:"; /*輸出兩集合之交集*/
		D.print();
		cout << "A-B:"; /*輸出兩集合之差集*/
		E.print();
		cout << "B-A:"; /*輸出兩集合之差集*/
		F.print();

	    contain=A>=B; /*判斷A是否包含B*/
        if(contain==-1)
            cout << "A contains B" << endl;
	    else
	        cout << "A does not contain B" << endl;

    	contain=B>=A; /*判斷B是否包含A*/
    	if(contain==-1)
    		cout << "B contains A" << endl;
    	else
    		cout << "B does not contain A" << endl;

    	if(A.innotin((int)temp[0])==1) /*判斷元素C是否在A中*/
    		cout << "'" << temp[0] << "'" << " is in A" << endl;
    	else
    		cout << "'" << temp[0] << "'" << " is not in A" << endl;

    	if(B.innotin((int)temp[0])==1) /*判斷元素C是否在B中*/
    		cout << "'" << temp[0] << "'" << " is in B" << endl;
    	else
    		cout << "'" << temp[0] << "'" << " is not in B" << endl;

        cout << endl;

    	A.initial(); /*初始化*/
    	B.initial(); /*初始化*/

	}

    return 0;
}

mike::mike()
{
    int i;
	for(i=0;i<256;i++)
		_string[i]=0;
}

void mike::print() /*輸出*/
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

void mike::get_string(unsigned char tempmike) /*輸入之字串*/
{
    _string[(int)tempmike]=1; /*照ASCII CODE碼排列*/
}

mike mike::operator+(mike point) /*重載運算子+*/
{
	int i;
	mike temp;

	for(i=0;i<256;i++){
		if ((_string[i]==1) || (point._string[i]==1)){ /*做OR(或)*/
			temp._string[i]=1;
		}
	}
	return temp;
}

mike mike::operator*(mike point) /*重載運算子**/
{
	int i;
	mike temp;

	for(i=0;i<256;i++){
		if((_string[i]==1) && (point._string[i]==1)){ /*做AND(且)*/
			temp._string[i]=1;
		}
	}
	return temp;
}

mike mike::operator-(mike point) /*重載運算子-*/
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

int mike::operator>=(mike point) /*重載運算子>=*/
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

void mike::initial() /*class初始化*/
{
    int i;

	for(i=0;i<256;i++){
		_string[i]=0;
	}
}

unsigned int mike::innotin( int num) /*回傳是否在其中*/
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
