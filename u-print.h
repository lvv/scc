
{ char				v = 97;				_ "char     :  ", v, ";    ";  cout << v << "\n"; };
{ const char*			v = "abc";			_ "c string :  ", v, ";    ";  cout << v << "\n"; };
{ string			v = "abc";			_ "str      :  ", v, ";    ";  cout << v << "\n"; };
{ strr				v ("abc");			_ "strr     :  ", v, ";    ";  cout << v << "\n"; };
{ fld				v ("abc");			_ "fld      :  ", v, ";    ";  cout << v << "\n"; };
{ std::array<int,3>		v {{1,2,3}};			_ "array    :  ", v, ";    ";  cout << v << "\n"; };
{ vector<int>			v {1,2,3};			_ "vint     :  ", v, ";    ";  cout << v << "\n"; };
{ deque<int>			v {1,2,3};			_ "dchar    :  ", v, ";    ";  cout << v << "\n"; };
{ deque<char>			v; v << "abc";			_ "vchar    :  ", v, ";    ";  cout << v << "\n"; };
{ set<char>			v; v << "abc";			_ "set<char>:  ", v, ";    ";  cout << v << "\n"; };
{ auto                          v = range("abc");   		_ "range(\"abc\"):  ", v, ";    ";  cout << v << "\n"; };
{ vector<int>			v {};				_ "vint{}   :  ", v, ";    ";  cout << v << "\n"; };
{ vector<vector<int>>		v {{1,1}, {2,2}};		_ "v..<vint>:  ", v, ";    ";  cout << v << "\n"; };
{ int				v[3]{1,2,3};			_ "int[]    :  ", v, ";    ";  cout << v << "\n"; };
{ tuple<const char*,int>	v {"aaa",2};			_ "tuple    :  ", v, ";    ";  cout << v << "\n"; };
{ tuple<>			v {};				_ "tuple{}  :  ", v, ";    ";  cout << v << "\n"; };
{ pair<int,int>			v {1,2};			_ "pair     :  ", v, ";    ";  cout << v << "\n"; };
{ map<string, int>		v {{"a",1},{"b",2},{"a",11}};	_ "map      :  ", v, ";    ";  cout << v << "\n"; };
{ map<int, int,std::greater<int>>v {{1,11},{2,22},{1,12}};	_ "map      :  ", v, ";    ";  cout << v << "\n"; };
{ map<string, int>		v {};				_ "map{}    :  ", v, ";    ";  cout << v << "\n"; };
{ unordered_map<int,int>	v {{1,1},{2,2}};		_ "uno..map :  ", v, ";    ";  cout << v << "\n"; };
{ vector<map<string,int>>	v {{{"aa",1}, {"bb",2}}};	_ "v<map>   :  ", v, ";    ";  cout << v << "\n"; };
{ set<int>			v {1,2,3,3};			_ "set      :  ", v, ";    ";  cout << v << "\n"; };
{ set<int,std::greater<int>>	v {1,2,3,3};			_ "set      :  ", v, ";    ";  cout << v << "\n"; };
{ set<int>			v {};				_ "set{}    :  ", v, ";    ";  cout << v << "\n"; };
{ multiset<int>			v {1,2,3,3};			_ "multiset :  ", v, ";    ";  cout << v << "\n"; };
{ unordered_set<int>		v {1,2,3,3};			_ "multiset :  ", v, ";    ";  cout << v << "\n"; };
//{ stack<int>			v; v << 1 << 2;			_ "set      :  ", v, ";    ";  cout << v << "\n"; };
//{ queue<int>			v; v << 1 << 2;			_ "queue    :  ", v, ";    ";  cout << v << "\n"; };

{ auto				v = make_tuple("aaa",2,make_tuple(3,4.5f));	_ "tuple<tu :  ", v, ";    ";  cout << v << "\n"; };
{ vector<int>			v {1,2,3};			_ "oi       :  "; std::copy(v.begin(), v.end(), oi);   _ endl; };
{ deque<int>			v {1,2,3};			_ "oi       :  "; std::copy(v.begin(), v.end(), oi);   _ endl; };

