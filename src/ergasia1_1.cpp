#include <iostream>
#include <ctime>


 
static const int Tests=20;
 
int counting_function(unsigned int a){
	unsigned short int counter=0;
	while(a>=1){
		if (a%2==1) ++counter;
		a=a/2;	
	}
	return counter;
}
 
int main(){
	unsigned int Test_array [Tests];
	std::srand(std::time(NULL));
	for (int i = 0; i < Tests; ++i){
		Test_array[i]=std::rand();
		std::cout<<Test_array[i]<<std::endl;
		std::cout<<counting_function(Test_array[i])<<std::endl;

	}
}
