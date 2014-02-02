/*
  ==============================================================================

    StereoEnhancer.cpp
    Created: 2 Feb 2014 10:53:20am
    Author:  Aneesh

  ==============================================================================
*/

#include "StereoEnhancer.h"

StereoEnhancer::StereoEnhancer()
{
	setWidth(1.0f);
}

StereoEnhancer::~StereoEnhancer()
{

}

void StereoEnhancer::setWidth(float newWidth)
{
	width = newWidth;
	float temp;
	if(1.0f+width>2.0f)
	{
		temp = 1.0f/(1.0f+width);
	}

	diffGain = width*temp;
	sumGain = temp;
}

void StereoEnhancer::clockProcess(float* leftSample, float* rightSample)
{
	float m = sumGain*(*leftSample + *rightSample);
	float s = diffGain*(*rightSample - *leftSample);
	*leftSample = m-s;
	*rightSample = m+s;
}


