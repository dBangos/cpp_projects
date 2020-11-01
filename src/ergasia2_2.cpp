#include <ctime>
#include <iostream>

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"
static const int TestNum=20;

template <int W>

void csd_encode(ac_int<W,true> &num, ac_int<W,false> &x_p, ac_int<W,false> &x_n){
     int i = 0;
     int carry = 0;//Wether the previously examined bit was 1
     while(i<W){
         if (carry==0){
             if(num[i]==0){
                 x_p[i]=0;
                 x_n[i]=0;
                 carry=0;
                 if(i==6) std::cout<<"1"<<std::endl;
             }
             else if(num[i+1]==0){
                 x_p[i]=1;
                 x_n[i]=0;
                 carry=0;
                 if(i==6) std::cout<<"2"<<std::endl;
             }
             else{
                 x_p[i]=0;
                 x_n[i]=1;
                 carry=1;
                 if(i==6) std::cout<<"3"<<std::endl;
             }
         }
        else {
            if(num[i]==1){
                x_p[i]=0;
                x_n[i]=0;
                carry=1;
                if(i==6) std::cout<<"4"<<std::endl;
            }
            else if(num[i+1]==0){
                x_p[i]=1;
                x_n[i]=0;
                carry=0;
                if(i==6) std::cout<<"5"<<std::endl;
            }
            else{
                x_p[i]=0;
                x_n[i]=1;
                carry=1;
                if(i==6) std::cout<<"6"<<std::endl;
            }
        }
     ++i;

     }
}
int main(){
    std::srand(std::time(NULL));
    for (int i = 0;i<TestNum;++i){
        ac_int<8, true> a;
        ac_int<8, false> b;
        ac_int<8, false> c;
        a=std::rand();
        csd_encode(a,b,c);
        std::cout<<a<<" "<<b<<" "<<c<<std::endl;
    }
}