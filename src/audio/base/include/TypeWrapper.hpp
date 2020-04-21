
#pragma once


namespace wasabi {
namespace audio {
namespace base {

// TODO: explicit ctr or not?
template <typename T, typename TypeTag>
struct TypeWrapper {
    TypeWrapper(T&& value) : m_value{std::forward<T>(value)} {}
    TypeWrapper() = default;
    TypeWrapper(const TypeWrapper&) = default;
    TypeWrapper(TypeWrapper&&) = default;

    TypeWrapper& operator= (const TypeWrapper&) = default;
    TypeWrapper& operator= (TypeWrapper&&) = default;

    virtual ~TypeWrapper() = default;

    TypeWrapper<T, TypeTag> operator+ (const TypeWrapper<T, TypeTag>& rhs) const noexcept {
        return m_value + rhs.m_value;
    }

    TypeWrapper<T, TypeTag> operator- (const TypeWrapper<T, TypeTag>& rhs) const noexcept {
        return m_value - rhs.m_value;
    }

    TypeWrapper<T, TypeTag>& operator+= (const TypeWrapper<T, TypeTag>& rhs) noexcept {
        m_value += rhs.m_value;
        return *this;
    }
    
    TypeWrapper<T, TypeTag>& operator-= (const TypeWrapper<T, TypeTag>& rhs) noexcept {
        m_value -= rhs.m_value;
        return *this;
    }

    bool operator== (const TypeWrapper<T, TypeTag>& rhs) const noexcept {
        return m_value == rhs.m_value;
    }

    bool operator!= (const TypeWrapper<T, TypeTag>& rhs) const noexcept {
        return m_value != rhs.m_value;
    }

    using tag = TypeTag;
    T m_value;
};

} // namespace wasabi
} // namespace audio
} // namespace base
