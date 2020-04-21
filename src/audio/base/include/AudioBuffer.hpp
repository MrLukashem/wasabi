
#pragma once

#include <stdexcept>
#include <vector>


namespace wasabi {
namespace audio {
namespace base {

// TODO: group up const functions and non-const functions
// TODO: clone buffer
template <typename SampleType, uint8_t NumberOfChannels = 1>
class AudioBuffer {
private:
    struct SampleProxy;
public:
    explicit AudioBuffer() = default;

    explicit AudioBuffer(const uint32_t length)
        : m_data(length * NumberOfChannels), m_length(length), m_currentSample{}
        , m_currentChannel{} {
            m_data.resize(length * NumberOfChannels);
        }

    AudioBuffer(AudioBuffer&& buffer) {
        m_data = std::move(buffer.m_data);
        m_length = buffer.m_length;
        m_currentSample = buffer.m_currentSample;
        m_currentChannel = buffer.m_currentChannel;
    }

    AudioBuffer(const AudioBuffer& buffer) {
        m_data = buffer.m_data;
    }

    virtual ~AudioBuffer() = default;

    SampleProxy operator[] (const uint32_t n) {
        return SampleProxy(n, *this);
    }

    auto begin() noexcept {
        return std::begin(m_data) + (length() * m_currentChannel);
    }

    auto end() noexcept {
        return std::begin(m_data) + (length() * (m_currentChannel + 1));
    }

    auto cbegin() const noexcept {
        return std::cbegin(m_data) + (length() * m_currentChannel);
    }

    auto cend() const noexcept {
        return std::cbegin(m_data) + (length() * (m_currentChannel + 1));
    }

    uint32_t length() const {
        return m_data.size();
    }

    constexpr uint32_t numberOfChannels() const {
        return NumberOfChannels;
    }

    void reallocate(const uint32_t newLength) {
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
        m_data.at(channel * m_data.size() + m_currentSample) = sample;
        ++m_currentSample;
    }

    void emplaceSample(const SampleType& sample, const uint32_t n, const uint32_t channel = 0) {
        m_data.at(channel * m_data.size() + n) = sample;
    }

    SampleType& getNextSample(const uint32_t channel = 0) {
        return m_data.at(channel * m_data.size() + m_currentSample++);
    }

    SampleType& getSample(const uint32_t n, const uint32_t channel = 0) {
        return m_data.at(channel * m_data.size() + n);
    }

    const SampleType& getSample(const uint32_t n, const uint32_t channel = 0) const {
        return m_data.at(channel * m_data.size() + n);
    }

    SampleType& getNextSampleAndAdvance(const uint32_t channel = 0) {
        auto& sample = getSample(channel);
        ++m_currentSample;
        return sample;
    }

    uint32_t getPosition() const noexcept {
        return m_currentSample;
    }

    void setPosition(const uint32_t position) {
        m_currentSample = position < m_length
            ? position : throw std::out_of_range("The position is out of the buffer length");
    }

    uint32_t advance(const uint32_t numOfSamples) noexcept {
        const auto maxSamplesToAdvance = length() - m_currentSample - 1;
        const auto samplesToAdvance =
            maxSamplesToAdvance >= numOfSamples ? numOfSamples : maxSamplesToAdvance;
        m_currentSample += samplesToAdvance;
    
        return samplesToAdvance;
    }

    void setCurrentChannel(const uint8_t channel) {
        m_currentChannel = channel < NumberOfChannels ? channel : throw std::out_of_range{};
    }

    uint8_t getCurrentChannel() const noexcept {
        return m_currentChannel;
    }
private:
    std::vector<SampleType> m_data{};
    uint32_t m_length{};
    uint32_t m_currentSample{};
    uint8_t m_currentChannel{};

    struct SampleProxy {
        SampleProxy(const uint32_t n, AudioBuffer& buffer) : m_mySampleIndex{n}, m_buffer{buffer} {}

        SampleProxy(SampleProxy&&) = default;
        SampleProxy(const SampleProxy&) = default;

        SampleType& operator[] (const uint8_t channel) {
            return m_buffer.getSample(m_mySampleIndex, channel);
        }

        SampleType& operator= (const SampleType& sample) {
            m_buffer.emplaceSample(sample, m_mySampleIndex, m_buffer.getCurrentChannel());
            return m_buffer.getSample(m_mySampleIndex, m_buffer.getCurrentChannel());
        }

        SampleType& operator+= (const SampleType& value) {
            auto& currentSample = m_buffer.getSample(m_mySampleIndex, m_buffer.getCurrentChannel());
            m_buffer.emplaceSample(currentSample + value, m_mySampleIndex, m_buffer.getCurrentChannel());

            return currentSample;
        }

        SampleType& operator-= (const SampleType& value) {
            auto& currentSample = m_buffer.getSample(m_mySampleIndex, m_buffer.getCurrentChannel());
            m_buffer.emplaceSample(currentSample - value, m_mySampleIndex, m_buffer.getCurrentChannel());

            return currentSample;
        }

        const uint32_t m_mySampleIndex;
        AudioBuffer<SampleType, NumberOfChannels>& m_buffer;
    };

    void resetControlFields() noexcept {
        m_length = 0;
        m_currentSample = 0;
        m_currentSample = 0;
    }
};

} // namespace wasabi
} // namespace audio
} // namespace base
