/*
  ==============================================================================

    SchroederReverb.h
    Created: 18 Feb 2025 7:41:44pm
    Author:  Akali

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SchroederReverb
{
public:
    SchroederReverb();
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);
    void setParameters(float roomSize, float damping, float wetLevel, float dryLevel);

private:
    struct CombFilter
    {
        void setDelayTime(float timeMs, double sampleRate);
        void setFeedback(float feedback);
        float processSample(float input);

        juce::AudioBuffer<float> buffer;
        int writePointer = 0;
        float feedback = 0.0f;
    };

    struct AllPassFilter
    {
        void setDelayTime(float timeMs, double sampleRate);
        void setFeedback(float feedback);
        float processSample(float input);

        juce::AudioBuffer<float> buffer;
        int writePointer = 0;
        float feedback = 0.0f;
    };

    static constexpr int numCombFilters = 4;
    static constexpr int numAllPassFilters = 2;

    CombFilter combFilters[numCombFilters];
    AllPassFilter allPassFilters[numAllPassFilters];

    double sampleRate = 44100.0;
    float wetLevel = 0.5f, dryLevel = 0.5f;
};