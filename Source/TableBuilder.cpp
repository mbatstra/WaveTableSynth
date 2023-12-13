#include "TableBuilder.h"
#include "juce_core/system/juce_PlatformDefs.h"

TableBuilder::TableBuilder(uint32_t numChannels, uint32_t size)
  : numChannels_(numChannels), size_(size)
{
  table_.setSize(numChannels_, size_);
}

TableBuilder::TableBuilder(const TableBuilder& other)
{
  table_ = other.table_;
  numChannels_ = other.numChannels_;
  size_ = other.size_;
}

void TableBuilder::cacheTable(std::vector<SampleFunc> f)
{
  jassert(f.size() == numChannels_);

  double angleDelta = juce::MathConstants<double>::twoPi / (double) size_;
  double currentAngle = 0.0;

  for (size_t i = 0; i < f.size(); i++) {
    auto* samples = table_.getWritePointer(i);
    for (size_t j = 0; j < size_; j++) {
      double sample = f[i](currentAngle);
      samples[j] = sample;
      currentAngle += angleDelta;
    }
    samples[size_ - 1] = samples[0]; // this way it wraps properly
  }
}
