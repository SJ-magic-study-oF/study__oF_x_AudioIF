/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"


/************************************************************
************************************************************/
enum{
	WIDTH = 1280,
	HEIGHT = 720,
	
	MARGIN = 1,
};
enum{
	NUM_POINTS = WIDTH,
};
enum{
	THREAD_SLEEP_MS = 1,
};

/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class THREAD__DOUBLE : public ofThread{
private:
	double val;
	
	bool b_set;
	double NewVal;

public:
	THREAD__DOUBLE()
	{
		val = 0;
	}

	/******************************
	description
		need lock()/unlock()
	******************************/
	double getVal(){
		return val;
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	void set(double _val){
		if(isThreadRunning()){
			NewVal = _val;
			b_set = true;
		}
	}
	
	void threadedFunction(){
		while(isThreadRunning()) {
			bool b_set_Copy;
			
			lock();
			if(b_set){
				val = NewVal;
				b_set = false;
			}
			b_set_Copy = b_set;
			unlock();
			
			sleep(THREAD_SLEEP_MS);
		}
    }
};

/**************************************************
**************************************************/
class THREAD__VERTS : public ofThread{
private:
	
	ofVec3f Verts[NUM_POINTS];
	
	bool b_set;
	double NewVal;
	
public:
	THREAD__VERTS()
	{
		for(int i = 0; i < NUM_POINTS; i++){
			Verts[i].set(i, 0);
		}
	}

	/******************************
	description
		need lock()/unlock()
	******************************/
	const ofVec3f& operator[] (const int i){
		return Verts[i];
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	double get_Minimum(int samples)
	{
		double min = Verts[NUM_POINTS - 1].y;
		for(int i = 1; i < samples; i++){
			int id = NUM_POINTS - 1 - i;
			
			if(Verts[id].y < min) min = Verts[id].y;
		}
		
		return min;
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	void set(double _val){
		if(isThreadRunning()){
			NewVal = _val;
			b_set = true;
		}
	}
	
	void threadedFunction(){
		while(isThreadRunning()) {
			bool b_set_Copy;
			
			lock();
			b_set_Copy = b_set;
			unlock();
			
			if(b_set_Copy){
				lock();
				
				for(int i = 0; i < NUM_POINTS - 1; i++){
					Verts[i].set(i, Verts[i + 1].y);
				}
				Verts[NUM_POINTS - 1].set(NUM_POINTS - 1, NewVal);
				
				b_set = false;
				
				unlock();
				
			}
			
			sleep(THREAD_SLEEP_MS);
		}
    }
};
