/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "StereoEnhancer.h"

//==============================================================================
/**
*/
class StereoEnhancerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    StereoEnhancerAudioProcessor();
    ~StereoEnhancerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

	//==============================================================================

	enum Parameters{MasterBypass = 0, StereoWidth,totalNumParam};
	bool needsUIUpdate()
	{
		return UIUpdateFlag;
	}

	void requestUIUpdate()
	{
		UIUpdateFlag = true;
	}

	void clearUIUpdateFlag()
	{
		UIUpdateFlag = false;
	}



private:
    //==============================================================================
    
	float UserParams[totalNumParam];
	StereoEnhancer stereoEnhancer;
	bool UIUpdateFlag;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoEnhancerAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
