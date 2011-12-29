// test if u-print.h can be used independantly

#include"print.h"

#include <array>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using std::array;
using std::vector;
using std::pair;
using std::tuple;
using std::make_tuple;
using std::string;
using std::map;
using std::set;
using std::multiset;
using std::multimap;
using std::unordered_map;
using std::unordered_set;

int main() {
	#include "u-print.h"
}
