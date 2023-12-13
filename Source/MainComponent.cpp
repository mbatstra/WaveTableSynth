#include "MainComponent.h"
#include "SampleFunctions.h"

//==============================================================================
MainComponent::MainComponent()
  : tableBuilder_(TableBuilder(2, 128))
{
  tableBuilder_.cacheTable(std::vector<SampleFunc>({ sf::sin, sf::square }));
  oscillator_ = new WaveTableOscillator(tableBuilder_.getTable());

  addAndMakeVisible(frequencySlider_);
  frequencySlider_.setRange(50.0, 5000.0);
  frequencySlider_.setSkewFactorFromMidPoint (500.0);
  frequencySlider_.onValueChange = [this]
  {
    if (sampleRate_ > 0.0)
      oscillator_->setFrequency(frequencySlider_.getValue(), sampleRate_);
  };
  addAndMakeVisible(pulseWidthSlider_);
  pulseWidthSlider_.setRange(0.0, 1.0);
  pulseWidthSlider_.onValueChange = [this]
  {
    if (sampleRate_ > 0.0)
      oscillator_->setPulseWidth(pulseWidthSlider_.getValue());
  };

  setSize (800, 600);
  setAudioChannels (0, 2);
}

MainComponent::~MainComponent()
{
  shutdownAudio();
  delete oscillator_;
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  sampleRate_ = sampleRate;
  oscillator_->setFrequency(frequencySlider_.getValue(), sampleRate_);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
  float level = 0.125f;
  auto leftBuf = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  auto rightBuf = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
  for (int i = 0; i < bufferToFill.numSamples; i++) {
    float currentSample = oscillator_->getNextSample();
    leftBuf[i] = currentSample * level;
    rightBuf[i] = currentSample * level;
  }
}

void MainComponent::releaseResources()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
  frequencySlider_.setBounds(10, 10, getWidth() - 20, 20);
  pulseWidthSlider_.setBounds(30, 30, getWidth() - 20, 20);
}

//==============================================================================
