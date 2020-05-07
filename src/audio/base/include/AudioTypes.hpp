
#include "TypeWrapper.hpp"

namespace wasabi {
namespace audio {
namespace base {

using SampleRate = TypeWrapper<uint32_t, struct SampleRateTag>;
using BitDepth = TypeWrapper<uint8_t, struct BitDepthTag>;
using Channels = TypeWrapper<uint32_t, struct ChannelsTag>;

} // namespace base
} // namesapce audio
} // namespace wasabi
