				#include <scc/simple.h>
				#include <scc/debug.h>
				#include <lvv/check.h>
				using namespace sto;

				int main () {


//  CL_ELEM_TYPE
CHECK_TYPES_ARE_SAME(   cl_elem_type<vint>        , int)
CHECK_TYPES_ARE_SAME(   cl_elem_type<vint&>       , int)
CHECK_TYPES_ARE_SAME(   cl_elem_type<vint&&>      , int)

CHECK_TYPES_ARE_SAME(   cl_elem_type<const vint>  , int)
CHECK_TYPES_ARE_SAME(   cl_elem_type<const vint&> , int)
CHECK_TYPES_ARE_SAME(   cl_elem_type<const vint&&>, int)

CHECK_TYPES_ARE_SAME(   cl_elem_type<int(&)[2]>   , int)
CHECK_TYPES_ARE_SAME(   cl_elem_type<int*(*)(int)>, no_type)
CHECK_TYPES_ARE_SAME(   cl_elem_type<int>         , no_type)


//  IS_CONTAINER
CHECK(   is_range<vint>()         ) 
CHECK(   is_range<vint&>()        ) 
CHECK(   is_range<vint&&>()       ) 

CHECK(   is_range<const vint>()   ) 
CHECK(   is_range<const vint&>()  ) 
CHECK(   is_range<const vint&&>() ) 

CHECK( ! is_range<int*(*)(int)>() ) 
CHECK( ! is_range<int>()          ) 
CHECK(   is_range<int(&)[2]>()    ) 

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
CHECK_TYPES_ARE_SAME(    cl_traits<vint>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    cl_traits<vint&>::elem_type,		int	)
CHECK_TYPES_ARE_SAME(    cl_traits<vint&&>::elem_type,		int	)

CHECK_TYPES_ARE_SAME(    cl_traits<const vint>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    cl_traits<const vint&>::elem_type,	int	)
CHECK_TYPES_ARE_SAME(    cl_traits<const vint&&>::elem_type,	int	)


//  HAS_VALUE_TYPE
CHECK(   has_value_type<vint>()			)
CHECK(   has_value_type<vint&>()		)
CHECK(   has_value_type<vint&&>()		)
CHECK(   has_value_type<const vint&>()		)
CHECK(   has_value_type<volatile vint&>()	)
CHECK(   has_value_type<vint&&>()		)
CHECK( ! has_value_type<int(&)[2]>()		)
CHECK( ! has_value_type<int>()			)


// ITERATORS
CHECK(   is_input_iterator<vint::const_iterator>()	)
CHECK( ! is_input_iterator<void>()			)
CHECK( ! is_input_iterator<char*>() 			)
CHECK( ! is_input_iterator<char[]>() 			)
CHECK( ! is_input_iterator<std::true_type>()		)


					CHECK_EXIT;
					}
