// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_INFRA_HASH_H_
#define INCLUDE_IMLAB_INFRA_HASH_H_
//---------------------------------------------------------------------------
#include <tuple>
#include "./template.h"
//---------------------------------------------------------------------------
// Hash a tuple with an index sequence
template<typename... Types, std::size_t... Indexes>
inline uint64_t HashTuple(const std::tuple<Types...>& tuple, std::index_sequence<Indexes... >) {
    std::array<uint64_t, std::index_sequence<Indexes... >::size()> results {
        std::get<Indexes>(tuple).hash()...
    };
    auto combine_hashes = [](uint64_t l, uint64_t r) { return r + 0x9e3779b9 + (l << 6) + (l >> 2); };
    return std::accumulate(results.begin(), results.end(), 0, combine_hashes);
}
//---------------------------------------------------------------------------
// Hash a tuple
template<typename... Types>
inline uint64_t HashTuple(const std::tuple<Types ...>& tuple) {
    return HashTuple(tuple, std::make_index_sequence<sizeof... (Types)>());
}
//---------------------------------------------------------------------------
template <typename... Types>
class Key {
    // Key components
    std::tuple<Types...> components;

 public:
    // Constructor
    explicit Key(Types... key): components(key...) {}

    // Compare two keys
    bool operator==(const Key &other) const {
        return PairwiseCompare(components, other.components);
    }

    // Compare two keys
    bool operator!=(const Key &other) const {
        return !(PairwiseCompare(components, other.components));
    }

    // Hash the key
    uint64_t Hash() const {
        return HashTuple(components);
    }
};
//---------------------------------------------------------------------------
namespace std {
//---------------------------------------------------------------------------
template <typename... Types>
struct hash<Key<Types...>> {
    std::size_t operator()(const Key<Types...>& k) const {
        return k.Hash();
    }
};

template <class T1, class T2>
struct hash<std::pair<T1, T2>> {
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
//---------------------------------------------------------------------------
}  // namespace std
//---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_INFRA_HASH_H_
//---------------------------------------------------------------------------
