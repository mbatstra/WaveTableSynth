#pragma once

#include "TableBuilder.h"
#include "WaveTableOscillator.h"
#include <JuceHeader.h>

class MainComponent : public juce::AudioAppComponent
{
public:
  MainComponent();
  ~MainComponent() override;

  void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
  void releaseResources() override;

  void paint (juce::Graphics& g) override;
  void resized() override;

private:
  juce::AudioSampleBuffer table_;
  juce::Slider frequencySlider_;
  juce::Slider pulseWidthSlider_;
  int sampleRate_;
  WaveTableOscillator* oscillator_;
  TableBuilder tableBuilder_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
