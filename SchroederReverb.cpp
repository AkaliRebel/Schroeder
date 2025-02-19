/*
  ==============================================================================

    SchroederReverb.cpp
    Created: 18 Feb 2025 7:41:44pm
    Author:  Akali

  ==============================================================================
*/

#include "SchroederReverb.h"

SchroederReverb::SchroederReverb()
{
    // Initialize comb filter delay times (in milliseconds)
    float combDelayTimes[numCombFilters] = { 50.0f, 56.0f, 61.0f, 68.0f };
    for (int i = 0; i < numCombFilters; ++i)
        combFilters[i].setDelayTime(combDelayTimes[i], sampleRate);

    // Initialize all-pass filter delay times (in milliseconds)
    float allPassDelayTimes[numAllPassFilters] = { 6.0f, 10.0f };
    for (int i = 0; i < numAllPassFilters; ++i)
        allPassFilters[i].setDelayTime(allPassDelayTimes[i], sampleRate);
}

void SchroederReverb::prepare(double sampleRate)
{
    this->sampleRate = sampleRate;

    for (auto& comb : combFilters)
        comb.setDelayTime(combDelayTimes[i], sampleRate);

    for (auto& allPass : allPassFilters)
        allPass.setDelayTime(allPassDelayTimes[i], sampleRate);
}

void SchroederReverb::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float input = channelData[sample];

            // Process through parallel comb filters
            float combOutput = 0.0f;
            for (auto& comb : combFilters)
                combOutput += comb.processSample(input);

            // Process through series all-pass filters
            float allPassOutput = combOutput;
            for (auto& allPass : allPassFilters)
                allPassOutput = allPass.processSample(allPassOutput);

            // Mix dry and wet signals
            channelData[sample] = (dryLevel * input) + (wetLevel * allPassOutput);
        }
    }
}

void SchroederReverb::setParameters(float roomSize, float damping, float wetLevel, float dryLevel)
{
    for (auto& comb : combFilters)
        comb.setFeedback(roomSize * damping);

    this->wetLevel = wetLevel;
    this->dryLevel = dryLevel;
}

// CombFilter implementation
void SchroederReverb::CombFilter::setDelayTime(float timeMs, double sampleRate)
{
    int delaySamples = static_cast<int>(timeMs * 0.001 * sampleRate);
    buffer.setSize(1, delaySamples);
    buffer.clear();
    writePointer = 0;
}

void SchroederReverb::CombFilter::setFeedback(float feedback)
{
    this->feedback = feedback;
}

float SchroederReverb::CombFilter::processSample(float input)
{
    float output = input + buffer.getSample(0, writePointer) * feedback;
    buffer.setSample(0, writePointer, output);
    writePointer = (writePointer + 1) % buffer.getNumSamples();
    return output;
}

// AllPassFilter implementation
void SchroederReverb::AllPassFilter::setDelayTime(float timeMs, double sampleRate)
{
    int delaySamples = static_cast<int>(timeMs * 0.001 * sampleRate);
    buffer.setSize(1, delaySamples);
    buffer.clear();
    writePointer = 0;
}

void SchroederReverb::AllPassFilter::setFeedback(float feedback)
{
    this->feedback = feedback;
}

float SchroederReverb::AllPassFilter::processSample(float input)
{
    float delayedSample = buffer.getSample(0, writePointer);
    float output = input * -feedback + delayedSample;
    buffer.setSample(0, writePointer, input + delayedSample * feedback);
    writePointer = (writePointer + 1) % buffer.getNumSamples();
    return output;
}
