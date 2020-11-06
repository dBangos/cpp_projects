#include <ctime>
#include <iostream>

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

typedef ac_int<4,false> Card;

static const int TestNum=20;

class BlackJack{
private:
    Card data;
    ac_int<3,false> count;
    ac_int<5,false> sum;
    bool ace_flag;
public:
    BlackJack(){//reset
        sum=0;
        count=0;
        ace_flag=false;
    }
    void run(ac_channel<Card> &in_card, bool &end_round, bool &win){
        while(in_card.available(1)){
            data=in_card.read();
            //std::cout<<"Data: "<<data<<std::endl;
            if(data==1){//if an ace appears
                ++count;
                sum=sum+11;
                if(count==1){
                    ace_flag=true;
                }
                else if(count==2 && ace_flag==true){
                    win=true;
                    end_round=true;
                    //std::cout<<"Break1"<<std::endl;
                    break;
                }
            }
            else{
                sum=sum+data;
                ++count;
            }
            //std::cout<<"Sum: "<<sum<<std::endl;
            //std::cout<<"Count: "<<count<<std::endl;
            if(sum==21 || (count==5 && sum<21)){
                win=true;
                end_round=true;
                //std::cout<<"Break2"<<std::endl;
                break;
            }
            else if(sum>21){
                win=false;
                end_round=true;
                //std::cout<<"Break3"<<std::endl;
                break;
            }
        }
    }//run
};//class
int testing(int *outsidearray){//function that passes an array to class Blackjack and prints the results
    ac_channel<Card> in_stream;
    BlackJack instance1;//creating class object, resets previous instance
    bool win=0,end=0;
    for(int j=0;j<5;++j){
        std::cout<<outsidearray[j]<<" ";
        in_stream.write(outsidearray[j]);
    }
    std::cout<<"\n";
    while(in_stream.available(1)){
        instance1.run(in_stream,end,win);
        std::cout<<end<<""<<win<<" "<<std::endl;
        if(win==1){
            std::cout<<"Win"<<std::endl;
            win=0;
            end=0;
            break;
        }
        else if(end==1){
            std::cout<<"Defeat"<<std::endl;
            win=0;
            end=0;
            break;
        }
    }
    std::cout<<"\n";
};

int main(){
    std::srand(std::time(NULL));
    int arr[5];
    for (int j=0;j<TestNum;++j){
        for(int i=0;i<5;++i){
            arr[i]=1+std::rand()/(RAND_MAX/10);//assigns random values 1-10
        }
        testing(arr);
    }
    int arr2[]={1,1,5,6,7};//testing 2 aces scenario
    testing(arr2);
  
    int arr3[]={2,2,2,2,2};//testing win by 5 ammount of cards scenario
    testing(arr3);
    
    int arr4[]={9,9,3,5,5};//testing win by score 21
    testing(arr4);
    return 0;
    
}