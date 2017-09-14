#include "../include/bignum.h" //实现头文件
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
int main(){

	cout <<Bignum("9") + Bignum("9")<<endl;
	Bignum b("123456789");
	cout << b <<endl;
	cout <<"100+303:" <<Bignum("100") +Bignum("303") << endl;
	cout <<Bignum("99999")-Bignum("99999")<< endl;
	cout <<"10+30:"<< Bignum("10") + Bignum("30") << endl;
	cout <<"-10+(-9):"<< Bignum("-10") + Bignum("-9")  << endl;
	cout <<"-10+20:"<< Bignum("-10") + Bignum("20")  << endl;
	cout <<"10+(-10010):"<< Bignum("10") + Bignum("-10010")  << endl;
	cout <<"-100+(-900):"<< Bignum("-100") + Bignum("-900")  << endl;
	cout <<"-10000+900:"<< Bignum("-10000") + Bignum("900")  << endl;
	cout <<"-100000-(-100):"<< Bignum("-100000") - Bignum("-100") <<endl;
	cout <<"-1000-100:"<< Bignum("-1000") - Bignum("100") <<endl;
	cout <<"0-(-100):"<< Bignum("0") - Bignum("-100") <<endl;
	cout <<"-100-(-900):"<< Bignum("-100") - Bignum("-900")  << endl;
	cout <<"100-900):"<< Bignum("100") - Bignum("900")  << endl;
	cout << Bignum("-1111111111" )-Bignum("9999999999") << endl;
	cout << Bignum("-1999" )-Bignum("1") << endl;
	cout << Bignum("-1999" )-Bignum("2000") << endl;
	cout << Bignum("-99999" )-Bignum("99999") << endl;
	cout <<Bignum("99999")-Bignum("99999")<< endl;
	cout << Bignum("15")*(Bignum("15")) <<endl;
	cout << Bignum("5000")*(Bignum("5000")) <<endl;
	cout << Bignum("0")*(Bignum("0")) <<endl;
	cout << Bignum("99999")*(Bignum("99999")) <<endl;
	cout << Bignum("-99999999999999")*Bignum("-99999999999") <<endl;
	cout << Bignum("-99999999999999")*Bignum("99999999999") <<endl;
	cout << Bignum("99999999999999")*Bignum("-99999999999") <<endl;
	cout << Bignum("99999999999")*Bignum("999999999") <<endl;
	cout << Bignum("1000000000")*Bignum("1000000000") <<endl;
	cout << Bignum("455614313003")*Bignum("81436131") <<endl;
	cout << Bignum("55654165153610445")*Bignum("49846514651421564561") <<endl;
	cout << Bignum("55654165153610445")*Bignum("49846514651464561") <<endl;
	cout << Bignum("4294967296")<<endl;
	cout <<(size_t) -1<<endl;
	cout << Bignum("99999")/Bignum("11111") <<endl;
	cout << Bignum("99999999999999")/Bignum("111") <<endl;
	cout << Bignum("123456789987654321")/Bignum("98765432112345678") <<endl;
	cout << Bignum("45614561131456153145123321231")/Bignum("555") <<endl;
}
