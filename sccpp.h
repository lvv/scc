	sregex	ws, snippet, expr, last_expr, code, block, statement, op, word, paran, str, ch, esc,
		comment_cpp, comment_c, comment,
		valid_snippet, with_last_snippet;

	ws		= *_s;
	comment_cpp	= "//" >> *~_ln >> (_ln | eos);
	comment_c	= "/*" >> *_ >> "*/";
	comment		= comment_c | comment_cpp;
	op		= (set = '+', '-', '*', '-');
	word		= _b >> +_w >> _b;
	esc		= as_xpr('\\') >>
				(
					(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
					|         repeat<3,3>(_d)
				//	| (as_xpr('x') << _d << _d )		// xpressive: invalid regex
				//	| ('u' << repeat<4,4>(_d))
				//	| ('U' << repeat<8,8>(_d))
				);


	str		= as_xpr('\"') >> *(~(set='\"','\\') |  esc) >> '\"';
	ch		= as_xpr('\'') >> +(~as_xpr('\'') |  "\\\'") >> '\'';
	expr		= ws >> +((word|comment|op|str|ch|by_ref(paran)) >> ws);

	paran		= ('(' >> !by_ref(expr) >> ')') |
			  ('[' >> !by_ref(expr) >> ']');
	last_expr	= expr >> eos;
	statement	= expr >> ';' >> ws;
	code		= +( statement | by_ref(block) );
	block		= ws >> '{' >> by_ref(code) >> '}' >> ws;
	valid_snippet		= bos >> !(s1 = code) >> !(s2 = last_expr) >> eos;
	with_last_snippet	= bos >> !(s1 = code) >>  (s2 = last_expr) >> eos;
