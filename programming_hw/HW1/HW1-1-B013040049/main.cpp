#include <iostream>

using namespace std;

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Sep.30,2013*/
/*目的: OOP Homework 1-1*/

int main()
{
    int a,b,c,d,e,f;

    double money,registration,road_tax,insurance,extended_warranty,service_tax,on_road_price; /*待算項目*/

    cin >> money; /*輸入金錢*/

    registration = money*0.04; /*費率計算*/
    road_tax = money*0.02;
    insurance = money*0.025;
    extended_warranty = money*0.0125;
    service_tax = (registration+road_tax+insurance+extended_warranty)*0.12;
    on_road_price = registration+road_tax+insurance+extended_warranty+service_tax+money;

    a = (int)(registration+0.5); /*四捨五入*/
    b = (int)(road_tax+0.5);
    c = (int)(insurance+0.5);
    d = (int)(extended_warranty+0.5);
    e = (int)(service_tax+0.5);
    f = (int)(on_road_price+0.5);

    cout << "registration : " << a << endl /*輸出*/
         << "road_tax : " << b << endl
         << "insurance : " << c << endl
         << "extended_warranty : " << d << endl
         << "service_tax : " << e << endl
         << "on_road_price : " << f;

    return 0;
}
