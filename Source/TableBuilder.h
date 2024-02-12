#pragma once
#include "SampleFunctions.h"
#include <JuceHeader.h>
#include <cstdint>
#include <vector>

class TableBuilder
{
  public:
    TableBuilder(uint32_t numChannels, uint32_t size);
    TableBuilder(const TableBuilder& other);
    virtual ~TableBuilder() = default;

    void cacheTable(std::vector<SampleFunc> f);
    juce::AudioSampleBuffer&& getTable() { return std::move(table_); }

  private:
    juce::AudioSampleBuffer table_;
    uint32_t size_;
    uint32_t numChannels_;
};
