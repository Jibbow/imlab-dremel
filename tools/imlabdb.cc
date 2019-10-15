// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <cstdint>
#include <chrono>  // NOLINT
#include <iostream>
#include <fstream>
#include "imlab/database.h"
#include "imlab/schema.h"
#include "imlab/infra/types.h"

namespace {

const int32_t kWarehouses = 5;

// Uniform random number
int32_t URand(int32_t min, int32_t max) {
    return (random() % (max - min + 1)) + min;
}

// Uniform random number
int32_t URandExcept(int32_t min, int32_t max, int32_t v) {
    if (max <= min)
        return min;
    int32_t r = (random() % (max - min)) + min;
    return (r >= v) ? (r + 1) : r;
}

// Non-uniform random number
int32_t NURand(int32_t A, int32_t x, int32_t y) {
    return ((((random() % A) | (random() % (y - x + 1) + x)) + 42) % (y - x + 1)) + x;
}

// Place a random order
void RandomNewOrder(imlab::Database &db) {
    Timestamp now(0);
    auto w_id = Integer(URand(1, kWarehouses));
    auto d_id = Integer(URand(1, 10));
    auto c_id = Integer(NURand(1023, 1, 3000));
    auto ol_cnt = Integer(URand(5, 15));

    std::array<Integer, 15> supware;
    std::array<Integer, 15> itemid;
    std::array<Integer, 15> qty;
    for (auto i = Integer(0); i < ol_cnt; i += Integer(1)) {
        supware[i.value] = (URand(1, 100) > 1) ? w_id : Integer(URandExcept(1, kWarehouses, w_id.value));
        itemid[i.value] = Integer(NURand(8191, 1, 100000));
        qty[i.value] = Integer(URand(1, 10));
    }

    db.NewOrder(w_id, d_id, c_id, ol_cnt, supware, itemid, qty, now);
}

}  // namespace

int main(int argc, char *argv[]) {
    // TODO
    return 0;
}
