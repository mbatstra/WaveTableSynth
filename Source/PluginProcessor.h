#pragma once

#include "TableBuilder.h"
#include "WaveTableOscillator.h"
#include <JuceHeader.h>

class MyPluginAudioProcessor  : public juce::AudioProcessor
{
public:
  MyPluginAudioProcessor();
  ~MyPluginAudioProcessor() override;


  // init and deinit
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  #ifndef JucePlugin_PreferredChannelConfigurations
   bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
  #endif

  // audio
  void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
  int getSampleRate() const { return sampleRate_; }

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  // midi related
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  // program related
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const juce::String getProgramName (int index) override;
  void changeProgramName (int index, const juce::String& newName) override;

  // state info
  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;

  // public for now
  int sampleRate_;
  WaveTableOscillator* oscillator_;
  WaveTableOscillator* modulator_;

private:
  juce::AudioSampleBuffer table_;
  TableBuilder tableBuilder_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginAudioProcessor)
};
