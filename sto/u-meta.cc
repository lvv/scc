				#include <scc/simple.h>
				#include <sto/debug.h>
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
CHECK(   is_range<sto::basic_range<vector<int>>&&>::value )
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
CHECK   ( is_cstr<decltype( "abc")>   ::value)
CHECK   ( is_cstr<char[3]>            ::value)
CHECK   ( ! is_cstr<unsigned char[3]> ::value)
CHECK   ( ! is_cstr<signed char[3]>   ::value)
CHECK   ( ! is_cstr<int[3]>           ::value)
CHECK   ( is_cstr<char(&)[3]>         ::value)
CHECK   ( is_cstr<const char[3]>      ::value)
//CHECK ( ! is_cstr<char*>            ::value)
//CHECK ( is_cstr<const char*>        ::value)
CHECK   ( ! is_cstr<string>           ::value)
CHECK   ( ! is_cstr<const string&>    ::value)

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
CHECK(   (have_same_elem<vint, basic_range<vint>>::value)	)
CHECK(   (have_same_elem<vint, basic_range<vint&>&>::value)	)
CHECK(   (have_same_elem<vint, basic_range<vint&>&>::value)	)

// ITERATORS
CHECK(   is_input_iterator<vint::const_iterator>::value	)

CHECK( ! is_input_iterator         <void>  		::value)
CHECK( ! is_random_access_iterator <int>		::value)
CHECK(   is_input_iterator         <char*> 		::value)
CHECK(   is_input_iterator         <char[]>		::value)
CHECK( ! is_input_iterator         <std::true_type>	::value)
CHECK( ! is_input_iterator         <int(*)(int)>	::value)

CHECK( ! is_input_iterator         <int>         	::value)
CHECK(   is_input_iterator         <vint::iterator>	::value)
CHECK(   is_bidirectional_iterator <vint::iterator>	::value)
CHECK(   is_input_iterator         <lint::iterator>	::value)
CHECK(   is_forward_iterator       <lint::iterator>	::value)
CHECK(   is_bidirectional_iterator <lint::iterator>	::value)
CHECK( ! is_random_access_iterator <lint::iterator>	::value)
CHECK(   is_random_access_iterator <vint::iterator>	::value)
CHECK(   is_random_access_iterator <int*>  		::value)
CHECK(   is_random_access_iterator <int[3]>		::value)

// constess of iterator
CHECK(   is_const_iterator<vint::const_iterator>()	)
CHECK( ! is_const_iterator<vint::iterator>()		)
CHECK(   is_const_iterator<const int*>()		)
CHECK( ! is_const_iterator<int*>()			)
CHECK(   (is_const_iterator<std::array<int,3>::const_iterator>()))
CHECK( ! (is_const_iterator<std::array<int,3>::iterator>()))

// basic_range
CHECK(   (is_sto_range_iterator	<decltype(+range(vint{1}))>::value))
CHECK( ! (is_sto_range_iterator	<decltype( range(vint{1}))>::value))
CHECK(   (is_random_access_iterator	<decltype(+range(vint{1}))>::value))
CHECK( ! (is_random_access_iterator	<decltype(+range(lint{1}))>::value))
CHECK(   (is_bidirectional_iterator	<decltype(+range(vint{1}))>::value))
CHECK( ! (is_sto_range		<decltype(+range(vint{1}))>::value))
CHECK(   (is_sto_range		<decltype( range(vint{1}))>::value))
CHECK(   (is_range			<decltype( range(vint{1}))>::value))
CHECK( ! (is_range			<decltype(+range(vint{1}))>::value))

// numeric_range
CHECK(   (is_numeric_range_iterator	<decltype(+range(2))>::value))
CHECK( ! (is_numeric_range_iterator	<decltype( range(2))>::value))
CHECK( ! (is_numeric_range		<decltype(+range(2))>::value))
CHECK(   (is_numeric_range		<decltype( range(2))>::value))
CHECK(   (is_random_access_iterator	<decltype(+range(2))>::value))
CHECK(   (is_range			<decltype( range(2))>::value))
CHECK( ! (is_range			<decltype(+range(2))>::value))

// erasable_category
CHECK(   (is_same<non_erasable,decltype(erasable_category(1))>::value))
CHECK(   (is_same<non_erasable,decltype(erasable_category("abc"))>::value))
CHECK(   (is_same<cstr_erasable,decltype(erasable_category(c9))>::value))
CHECK(   (is_same<vector_erasable,decltype(erasable_category(v9))>::value))

					CHECK_EXIT;
					}
