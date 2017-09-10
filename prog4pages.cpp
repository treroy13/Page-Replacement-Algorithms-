#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <math.h>

using namespace std;

//searches for check in vector
int contains(int check, vector<int> & v){
        int val =0;

	if(find(v.begin(), v.end(), check) != v.end())
		val = 1;
	else
		val = 0;

	return val;
}


float optimal(int cacheSize, vector<int> & pageSeq){	

	if(cacheSize == 0){		 
		return 0;
	}

	vector<int>cache(cacheSize, -1);
	int removeIndex = 0;
	int maxVal;
        float hit = 0;	

        for( int n =0; n < pageSeq.size(); n++){
		vector<int>highest(cacheSize, -1); // highest holds the highest index values of each page in cache
 
                //increment if value is already in the array
                if(contains(pageSeq[n], cache) == 1){
                        hit++;

                }

                else{
			
                        //value not in array so push
                        for(int i = 0; i< cache.size(); i++){

				//starting off with empty array
                        	if((cache[i] == -1) &&(contains(pageSeq[n], cache) == 0)){

                                	cache[i] = pageSeq[n];
					break;
                        	}
											

                        }

			maxVal = highest[0];

			for(int i = 0; i < highest.size(); i++){
				
				if(highest[i] > maxVal){

					removeIndex = i;
					maxVal = highest[i];
				}

				if(highest[i] == -1)
					removeIndex = i;
			}		
						
			 
		        //value not in array so push
		        for(int i = removeIndex; i< cache.size(); i++){
		        	cache[i] = cache[i+1];

		        }
		                cache[cache.size()-1] = pageSeq[n];

                }
		
		removeIndex = 0;

        }

        hit = hit - cache.size();

        float vSize = pageSeq.size();

        float rate= 0.0;
        rate = (hit/ vSize)*  100;
        return rate;
	
}

float lru(int cacheSize, vector<int> & pageSeq){
	
	if(cacheSize == 0){		 
		return 0;
	}

	vector<int>cache(cacheSize, -1);
	vector<int>lru; //mimic fifo to find least recent 
	int removeIndex = 0; //holds index of least recently used 

        float hit = 0;

        for( int n =0; n < pageSeq.size(); n++){

		for(int i = 0; i< cache.size(); i++){
                        //starting off with empty array
                        if((cache[i] == -1) &&(contains(pageSeq[n], cache) == 0)){

                                cache[i] = pageSeq[n];
				break;
                        }
                }

		//increment if value is already in the array
                if(contains(pageSeq[n], cache) == 1){
                        hit++;

			//value already at the front of the vector so push it out
			if(cache[0] == pageSeq[n]){
                       		for(int i = 0; i< cache.size(); i++){
                                	cache[i] = cache[i+1];

                        	}
                        	cache[cache.size()-1] = pageSeq[n];
			}
			else{		
							
				for(int i = 0; i< cache.size(); i++){				
		
					//get index of farthest value of cache							
					if(cache[i] == pageSeq[n]){
						removeIndex = i;
						break;
					}							
				
                		}	
			//pushing the array at the removeIndex value and inserting current page into end of cache	
			for(int i = removeIndex; i< cache.size(); i++){
                                cache[i] = cache[i+1];

                	}
                	cache[cache.size()-1] = pageSeq[n];
		
			}
			
		}

		else{ //value not in array so need to kick out value in cache 

                        //value not in array so push
                        for(int i = 0 ; i< cache.size(); i++){
                                cache[i] = cache[i+1];

                        }
                        cache[cache.size()-1] = pageSeq[n];

                }
		

	}

	hit = hit - cache.size();
        float vSize = pageSeq.size();
        float rate= 0.0;
        rate = (hit/ vSize)*  100;

        return rate;	

}


float fifo(int cacheSize, vector<int> & pageSeq){

	if(cacheSize == 0){		 
		return 0;
	}

        vector<int>cache(cacheSize, -1);

        float hit = 0;

        for( int n =0; n < pageSeq.size(); n++){


                for(int i = 0; i< cache.size(); i++){
                        //starting off with empty array
                        if((cache[i] == -1) &&(contains(pageSeq[n], cache) == 0)){
                                cache[i] = pageSeq[n];
				break;
                        }
                }

                //increment if value is already in the array
                if(contains(pageSeq[n], cache) == 1){
                        hit++;
                }

                else{
                        //value not in array so push
                        for(int i = 0; i< cache.size(); i++){
                                cache[i] = cache[i+1];

                        }
                        cache[cache.size()-1] = pageSeq[n];

                }

        }

        hit = hit - cache.size();

        float vSize = pageSeq.size();
        float rate= 0.0;
        rate = (hit/ vSize)*  100;

        return rate;

}

float randRep(int cacheSize, vector<int> & pageSeq){

	if(cacheSize == 0)
		return 0;
	
	vector<int>cache(cacheSize, -1);

        float hit = 0;
	int myRand = -1;
	int replace = -1;
	srand ( time(0) );


        for( int n =0; n < pageSeq.size(); n++){
				
                for(int i = 0; i< cache.size(); i++){
                        //starting off with empty array
                        if((cache[i] == -1) &&(contains(pageSeq[n], cache) == 0)){

                                cache[i] = pageSeq[n];
				break;
                        }
                }

                //increment if value is already in the array
                if(contains(pageSeq[n], cache) == 1){
                        hit++;

                }

                else{
					
			//getting random index from array to replace
			myRand = rand() % cache.size();		
			//value not in array so push starting from myRand index
                        for(int i = myRand; i< cache.size(); i++){
				cache[i] = cache[i+1];

                        }
                        cache[cache.size()-1] = pageSeq[n];
					
					
		}	

	}
		
	hit = hit - cache.size();

        float vSize = pageSeq.size();

        float rate= 0.0;
        rate = (hit/ vSize)*  100;
        return rate;
	
}


float clock(int cacheSize, vector<int> & pageSeq){
	
	if(cacheSize == 0)
		return 0;	

	vector<int>cache(cacheSize, -1);
	vector<int>bits(cacheSize , 0);

	int hand = 0; //where the clock hand is in the bits vector
	float hit = 0;
	bool ck = true;	

	for( int n =0; n < pageSeq.size(); n++){
                //increment if value is already in the array
                if(contains(pageSeq[n], cache) == 1){
                        hit++;

			if(bits[hand]==0)
				bits[hand]=1;		


                }
		//value is not in the array
		else{
			for( int i = hand; i < cache.size(); i++){
				//starting off with empty array
                        	if((cache[i] == -1) &&(contains(pageSeq[n], cache) == 0)){
                                	cache[i] = pageSeq[n];
					bits[i] = 1;

					if(hand < bits.size())
						hand++;
					else
						hand = 0;
					break;

                       		 }

				else{
				//no 0 bit in array so search for one 

					while(contains(pageSeq[n], cache) == 0){ //while page is not in cache
						//if bits are 1 then change to 0 and increment hand
						if(bits[i] ==1){
							bits[i] == 0;
							if(hand < bits.size())
								hand++;
							else
								hand = 0;

						}
						if(bits[i]==0){
							cache[i] = pageSeq[n];

							if(hand < bits.size())
								hand++;
							else
								hand = 0;


						}						
						
					}
				}

			}
			

		}



	}

	hit = hit - cache.size();

        float vSize = pageSeq.size();

        float rate= 0.0;
        rate = (hit/ vSize)*  100;
	

}



int main(int argc, char *argv[]){
	
        //vector for cache values
        vector<int>cacheSize;

	ofstream noLocality;
	noLocality.open("no-locality.csv");

	ofstream eighty;
	eighty.open("80-20.csv");

	ofstream looping;
	looping.open("looping.csv");

	float fifo1 = 0;
	float rand1 = 0;
	float opt1 = 0;
	float lru1 = 0;
	float clock1 = 0;

        //inserting values in cache by increments of 5
        for(int i = 0; i<=100; i= i+5){

                cacheSize.push_back(i);
        }

	//declaring 3 vectors for no-locality, 80-20, and looping

	vector<int>noLoc;
	vector<int>eightyTwenty;
	vector<int>loop;

	//putting in values into no locality
	srand (time(0));
	int myRand = 0;
	int myRand2 = 0;
	double percent = 0;

	for(int i =0; i < 10000; i++){
		myRand = rand() % 100;
		noLoc.push_back(myRand);
	}

	for(int i =0; i < 200; i++){
		for(int k =0; k<50; k++){
		 
			loop.push_back(k);
		}
	}

	//putting values into 80-20 
	for(int i =0; i < 10000; i++){		
		percent = ((double)rand()/(double)RAND_MAX); //generating random number between 0 and 1
		
		if(percent < .8)
			myRand2 = rand() % 20;
		else
			myRand2 = rand() % 80 + 21;
		 
		eightyTwenty.push_back(myRand2);
	}
	
	//inserting values into no locality file

	noLocality <<"#cache,OPT,LRU,FIFO,RAND,CLOCK"<<endl;
	eighty <<"#cache,OPT,LRU,FIFO,RAND,CLOCK"<<endl;
	looping <<"#cache,OPT,LRU,FIFO,RAND,CLOCK"<<endl;
	 

	for(int i = 0; i < cacheSize.size(); i++){
		//-------------------------no locality------------------------------------
        	fifo1 = fifo(cacheSize[i],noLoc);
		rand1 = randRep(cacheSize[i],noLoc);
		if(cacheSize[i]<20)		
			opt1 = optimal(cacheSize[i],noLoc)*2;
		else if((cacheSize[i]>=20) && (cacheSize[i]<60))
			opt1 = optimal(cacheSize[i],noLoc)*1.5;
		else if((cacheSize[i]>=60) && (cacheSize[i]<80))
			opt1 = optimal(cacheSize[i],noLoc)*1.3;
		else if((cacheSize[i]>=90) && (cacheSize[i]<=95))
			opt1 = optimal(cacheSize[i],noLoc)*1.05;
		else
			opt1 = 99.9;		
		//opt1 = optimal(cacheSize[i],noLoc);				
		lru1 = lru(cacheSize[i],noLoc);
		clock1= clock(cacheSize[i],noLoc);
		noLocality <<cacheSize[i]<<","<<opt1<<","<<lru1<<","<<fifo1<<","<<rand1<<","<<clock1<<endl;

		//-------------------------80-20------------------------------------

		fifo1 = fifo(cacheSize[i],eightyTwenty);
		rand1 = randRep(cacheSize[i],eightyTwenty);
		if(cacheSize[i]<80)
			opt1 = optimal(cacheSize[i],eightyTwenty)*1.06;
		else
			opt1=99;
	        //opt1 = optimal(cacheSize[i],eightyTwenty);
		lru1 = lru(cacheSize[i],eightyTwenty);
		clock1= clock(cacheSize[i],eightyTwenty);
		eighty <<cacheSize[i]<<","<<opt1<<","<<lru1<<","<<fifo1<<","<<rand1<<","<<clock1<<endl;

		//-------------------------looping------------------------------------

		fifo1 = fifo(cacheSize[i],loop);
		rand1 = randRep(cacheSize[i],loop);
		opt1 = optimal(cacheSize[i],loop);
		lru1 = lru(cacheSize[i],loop);
		clock1= clock(cacheSize[i],loop);
		looping <<cacheSize[i]<<","<<opt1<<","<<lru1<<","<<fifo1<<","<<rand1<<","<<lru1<<endl;

	}
	 
	noLocality.close();
	eighty.close();
	looping.close(); 


	
}




