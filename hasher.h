#ifndef  SCC_HASHER_H
#define  SCC_HASHER_H

#include <tuple>
///////////////////  TUPLE
// from http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
namespace std{
    namespace {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     http://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v) {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl {
          static void apply(size_t& seed, Tuple const& tuple) {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, get<Index>(tuple));
          }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0> {
          static void apply(size_t& seed, Tuple const& tuple) {
            std::hash_combine(seed, get<0>(tuple));
          }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>> {
        size_t
        operator()(std::tuple<TT...> const& tt) const {                                              
            size_t seed = 0;                             
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);    
            return seed;                                 
        }                                              

    };
}

///////////////////  PAIR

namespace std {
    template <class T, class U>
        struct hash<pair<T,U>> {
            size_t operator()(const pair<T,U>& val ) const {
                return hash<T>()(val.first) ^ hash<U>()(val.second);
            }
    };
};

///////////////////  ARRAY

#include <array>

namespace std {
	    template<typename T, size_t N>
    struct hash<array<T, N> > {
        typedef array<T, N> argument_type;
        typedef size_t result_type;

        result_type operator()(const argument_type& a) const {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i) {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };
}
#endif	// SCC_HASHER_H
