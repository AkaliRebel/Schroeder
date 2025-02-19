/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    roomSizeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(roomSizeSlider);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, processor.roomSizeParamID, roomSizeSlider);

    roomSizeLabel.setText("Room Size", juce::dontSendNotification);
    roomSizeLabel.attachToComponent(&roomSizeSlider, true);
    addAndMakeVisible(roomSizeLabel);

    // Damping Slider
    dampingSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(dampingSlider);
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, processor.dampingParamID, dampingSlider);

    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.attachToComponent(&dampingSlider, true);
    addAndMakeVisible(dampingLabel);

    // Wet Level Slider
    wetLevelSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    wetLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(wetLevelSlider);
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, processor.wetLevelParamID, wetLevelSlider);

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.attachToComponent(&wetLevelSlider, true);
    addAndMakeVisible(wetLevelLabel);

    // Dry Level Slider
    dryLevelSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    dryLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(dryLevelSlider);
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, processor.dryLevelParamID, dryLevelSlider);

    dryLevelLabel.setText("Dry Level", juce::dontSendNotification);
    dryLevelLabel.attachToComponent(&dryLevelSlider, true);
    addAndMakeVisible(dryLevelLabel);
    setSize (400, 300);
}

SchroederReverbAudioProcessorEditor::~SchroederReverbAudioProcessorEditor()
{
}

//==============================================================================
void SchroederReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Schroeder Reverb", getLocalBounds(), juce::Justification::centredTop, true);
}

void SchroederReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds().reduced(10);
    auto sliderHeight = 40;
    auto labelWidth = 80;

    roomSizeSlider.setBounds(area.removeFromTop(sliderHeight).withTrimmedLeft(labelWidth));
    dampingSlider.setBounds(area.removeFromTop(sliderHeight).withTrimmedLeft(labelWidth));
    wetLevelSlider.setBounds(area.removeFromTop(sliderHeight).withTrimmedLeft(labelWidth));
    dryLevelSlider.setBounds(area.removeFromTop(sliderHeight).withTrimmedLeft(labelWidth));
}
