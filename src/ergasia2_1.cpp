#include <ctime>
#include <iostream>

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"


static const int TestNum=20;
void int_test(){
	ac_int<8, false> a,b;
	ac_int<9, false>c,d;
	
	a=std::rand();
	b=std::rand();
	c=std::rand();
	d=std::rand();
	ac_int<19, true>e=a*b+c*d;//maxvlaue is 11111111*11111111+11111111*11111111, thus 18+1 bits are needed
	std::cout<<"a= "<<a<<" "<<a.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"b= "<<b<<" "<<b.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"c= "<<c<<" "<<c.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"d= "<<d<<" "<<d.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"e= "<<e<<" "<<e.to_string(AC_BIN, false)<<std::endl;
}
void fixed_test(){
	ac_fixed<5,2,false> f;//min=0 max=3.075
	ac_fixed<5,4 ,true> g;//min=-8 max=7.5
	f=((float)rand()/RAND_MAX)*(-3.075);
	g=((float)rand()/RAND_MAX)*(7.5+8)-8;
	ac_fixed<9,6,true> h=f*g;//maxval 11.111*1111.1
	std::cout<<"f= "<<f<<" "<<f.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"g= "<<g<<" "<<g.to_string(AC_BIN, false)<<std::endl;
	std::cout<<"h= "<<h<<" "<<h.to_string(AC_BIN, false)<<std::endl;
}
int main(){
	std::srand(std::time(NULL));
	for (int i = 0;i<TestNum;++i){
		int_test();
		fixed_test();
	}
}
