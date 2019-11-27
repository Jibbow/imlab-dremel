# ---------------------------------------------------------------------------
# IMLAB
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# TBB: Thread Building Blocks
# ---------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH "../FindTBB.cmake")

find_package(TBB)

# ---------------------------------------------------------------------------
# Benchmarks
# ---------------------------------------------------------------------------

add_executable(tpcc_5w_neworder bench/tpcc_5w_neworder.cc)
add_executable(tpcc_5w_mix_neworder_delivery bench/tpcc_5w_mix_neworder_delivery.cc)

target_link_libraries(tpcc_5w_neworder imlab tbb benchmark gtest gmock Threads::Threads)
target_link_libraries(tpcc_5w_mix_neworder_delivery imlab tbb benchmark gtest gmock Threads::Threads)
