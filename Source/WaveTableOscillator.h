#pragma once
#include <JuceHeader.h>
#include <cstdint>

class WaveTableOscillator
{
  public:
    WaveTableOscillator(const juce::AudioSampleBuffer&& tableToUse)
      : table_(tableToUse),
        tableSize_(table_.getNumSamples() - 1)
    {
      jassert(table_.getNumChannels() == 2);
    }

    void setFrequency(float freq, float sampleRate)
    {
      auto tableSizeOverSampleRate = (float) tableSize_ / sampleRate;
      tableDelta_ = freq * tableSizeOverSampleRate;
    }

    void setPulseWidth(float f)
    {
      pulseWidth_ = f;
    }

    inline float getNextSample(float mod) noexcept
    {
      float sample1 = lerpSampleFromBuffer_(0);
      float sample2 = lerpSampleFromBuffer_(1);
      float currentSample = sample2 * pulseWidth_ + (1.0f - pulseWidth_) * sample1;
      if ((currentIndex_ += (tableDelta_ + tableDelta_ * mod * 0.5f)) > (float) tableSize_)
        currentIndex_ -= (float) tableSize_;
      return currentSample;
    }

  private:
    inline float lerpSampleFromBuffer_(uint32_t buf)
    {
      auto* table = table_.getReadPointer(buf);
      uint32_t index0 = (uint32_t) currentIndex_;
      uint32_t index1 = index0 + 1; // this is safe because we subtract 1 in ctor
      float value0 = table[index0];
      float value1 = table[index1];
      float frac = currentIndex_ - (float) index0;
      return value0 + frac * (value1 - value0);
    }

    const juce::AudioSampleBuffer table_;
    const uint32_t tableSize_;
    float currentIndex_ = 0.0f, tableDelta_ = 0.0f, pulseWidth_ = 0.0f;
};
