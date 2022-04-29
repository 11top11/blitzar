#include "benchmark/reduce2/reduce_cpu.h"

#include "sxt/curve21/type/element_p3.h"
#include "sxt/curve21/constant/zero.h"
#include "sxt/curve21/operation/add.h"

namespace sxt {
//--------------------------------------------------------------------------------------------------
// reduce_cpu
//--------------------------------------------------------------------------------------------------
void reduce_cpu(c21t::element_p3* res, int m, int n) noexcept {
  // pretend like g is a random element rather than fixed
  c21t::element_p3 g{
      .X{3990542415680775, 3398198340507945, 4322667446711068, 2814063955482877,
         2839572215813860},
      .Y{1801439850948184, 1351079888211148, 450359962737049, 900719925474099,
         1801439850948198},
      .Z{1, 0, 0, 0, 0},
      .T{1841354044333475, 16398895984059, 755974180946558, 900171276175154,
         1821297809914039},
  };

  for (int mi=0; mi<m; ++mi) {
    auto& res_mi = res[mi];
    res_mi = c21cn::zero_p3_v;
    for (int i=0; i<n; ++i) {
      c21o::add(res_mi, res_mi, g);
    }
  }
}
} // namespace sxt