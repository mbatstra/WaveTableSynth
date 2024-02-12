#include "PluginEditor.h"
#include "PluginProcessor.h"


MyPluginAudioProcessorEditor::MyPluginAudioProcessorEditor(
    MyPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  // TODO: make initSlider()
  addAndMakeVisible(frequencySlider_);
  frequencySlider_.setRange(50.0, 5000.0);
  frequencySlider_.setSkewFactorFromMidPoint (500.0);
  frequencySlider_.onValueChange = [this]
  {
    if (audioProcessor.getSampleRate() > 0.0)
      audioProcessor.oscillator_->setFrequency(frequencySlider_.getValue(), audioProcessor.getSampleRate());
  };
  addAndMakeVisible(modSlider_);
  modSlider_.setRange(50.0, 5000.0);
  modSlider_.setSkewFactorFromMidPoint (500.0);
  modSlider_.onValueChange = [this]
  {
    if (audioProcessor.getSampleRate() > 0.0)
      audioProcessor.modulator_->setFrequency(modSlider_.getValue(), audioProcessor.getSampleRate());
  };
  addAndMakeVisible(pulseWidthSlider_);
  pulseWidthSlider_.setRange(0.0, 1.0);
  pulseWidthSlider_.onValueChange = [this]
  {
    if (audioProcessor.getSampleRate() > 0.0)
      audioProcessor.oscillator_->setPulseWidth(pulseWidthSlider_.getValue());
  };

  setSize(400, 300);
}

MyPluginAudioProcessorEditor::~MyPluginAudioProcessorEditor() {}

//==============================================================================
void MyPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("audio time", getLocalBounds(), juce::Justification::centred,
                   1);
}

void MyPluginAudioProcessorEditor::resized() {
  frequencySlider_.setBounds(10, 10, getWidth() - 20, 20);
  modSlider_.setBounds(10, 30, getWidth() - 20, 20);
  pulseWidthSlider_.setBounds(10, 50, getWidth() - 20, 20);
}
