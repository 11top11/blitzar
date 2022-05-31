#include "sxt/seqcommit/generator/cpu_generator.h"

#include "sxt/base/container/span.h"
#include "sxt/curve21/type/element_p3.h"
#include "sxt/seqcommit/base/commitment.h"
#include "sxt/seqcommit/generator/base_element.h"
#include "sxt/curve21/ristretto/byte_conversion.h"

namespace sxt::sqcgn {
//--------------------------------------------------------------------------------------------------
// cpu_get_generators
//--------------------------------------------------------------------------------------------------
void cpu_get_generators(
    basct::span<sqcb::commitment> generators,
    uint64_t offset_generators) noexcept {

  uint64_t num_generators = generators.size();
  
  for (uint64_t row_i = 0; row_i < num_generators; row_i++) {
    c21t::element_p3 g_i;

    sqcgn::compute_base_element(g_i, row_i + offset_generators);

    c21rs::to_bytes(generators[row_i].data(), g_i);
  }
}

} // namespace sxt::sqcgn
