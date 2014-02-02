/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoEnhancerAudioProcessorEditor::StereoEnhancerAudioProcessorEditor (StereoEnhancerAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    addAndMakeVisible (WidthControlSlider = new Slider ("Width Slider"));
    WidthControlSlider->setRange (0, 5, 0.1);
    WidthControlSlider->setSliderStyle (Slider::LinearHorizontal);
    WidthControlSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    WidthControlSlider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Stereo Width :")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (BypassButton = new TextButton ("Bypass"));
    BypassButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->requestUIUpdate();
	startTimer(200);
	BypassButton->setClickingTogglesState(true);
    //[/Constructor]
}

StereoEnhancerAudioProcessorEditor::~StereoEnhancerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    WidthControlSlider = nullptr;
    label = nullptr;
    BypassButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoEnhancerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoEnhancerAudioProcessorEditor::resized()
{
    WidthControlSlider->setBounds (32, 64, 150, 24);
    label->setBounds (32, 24, 150, 24);
    BypassButton->setBounds (32, 128, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoEnhancerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	StereoEnhancerAudioProcessor* thisProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == WidthControlSlider)
    {
        //[UserSliderCode_WidthControlSlider] -- add your slider handling code here..
		thisProcessor->setParameter(StereoEnhancerAudioProcessor::StereoWidth,static_cast<float>(WidthControlSlider->getValue()));
        //[/UserSliderCode_WidthControlSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void StereoEnhancerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    StereoEnhancerAudioProcessor* thisProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassButton)
    {
        //[UserButtonCode_BypassButton] -- add your button handler code here..
        //[/UserButtonCode_BypassButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StereoEnhancerAudioProcessorEditor::timerCallback()
{
	StereoEnhancerAudioProcessor* thisProcessor = getProcessor();

	if(thisProcessor->needsUIUpdate())
	{
		BypassButton->setToggleState(1.0f == thisProcessor->getParameter(StereoEnhancerAudioProcessor::MasterBypass),false);
		WidthControlSlider->setValue(thisProcessor->getParameter(StereoEnhancerAudioProcessor::StereoWidth),juce::dontSendNotification);
		thisProcessor->clearUIUpdateFlag();
	}

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoEnhancerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="StereoEnhancerAudioProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Width Slider" id="c964ba2b80636ddc" memberName="WidthControlSlider"
          virtualName="" explicitFocusOrder="0" pos="32 64 150 24" min="0"
          max="5" int="0.10000000000000001" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e8dbf48f71332b40" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="32 24 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Stereo Width :" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Bypass" id="b08dba77fcd423c2" memberName="BypassButton"
              virtualName="" explicitFocusOrder="0" pos="32 128 150 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
