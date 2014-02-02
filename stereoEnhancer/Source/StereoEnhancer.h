/*
  ==============================================================================

    StereoEnhancer.h
    Created: 2 Feb 2014 10:53:20am
    Author:  Aneesh

  ==============================================================================
*/

#ifndef STEREOENHANCER_H_INCLUDED
#define STEREOENHANCER_H_INCLUDED

class StereoEnhancer
{
public:
	StereoEnhancer();
	~StereoEnhancer();

	void setWidth(float width);
	float getWidth()
	{
		return width;
	}

	void clockProcess(float* leftSample, float* rightSample);

private:
	float width, sumGain,diffGain;

};




#endif  // STEREOENHANCER_H_INCLUDED
