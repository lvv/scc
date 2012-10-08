				#include <scc/simple.h>
				#include <scc/debug.h>
				#include <lvv/check.h>
				using namespace sto;

				int main () {


//  CL_ELEM_TYPE
CHECK_TYPES_ARE_SAME(   rg_elem_type<vint>        , int)
CHECK_TYPES_ARE_SAME(   rg_elem_type<vint&>       , int)
CHECK_TYPES_ARE_SAME(   rg_elem_type<vint&&>      , int)

CHECK_TYPES_ARE_SAME(   rg_elem_type<const vint>  , int)
CHECK_TYPES_ARE_SAME(   rg_elem_type<const vint&> , int)
CHECK_TYPES_ARE_SAME(   rg_elem_type<const vint&&>, int)

CHECK_TYPES_ARE_SAME(   rg_elem_type<int(&)[2]>   , int)
CHECK_TYPES_ARE_SAME(   rg_elem_type<int*(*)(int)>, no_type)
CHECK_TYPES_ARE_SAME(   rg_elem_type<int>         , no_type)


//  IS_RANGE
CHECK(   is_range<vint>::value         ) 
CHECK(   is_range<vint&>::value        ) 
CHECK(   is_range<vint&&>::value       ) 

CHECK(   is_range<const vint>::value   ) 
CHECK(   is_range<const vint&>::value  ) 
CHECK(   is_range<const vint&&>::value ) 

CHECK(   is_range<decltype(range(1,2))>::value   ) 
CHECK(   is_range<decltype(range(v9))>::value  ) 
CHECK(   is_range<decltype(range(range(v9)))>::value  ) 
CHECK(   is_range<decltype(range(+v9,-v9))>::value ) 
CHECK(   is_range<sto::chain_range<vector<int>>&&>::value )
CHECK(   is_range<vector<int>&>::value)

CHECK( ! is_range<int*(*)(int)>::value ) 
CHECK( ! is_range<int>::value          ) 
CHECK(   is_range<int(&)[2]>::value    ) 

CHECK(   is_range<decltype(range(v9))>::value    ) 
CHECK( ! is_range<decltype(+range(v9))>::value    ) 


//  IS_STRING
CHECK(   is_string<decltype("abc")>::value) 
CHECK(   is_string<char[3]>::value) 
CHECK( ! is_string<unsigned char[3]>::value) 
CHECK( ! is_string<signed char[3]>::value) 
CHECK( ! is_string<int[3]>::value) 
CHECK(   is_string<char(&)[3]>::value) 
//CHECK( ! is_string<const char[3]>::value) 
//CHECK( ! is_string<char*>::value) 
//CHECK(   is_string<const char*>()) 
CHECK(   is_string<string>::value) 
CHECK(   is_string<const string&>::value) 


//  IS_C_STRING
CHECK   ( is_c_string_t<decltype( "abc")>   ::value)
CHECK   ( is_c_string_t<char[3]>            ::value)
CHECK   ( ! is_c_string_t<unsigned char[3]> ::value)
CHECK   ( ! is_c_string_t<signed char[3]>   ::value)
CHECK   ( ! is_c_string_t<int[3]>           ::value)
CHECK   ( is_c_string_t<char(&)[3]>         ::value)
CHECK   ( is_c_string_t<const char[3]>      ::value)
//CHECK ( ! is_c_string_t<char*>            ::value)
//CHECK ( is_c_string_t<const char*>        ::value)
CHECK   ( ! is_c_string_t<string>           ::value)
CHECK   ( ! is_c_string_t<const string&>    ::value)

//  HAS_PUSH_BACK
CHECK(   has_push_back<vint>::value			)
CHECK(   has_push_back<vint&>::value			)
CHECK(   has_push_back<vint&&>::value		)
CHECK(   has_push_back<const vint&>::value		)
CHECK(   has_push_back<const vint&&>::value		)
CHECK(   has_push_back<volatile vint&>::value	)
CHECK( ! has_push_back<int(&)[2]>::value		)
CHECK( ! has_push_back<forward_list<int>>::value	)
CHECK( ! has_push_back<stack<int>>::value		)
CHECK(   has_push_back<string>::value		)
CHECK( ! has_push_back<char(&)[2]>::value		)
CHECK( !(has_push_back<map<int,int>>::value)		)


//  REFNESS
CHECK_TYPES_ARE_SAME(    rg_traits<vint>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    rg_traits<vint&>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    rg_traits<vint&&>::elem_type,		int	)

CHECK_TYPES_ARE_SAME(    rg_traits<const vint>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    rg_traits<const vint&>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    rg_traits<const vint&&>::elem_type,	int	)


//  HAVE_SAME_ELEM
CHECK( ! (have_same_elem<vint, int>::value)			)

CHECK(   (have_same_elem<vint, int[3]>::value)		)
CHECK(   (have_same_elem<vint, int(&)[3]>::value)		)
CHECK(   (have_same_elem<vlong, int(&)[3]>::value)		)

CHECK(   (have_same_elem<vint, vlong>::value)		)
CHECK(   (have_same_elem<vint, llong>::value)		)
CHECK(   (have_same_elem<vint, vint&&>::value)		)
CHECK(   (have_same_elem<vint, vint&&>::value)		)
CHECK(   (have_same_elem<vint, vint&&>::value)		)
CHECK(   (have_same_elem<vint, chain_range<vint>>::value)	)
CHECK(   (have_same_elem<vint, chain_range<vint&>&>::value)	)
CHECK(   (have_same_elem<vint, chain_range<vint&>&>::value)	)

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
