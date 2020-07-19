
#include "TypeWrapper.hpp"

namespace wasabi {
namespace audio {
namespace base {

using SampleRate = TypeWrapper<uint32_t, struct SampleRateTag>;
using BitDepth = TypeWrapper<uint8_t, struct BitDepthTag>;
using Channels = TypeWrapper<uint8_t, struct ChannelsTag>;
using Volume = TypeWrapper<float, struct VolumeTag>;

} // namespace base
} // namesapce audio
} // namespace wasabi
