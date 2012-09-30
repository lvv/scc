				#include <scc/simple.h>
				#include <scc/debug.h>
				#include <lvv/check.h>
				using namespace sto;

				int main () {


//  CL_ELEM_TYPE
CHECK_TYPES_ARE_SAME(   rn_elem_type<vint>        , int)
CHECK_TYPES_ARE_SAME(   rn_elem_type<vint&>       , int)
CHECK_TYPES_ARE_SAME(   rn_elem_type<vint&&>      , int)

CHECK_TYPES_ARE_SAME(   rn_elem_type<const vint>  , int)
CHECK_TYPES_ARE_SAME(   rn_elem_type<const vint&> , int)
CHECK_TYPES_ARE_SAME(   rn_elem_type<const vint&&>, int)

CHECK_TYPES_ARE_SAME(   rn_elem_type<int(&)[2]>   , int)
CHECK_TYPES_ARE_SAME(   rn_elem_type<int*(*)(int)>, no_type)
CHECK_TYPES_ARE_SAME(   rn_elem_type<int>         , no_type)


//  IS_RANGE
CHECK(   is_range<vint>()         ) 
CHECK(   is_range<vint&>()        ) 
CHECK(   is_range<vint&&>()       ) 

CHECK(   is_range<const vint>()   ) 
CHECK(   is_range<const vint&>()  ) 
CHECK(   is_range<const vint&&>() ) 

CHECK(   is_range<decltype(range(1,2))>()   ) 
CHECK(   is_range<decltype(range(v9))>()  ) 
CHECK(   is_range<decltype(range(range(v9)))>()  ) 
CHECK(   is_range<decltype(range(+v9,-v9))>() ) 
CHECK(   is_range<sto::chain_range<vector<int>>&&>() )
CHECK(   is_range<vector<int>&>())

CHECK( ! is_range<int*(*)(int)>() ) 
CHECK( ! is_range<int>()          ) 
CHECK(   is_range<int(&)[2]>()    ) 

//  IS_STRING
CHECK(   is_string<decltype("abc")>()) 
CHECK(   is_string<char[3]>()) 
CHECK( ! is_string<unsigned char[3]>()) 
CHECK( ! is_string<signed char[3]>()) 
CHECK( ! is_string<int[3]>()) 
CHECK(   is_string<char(&)[3]>()) 
//CHECK( ! is_string<const char[3]>()) 
//CHECK( ! is_string<char*>()) 
//CHECK(   is_string<const char*>()) 
CHECK(   is_string<string>()) 
CHECK(   is_string<const string&>()) 

//  IS_C_STRING
CHECK(   is_c_string<decltype("abc")>()) 
CHECK(   is_c_string<char[3]>()) 
CHECK( ! is_c_string<unsigned char[3]>()) 
CHECK( ! is_c_string<signed char[3]>()) 
CHECK( ! is_c_string<int[3]>()) 
CHECK(   is_c_string<char(&)[3]>()) 
CHECK(   is_c_string<const char[3]>()) 
//CHECK( ! is_c_string<char*>()) 
//CHECK(   is_c_string<const char*>()) 
CHECK( ! is_c_string<string>()) 
CHECK( ! is_c_string<const string&>()) 

//  HAS_PUSH_BACK
CHECK(   has_push_back<vint>()			)
CHECK(   has_push_back<vint&>()			)
CHECK(   has_push_back<vint&&>()		)
CHECK(   has_push_back<const vint&>()		)
CHECK(   has_push_back<const vint&&>()		)
CHECK(   has_push_back<volatile vint&>()	)
CHECK( ! has_push_back<int(&)[2]>()		)
CHECK( ! has_push_back<forward_list<int>>()	)
CHECK( ! has_push_back<stack<int>>()		)
CHECK(   has_push_back<string>()		)
CHECK( ! has_push_back<char(&)[2]>()		)
CHECK( !(has_push_back<map<int,int>>())		)


//  REFNESS
CHECK_TYPES_ARE_SAME(    rn_traits<vint>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    rn_traits<vint&>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    rn_traits<vint&&>::elem_type,		int	)

CHECK_TYPES_ARE_SAME(    rn_traits<const vint>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    rn_traits<const vint&>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    rn_traits<const vint&&>::elem_type,	int	)


//  HAS_VALUE_TYPE
CHECK(   has_value_type<vint>()			)
CHECK(   has_value_type<vint&>()		)
CHECK(   has_value_type<vint&&>()		)
CHECK(   has_value_type<const vint&>()		)
CHECK(   has_value_type<volatile vint&>()	)
CHECK(   has_value_type<vint&&>()		)
CHECK( ! has_value_type<int(&)[2]>()		)
CHECK( ! has_value_type<int>()			)

//  HAVE_SAME_ELEM
CHECK( ! (have_same_elem<vint, int>())			)

CHECK(   (have_same_elem<vint, int[3]>())		)
CHECK(   (have_same_elem<vint, int(&)[3]>())		)
CHECK(   (have_same_elem<vlong, int(&)[3]>())		)

CHECK(   (have_same_elem<vint, vlong>())		)
CHECK(   (have_same_elem<vint, llong>())		)
CHECK(   (have_same_elem<vint, vint&&>())		)
CHECK(   (have_same_elem<vint, vint&&>())		)
CHECK(   (have_same_elem<vint, vint&&>())		)
CHECK(   (have_same_elem<vint, chain_range<vint>>())	)
CHECK(   (have_same_elem<vint, chain_range<vint&>&>())	)
CHECK(   (have_same_elem<vint, chain_range<vint&>&>())	)

// ITERATORS
CHECK(   is_input_iterator<vint::const_iterator>()	)
CHECK( ! is_input_iterator<void>()			)
CHECK( ! is_input_iterator<char*>() 			)
CHECK( ! is_input_iterator<char[]>() 			)
CHECK( ! is_input_iterator<std::true_type>()		)

// constess of iterator
CHECK(   is_const_iterator<vint::const_iterator>()	)
CHECK( ! is_const_iterator<vint::iterator>()		)
CHECK(   is_const_iterator<const int*>()		)
CHECK( ! is_const_iterator<int*>()			)
CHECK(   (is_const_iterator<std::array<int,3>::const_iterator>()))
CHECK( ! (is_const_iterator<std::array<int,3>::iterator>()))

					CHECK_EXIT;
					}
