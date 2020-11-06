#include <ctime>
#include <iostream>

#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

static const int TestNum=20;

void runlength_encode(ac_channel<ac_int<4, false> > &in,ac_channel<ac_int<4, false> > &out){
    ac_int<4, false> data;
    ac_int<4, false> outint,outcount;
    if(in.available(10)){
        
        
        for(int i=0;i<10;++i){
            data=in.read();
            //std::cout<<"Data in read: "<<data<<std::endl;
            if(outcount==0){//an den uparxei prohgoumeno gia na sugrinw
                outint=data;
                outcount=1;
            }
            else{//an uparxei prohgoumeno
                if(data==outint){//an to prohgoumeno pshfio einai idio me to twrino
                    ++outcount;
                }
                else{//an to prohgoumeno einai diaforetiko
                    out.write(outint);
                    out.write(outcount);//pernw tis prohgoumenes times sto outstream
                    //std::cout<<"Data out read: "<<outint<<std::endl;
                    //std::cout<<"Count out read: "<<outcount<<std::endl;
                    outint=data;//kai grafw tiw kainourgies times stis topikes metavlhtes
                    outcount=1;
                }
            }
            if(i==9){
                out.write(outint);
                out.write(outcount);
                //std::cout<<"Data out read: "<<outint<<std::endl;
                //std::cout<<"Count out read: "<<outcount<<std::endl;
            }
        
        }       
    }
}

int main(){
    std::srand(std::time(NULL));
    int arr[10];
    ac_channel<ac_int<4, false> > in_stream;
    ac_channel<ac_int<4, false> > out_stream;

    
    for (int i=0;i<TestNum;++i){
        for(int j=0;j<10;++j){
            arr[j]=std::rand()/(RAND_MAX/16);//assigns random values 0-15 
            std::cout<<arr[j]<<" "<<std::endl;
        }
        
        for(int j=0;j<10;++j){
            in_stream.write(arr[j]);
        }
        while(in_stream.available(10)){
            runlength_encode(in_stream,out_stream);
        }
        while(out_stream.available(1)){
            std::cout<<out_stream.read()<<" ";
        }
        std::cout<<"\n";
    }
    return 0;

}