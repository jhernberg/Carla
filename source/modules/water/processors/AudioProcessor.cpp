/*
  ==============================================================================

   This file is part of the Water library.
   Copyright (c) 2015 ROLI Ltd.
   Copyright (C) 2017-2018 Filipe Coelho <falktx@falktx.com>

   Permission is granted to use this software under the terms of the GNU
   General Public License as published by the Free Software Foundation;
   either version 2 of the License, or any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

   For a full copy of the GNU General Public License see the doc/GPL.txt file.

  ==============================================================================
*/

#include "AudioProcessor.h"

namespace water {

AudioProcessor::AudioProcessor()
{
    cachedTotalIns  = 0;
    cachedTotalOuts = 0;

    currentSampleRate = 0;
    blockSize = 0;
    latencySamples = 0;

    suspended = false;
    nonRealtime = false;
}

AudioProcessor::~AudioProcessor()
{
}

//==============================================================================
void AudioProcessor::setPlayConfigDetails (const int newNumIns,
                                           const int newNumOuts,
                                           const double newSampleRate,
                                           const int newBlockSize)
{
    cachedTotalIns = newNumIns;
    cachedTotalOuts = newNumOuts;
    setRateAndBufferSizeDetails (newSampleRate, newBlockSize);
}

void AudioProcessor::setRateAndBufferSizeDetails (double newSampleRate, int newBlockSize) noexcept
{
    currentSampleRate = newSampleRate;
    blockSize = newBlockSize;
}

//==============================================================================
void AudioProcessor::setNonRealtime (const bool newNonRealtime) noexcept
{
    nonRealtime = newNonRealtime;
}

void AudioProcessor::setLatencySamples (const int newLatency)
{
    if (latencySamples != newLatency)
        latencySamples = newLatency;
}

void AudioProcessor::suspendProcessing (const bool shouldBeSuspended)
{
    const CarlaRecursiveMutexLocker cml (callbackLock);
    suspended = shouldBeSuspended;
}

void AudioProcessor::reset() {}

void AudioProcessor::processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer&)
{
    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear (ch, 0, buffer.getNumSamples());
}

}
