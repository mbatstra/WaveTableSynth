#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MyPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
  MyPluginAudioProcessorEditor (MyPluginAudioProcessor&);
  ~MyPluginAudioProcessorEditor() override;

  void paint (juce::Graphics&) override;
  void resized() override;

private:
  MyPluginAudioProcessor& audioProcessor;

  juce::Slider frequencySlider_;
  juce::Slider modSlider_;
  juce::Slider pulseWidthSlider_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginAudioProcessorEditor)
};
