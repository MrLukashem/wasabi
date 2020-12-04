
#pragma once

#include <stdexcept>
#include <iterator>
#include <memory>
#include <vector>


namespace wasabi {
namespace audio {
namespace base {

template <typename SampleType>
struct AudioBuffer;

template <typename SampleType = std::byte>
AudioBuffer<SampleType> wrap(void* data);

template <typename SampleType = std::byte>
class AudioBuffer {
public:
    template <bool isConst = false>
    class Iterator;

    using ConstIterator = Iterator<true>;
private:
    struct SampleProxy;
public:
    explicit AudioBuffer() = default;

    explicit AudioBuffer(const uint32_t length, const uint8_t numberOfChannels)
        : m_data(std::make_shared<SampleType[]>((length + 1) * numberOfChannels)), m_length(length),
        m_currentSample{} , m_numberOfChannels{numberOfChannels}, m_currentChannel{} { }

    AudioBuffer(AudioBuffer&& buffer) {
        m_data = std::move(buffer.m_data);
        setup(buffer);
    }

    AudioBuffer(const AudioBuffer& buffer) {
        m_data = buffer.m_data;
        setup(buffer);
    }

    virtual ~AudioBuffer() = default;

    AudioBuffer& operator= (AudioBuffer&& buffer) {
        m_data = std::move(buffer.m_data);
        setup(buffer);

        return *this;
    }

    AudioBuffer& operator= (const AudioBuffer& buffer) {
        m_data = buffer.m_data;
        setup(buffer);

        return *this;
    }

    bool operator== (const AudioBuffer& buffer) const noexcept {
        return this->data() == buffer.data();
    }

    void setup(const AudioBuffer& buffer) {
        m_length = buffer.m_length;
        m_currentSample = buffer.m_currentSample;
        m_currentChannel = buffer.m_currentChannel;
    }

    SampleProxy operator[] (const uint32_t n) {
        return SampleProxy(n, *this);
    }

    auto begin() noexcept {
        return Iterator(m_data.get() + (length() * m_currentChannel), length());
    }

    auto end() noexcept {
        return Iterator(m_data.get() + (length() * m_currentChannel) + 1, length());
    }

    auto cbegin() const noexcept {
        return ConstIterator(m_data.get() + (length() * m_currentChannel), length());
    }

    auto cend() const noexcept {
        return ConstIterator(m_data.get() + (length() * m_currentChannel) + 1, length());
    }

    uint32_t length() const {
        return m_length * m_numberOfChannels;
    }

    constexpr uint32_t numberOfChannels() const {
        return m_numberOfChannels;
    }

    // TODO: reimplement for shared_ptr
    void reallocate(const uint32_t newLength) {
        resetControlFields();

        m_length = newLength;
        //m_data.resize(newLength * m_numberOfChannels);
    }

    void reset() noexcept {
        resetControlFields();
        m_data.clear();
    }

    SampleType* data() noexcept {
        return m_data.get();
    }

    const SampleType* data() const noexcept {
        return m_data.get();
    }

    const void* getAddress() const noexcept {
        return static_cast<const void*>(data());
    }

    void putSample(const SampleType& sample, const uint32_t channel = 0) {
        m_data[channel * m_length + m_currentSample] = sample;
        ++m_currentSample;
    }

    void emplaceSample(const SampleType& sample, const uint32_t n, const uint32_t channel = 0) {
        m_data[channel * m_length + n] = sample;
    }

    SampleType& getNextSample(const uint32_t channel = 0) {
        return m_data[channel * m_length + m_currentSample++];
    }

    SampleType& getSample(const uint32_t n, const uint32_t channel = 0) {
        return m_data[channel * m_length + n];
    }

    const SampleType& getSample(const uint32_t n, const uint32_t channel = 0) const {
        return m_data[channel * m_length + n];
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
        m_currentChannel = channel < m_numberOfChannels ? channel : throw std::out_of_range{};
    }

    uint8_t getCurrentChannel() const noexcept {
        return m_currentChannel;
    }

    template <typename NewSampleType>
    AudioBuffer<NewSampleType> to() const noexcept {
        auto buffer = AudioBuffer<NewSampleType>();
        buffer.m_data = std::reinterpret_pointer_cast<NewSampleType[]>(this->m_data);

        return buffer;
    }

    AudioBuffer<std::byte> toByteBuffer() const noexcept {
        return this->to<std::byte>();
    }
private:
    void resetControlFields() noexcept {
        m_length = 0;
        m_currentSample = 0;
        m_currentSample = 0;
    }
public:
    template <bool isConst>
    class Iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = SampleType;
        using pointer = std::conditional_t<isConst, const value_type*, value_type*>;
        using reference = std::conditional_t<isConst,  const value_type&, value_type&>;
        using iterator_category = std::input_iterator_tag;

        Iterator(SampleType* beginDataPtr, const std::size_t channelSize)
            : m_currentDataPtr(beginDataPtr), m_channelSize(channelSize) { }

        Iterator(const Iterator& rhs) = default;
        Iterator(Iterator&& rhs) = default;
        Iterator& operator= (const Iterator& rhs) = default;
        Iterator& operator= (Iterator&& rhs) = default;

        bool operator== (const Iterator& rhs) const {
            return m_currentDataPtr == rhs.m_currentDataPtr;
        }

        bool operator!= (const Iterator& rhs) const {
            return !(*this == rhs);
        }

        template <bool isConstSupported = isConst>
        typename std::enable_if_t<isConstSupported, reference>
        operator*() const {
            return *m_currentDataPtr;
        }

        template <bool isConstSupported = isConst>
        typename std::enable_if_t<!isConstSupported, reference>
        operator*() {
            return *m_currentDataPtr;
        }

        Iterator& operator++() {
            ++m_currentDataPtr;
            return *this;
        }
    private:
        const std::size_t m_channelSize;
        SampleType* m_currentDataPtr;
    };

    std::shared_ptr<SampleType[]> m_data{};
    uint32_t m_length{};
    uint32_t m_currentSample{};
    uint8_t m_numberOfChannels{};
    uint8_t m_currentChannel{};
private:
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
        AudioBuffer<SampleType>& m_buffer;
    };
};

template <typename SampleType = std::byte>
AudioBuffer<SampleType> wrap(void* data) {
    return AudioBuffer<SampleType>();
}

} // namespace base
} // namespace audio
} // namespace audio
