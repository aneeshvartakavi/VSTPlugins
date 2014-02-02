/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StereoEnhancerAudioProcessor::StereoEnhancerAudioProcessor()
{
	UserParams[MasterBypass] = 0.0f;
	UserParams[StereoWidth] = 1.0f;
	stereoEnhancer.setWidth(UserParams[StereoWidth]);
	UIUpdateFlag = true;
}

StereoEnhancerAudioProcessor::~StereoEnhancerAudioProcessor()
{
}

//==============================================================================
const String StereoEnhancerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StereoEnhancerAudioProcessor::getNumParameters()
{
	return totalNumParam;
}

float StereoEnhancerAudioProcessor::getParameter (int index)
{
	switch (index)
	{
	case MasterBypass:
		return UserParams[MasterBypass];
	case StereoWidth:
		UserParams[StereoWidth] = stereoEnhancer.getWidth();
		return UserParams[StereoWidth];
	default:
		return 0.0f;
	}
}

void StereoEnhancerAudioProcessor::setParameter (int index, float newValue)
{
	switch(index)
	{
	case MasterBypass:
		UserParams[MasterBypass]=newValue;
		break;
	case StereoWidth:
		UserParams[StereoWidth]=newValue;
		stereoEnhancer.setWidth(UserParams[StereoWidth]);
	break;
	default: 
		return;
	}

}



const String StereoEnhancerAudioProcessor::getParameterName (int index)
{
    switch(index)
	{
	case MasterBypass: return "Master Bypass";
	case StereoWidth: return "Stereo Width Factor";
	default:return String::empty;
	}
}

const String StereoEnhancerAudioProcessor::getParameterText (int index)
{
    if(index>=0 && index<totalNumParam)
	return String(UserParams[index]);//return parameter value as string
	else return String::empty;
}

const String StereoEnhancerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String StereoEnhancerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool StereoEnhancerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool StereoEnhancerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool StereoEnhancerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoEnhancerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoEnhancerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double StereoEnhancerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoEnhancerAudioProcessor::getNumPrograms()
{
    return 0;
}

int StereoEnhancerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoEnhancerAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoEnhancerAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void StereoEnhancerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoEnhancerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StereoEnhancerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void StereoEnhancerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
	if(getNumInputChannels()<2||UserParams[MasterBypass])
	{
		// Do nothing, output = input
	}

	else
	{
		// Process!
		float* leftChannel = buffer.getSampleData(0);
		float* rightChannel = buffer.getSampleData(1);

		for(int i=0; i<buffer.getNumSamples(); i++)
		{
			stereoEnhancer.clockProcess(&leftChannel[i],&rightChannel[i]);
		}

	}

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool StereoEnhancerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoEnhancerAudioProcessor::createEditor()
{
    return new StereoEnhancerAudioProcessorEditor (this);
}

//==============================================================================
void StereoEnhancerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	XmlElement root("Root");
	XmlElement *el;
	el = root.createNewChildElement("Bypass");
	el->addTextElement(String(UserParams[MasterBypass]));
	el = root.createNewChildElement("StereoWidth");
	el->addTextElement(String(UserParams[StereoWidth]));
	copyXmlToBinary(root,destData);

}

void StereoEnhancerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	XmlElement* pRoot = getXmlFromBinary(data,sizeInBytes);
	if(pRoot!=NULL)
	{
		forEachXmlChildElement((*pRoot),pChild)
		{
			if(pChild->hasTagName("Bypass"))
			{
				String text = pChild->getAllSubText();
				setParameter(MasterBypass,text.getFloatValue());
			}
			else if(pChild->hasTagName("StereoWidth"))
			{
				String text = pChild->getAllSubText();
				setParameter(StereoWidth,text.getFloatValue());
			}
			delete pRoot;
			UIUpdateFlag=true;//Request UI update
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoEnhancerAudioProcessor();
}
