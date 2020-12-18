#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

#include "mc_scverify.h"
static const int RUNS = 10;

static const int n = 12;//up to 48

#pragma hls_design top
void  Graph_Colouring( ac_int<n,false> neigh [n][n],ac_int<n,false> result[n],int &diffcols){  
    
	//initialization of data == setting everything to 0
	int return_col=0;
	int size=0;
    ac_int<n,false> ncolours[n];
    int c=0;
    bool colourfound=0;
    /*for (int x=0;x<n;++x){
        ncolours[x]=0;
    }*/
          
    for(int i=0;i<n;++i){
        for (int x=0;x<n;++x){
            ncolours[x]=neigh[i][x] * result[x];//temp array of colours of neighbours
        }
        
        c=1;
        colourfound=1;
        
        while(colourfound){
            for (int j=0;j<n;j++){//checks if a neighbour has the colour
                if(ncolours[j]==c)c+=1;
                else colourfound=0;
            }
        }
		result[i]=c;
		if(c>return_col)return_col=c;
    };
    /*for(int y = 0;y<n;++y){//assignment of values to return array
		result[y]=colours[y];
		if(colours[y]>return_col)return_col=colours[y];
	}*/
	diffcols=return_col;//assignment of colour to return value
}


CCS_MAIN(int argc, char* argv[]){
	std::srand(std::time(NULL));
    ac_int<6,false> neigh [6][6]={
        {0,1,0,0,1,1},
        {1,0,1,0,0,1},
        {0,1,0,1,0,0},
        {0,0,1,0,1,0},
        {1,0,0,1,0,1},
        {1,1,0,0,1,0}
    };

    
    /*
    
    ac_int<n,false> result [n];
    int colour=0;
    Graph_Colouring(neigh,result,colour);
    for(int y = 0;y<n;++y){
		std::cout<<result[y];
	}
	std::cout<<std::endl<<colour;
    */
    
    
    for (int k=0;k<RUNS;++k){
		ac_int<n, false> Adj_G[n][n];
  		for(int i = 0;i <n;i++){
    		for(int j = i;j < n;j++){
      			if(i == j){
        			Adj_G[i][j] = 0; 
      			}
				else{
	    			Adj_G[i][j] = std::rand()&1;
        			Adj_G[j][i] = Adj_G[i][j]; 
        			if(std::rand()&3==1) {//more 1 to artificialy inflate the required colours, adjust accordingly
						Adj_G[i][j]=1;
						Adj_G[j][i]=1;
					}
      			}
    		}
    	}
		int colour=0;
		ac_int<n,false> result [n];
    	Graph_Colouring(Adj_G,result,colour);
    	for(int f = 0;f<n;++f){
			std::cout<<result[f];
		}
		std::cout<<std::endl<<colour<<std::endl;
    }
	
	CCS_RETURN(0);
}
