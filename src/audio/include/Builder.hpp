

namespace wasabi {
namespace audio {

template <typename Product>
struct Builder {
    Builder() = default;
    virtual ~Builder() = default;

    virtual operator std::unique_ptr<Product>() const = 0;
    virtual std::unique_ptr<Product> build() const = 0;
};

} // namespace audio
} // namespace wasabi
