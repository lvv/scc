
	// full C++ grammar:  http://www.nongnu.org/hcb/#escape-sequence

	sregex	ws, snippet, expr, last_expr, code, block, statement, compaund_expr, op, word, paran, str, ch, esc,
		comment_cpp, comment_c, comment,
		valid_snippet, with_last_snippet;

	ws		= *_s;
	comment_cpp	= "//" >> *~_ln >> (_ln | eos);
	comment_c	= "/*" >> *_ >> "*/";
	comment		= comment_c | comment_cpp;
	op		= (set =  '$', '+', '-', '*', '/', '%', '&', '^', '|', '?', ':', '=', ',', '.', '<', '>') |
		"::" | "++" | "--" | "->" | ".*" | "->*" | ">>" | "<<" | "&&" | "||" | "<=" | ">=" | "!=" |
		(( as_xpr(">>") | "<<" | (set = '<', '>', '=', '!', '+', '-', '*', '/', '%', '&', '^', '|')) >> '=');

	word		=  _b >> +_w >> _b;
	esc		= as_xpr('\\') >>
				(
					(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
					|         repeat<1,3>(_d)	// octal
					| (as_xpr('x') >> +_d  )	// hex
					| ('u' >> repeat<4,4>(_d))	// unicode
					| ('U' >> repeat<8,8>(_d))	// unicode
				);


	str		= as_xpr('\"') >> *(~(set='\"','\\') |  esc) >> '\"';
	ch		= as_xpr('\'') >> +(~as_xpr('\'') |  "\\\'") >> '\'';
	expr		= ws >> +((word|comment|op|str|ch|by_ref(paran)|by_ref(compaund_expr)) >> ws);

	paran		= ('(' >> !by_ref(expr) >> ')') |
			  ('[' >> !by_ref(expr) >> ']') |
			  ('{' >> !by_ref(expr) >> '}');
	last_expr	= expr >> eos;
	statement	= expr >> ';' >> ws;
	compaund_expr	= as_xpr("({") >>  by_ref(code) >> "})";
	code		= +( statement | by_ref(block) );
	block		= ws >> '{' >> by_ref(code) >> '}' >> ws;
	valid_snippet		= bos >> (!(s1 = code)|ws) >> !(s2 = last_expr) >> eos;
	with_last_snippet	= bos >> (!(s1 = code)|ws) >>  (s2 = last_expr) >> eos;
