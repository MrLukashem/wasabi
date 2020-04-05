
#pragma once

#include <stdexcept>
#include <vector>


namespace wasabi {
namespace audio {
namespace base {

// TODO: group up const functions and non-const functions
template <typename SampleType, std::size_t NumberOfChannels = 1>
class AudioBuffer {
public:
    explicit AudioBuffer() = default;

    explicit AudioBuffer(const std::size_t length)
        : m_data(length * NumberOfChannels), m_length(length), m_currentSample{}
        , m_currentChannel{} {
            m_data.resize(length * NumberOfChannels);
        }

    explicit AudioBuffer(AudioBuffer&& buffer) {
        m_data = std::move(buffer.m_data);
        m_length = buffer.m_length;
        m_currentSample = buffer.m_currentSample;
        m_currentChannel = buffer.m_currentChannel;
    }

    explicit AudioBuffer(const AudioBuffer& buffer) {
        m_data = buffer.m_data;
    }

    virtual ~AudioBuffer() = default;

    auto begin() {
        return std::begin(m_data) + (length() * m_currentChannel);
    }

    auto end() {
        return std::begin(m_data) + (length() * (m_currentChannel + 1));
    }

    std::size_t length() const {
        return m_data.size();
    }

    constexpr std::size_t numberOfChannels() const {
        return NumberOfChannels;
    }

    void reallocate(const std::size_t newLength) noexcept {
        resetControlFields();

        m_length = newLength;
        m_data.resize(newLength * NumberOfChannels);
    }

    void reset() noexcept {
        resetControlFields();
        m_data.clear();
    }

    SampleType* data() noexcept {
        return m_data.data();
    }

    const SampleType* data() const noexcept {
        return m_data.data();
    }

    void putSample(const SampleType& sample, const uint32_t channel = 0) {
        ++m_currentSample;
        m_data.at(channel * m_data.size() + m_currentSample) = sample;
    }

    SampleType& getSample(const uint32_t channel = 0) {
        return m_data.at(channel * m_data.size() + m_currentSample);
    }

    const SampleType& getSample(const uint32_t channel = 0) const {
        return m_data.at(channel * m_data.size() + m_currentSample);
    }

    SampleType& getSampleAndAdvance(const uint32_t channel = 0) {
        auto& sample = getSample(channel);
        ++m_currentSample;
        return sample;
    }

    std::size_t position() const noexcept {
        return m_currentSample;
    }

    void setPosition(const std::size_t position) {
        m_currentSample = position < m_length ? position : throw std::out_of_range{};
    }

    std::size_t advance(const std::size_t numOfSamples) noexcept {
        const auto maxSamplesToAdvance = length() - m_currentSample;
        const auto samplesToAdvance =
            maxSamplesToAdvance >= numOfSamples ? numOfSamples : maxSamplesToAdvance;
        m_currentChannel += samplesToAdvance;
    
        return samplesToAdvance;
    }

    void setCurrentChannel(const std::size_t channel) {
        m_currentChannel = channel < NumberOfChannels ? channel : throw std::out_of_range{};
    }
private:
    std::vector<SampleType> m_data{};
    std::size_t m_length{};
    std::size_t m_currentSample{};
    std::size_t m_currentChannel{};

    void resetControlFields() {
        m_length = 0;
        m_currentSample = 0;
        m_currentSample = 0;
    }
};

} // namespace wasabi
} // namespace audio
} // namespace base