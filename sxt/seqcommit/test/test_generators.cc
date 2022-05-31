#include "sxt/seqcommit/test/test_generators.h"

#include "sxt/base/test/unit_test.h"
#include "sxt/curve21/type/element_p3.h"
#include "sxt/seqcommit/base/commitment.h"
#include "sxt/seqcommit/generator/base_element.h"
#include "sxt/curve21/ristretto/byte_conversion.h"

namespace sxt::sqctst {
//--------------------------------------------------------------------------------------------------
// test_pedersen_get_generators
//--------------------------------------------------------------------------------------------------
void test_pedersen_get_generators(
    basf::function_ref<void(basct::span<sqcb::commitment> generators,
        uint64_t offset_generators)> f) {

    SECTION("we can verify that computed generators are correct when offset is zero") {
      c21t::element_p3 expected_g_0, expected_g_1;
      uint64_t num_generators = 2;
      uint64_t offset_generators = 0;
      sqcgn::compute_base_element(expected_g_0, 0 + offset_generators);
      sqcgn::compute_base_element(expected_g_1, 1 + offset_generators);

      sqcb::commitment generators[num_generators];
      basct::span<sqcb::commitment> span_generators(generators, num_generators);

      f(span_generators, offset_generators);

      sqcb::commitment expected_commit_0, expected_commit_1;
      c21rs::to_bytes(expected_commit_0.data(), expected_g_0);
      c21rs::to_bytes(expected_commit_1.data(), expected_g_1);

      REQUIRE(generators[0] == expected_commit_0);
      REQUIRE(generators[1] == expected_commit_1);
    }

    SECTION("we can verify that computed generators are correct when offset is non zero") {
      c21t::element_p3 expected_g_0, expected_g_1;
      uint64_t num_generators = 2;
      uint64_t offset_generators = 15;
      sqcgn::compute_base_element(expected_g_0, 0 + offset_generators);
      sqcgn::compute_base_element(expected_g_1, 1 + offset_generators);

      sqcb::commitment generators[num_generators];
      basct::span<sqcb::commitment> span_generators(generators, num_generators);

      f(span_generators, offset_generators);

      sqcb::commitment expected_commit_0, expected_commit_1;
      c21rs::to_bytes(expected_commit_0.data(), expected_g_0);
      c21rs::to_bytes(expected_commit_1.data(), expected_g_1);

      REQUIRE(generators[0] == expected_commit_0);
      REQUIRE(generators[1] == expected_commit_1);
    }
}
}  // namespace sxt::sqctst
