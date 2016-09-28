#pragma once
#include <stdlib.h>
#include <assert.h>

//generate a random integer r where min <= r <max
//distribution is uniform (each value is equally likely)
int rand_between(int min, int max){
	assert(max>min);
	//first generate int between 0 and (max-min)
	int range = max-min;
	//find largest multiple of range that's less than RAND_MAX
	int LARGEST_MULTIPLE = (RAND_MAX/range)*range;

	//Generate random number that's less than LARGEST_MULTIPLE
	int r;
	do{
		r = rand();
	}while(r>=LARGEST_MULTIPLE);

	//this ensures uniform distribution when we use modulo operator
	r = r%range;
	r+=min;
	return r;
}

//generate a random float between 0 and 1
//naiive method; non-uniform
float randf(){
	return (float)rand()/RAND_MAX;
}

//generate a random float r where min <= r < max
//naiive method; we're just stretching randf result so 
//lots of values are impossible
float rand_betweenf(float min, float max){
	assert(max>min);
	float r = (max-min)*randf(); // 0 <= r < (max-min)
	return r+min;
}
