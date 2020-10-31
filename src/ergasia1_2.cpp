#include <iostream>
#include <ctime>


static const int Tests=20;


int int_checksum(unsigned int a){
	int result=0;
	int digitarray [10]={ };
	int i=0;

	int temp;

	while(a>0){//digit array has the decimal value of each digit with [0] being the rightmost
	   digitarray[i]=a%10;	
		a/=10;
		i++;
	}
	for(i = 0; i<10; ++i){
		temp=digitarray[i]*((i%2)+1);//the expression in the () multiplies it by 2 every 2nd iteration of the loop
		if(temp>9)
			result=result +temp%10 +1;//since the maximum value that temp can take is 2*9, adding 1 covers all cases
		else
			result=result+temp;
	}
	return result;
}


int main(){
	unsigned int Test_array [Tests];
	std::srand(std::time(NULL));
	std::cout<<int_checksum(3561)<<std::endl;
	for (int i = 0; i < Tests; ++i){
		Test_array[i]=std::rand();
		std::cout<<Test_array[i]<<std::endl;
		std::cout<<int_checksum(Test_array[i])<<std::endl;
	}
}
