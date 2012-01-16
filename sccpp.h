
	// full C++ grammar:  http://www.nongnu.org/hcb/#escape-sequence

	sregex	atom, expr1, expr, code1, code, block, statement, compaund_expr,
		op, postfix_op, prefix_op,
		word, paran, str, ch, esc,
		comment_cpp, comment_c, comment, blnk,
		valid_snippet, with_last;

	// BLANK
	comment_cpp	= as_xpr('/') >> '/' >> *~_ln >> (_ln | eos);
	comment_c	= as_xpr('/') >> '*' >>  -*_ >>  '*' >> '/';
	comment		= comment_c | comment_cpp;
	blnk		= *_s;// >> *(comment >> *_s);


	///  STRING
	esc		= as_xpr('\\') >>
				(
					(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
					|         repeat<1,3>(_d)	// octal
					| (as_xpr('x') >> +_d  )	// hex
					| ('u' >> repeat<4,4>(_d))	// unicode
					| ('U' >> repeat<8,8>(_d))	// unicode
				);


	str		= as_xpr('\"') >> -*(~(set='\"','\\') /*|  esc*/) >> '\"';
	ch		= as_xpr('\'') >> -+~as_xpr('\'') >> '\'';

	////  OP
	// & $ ? && &
	op		= (set= '+','-', '*', '/', '%',  '|',  ':', '=', ',', '.', '<', '>')
				| (as_xpr('=')>> '=')
				//| as_xpr("::") |  "->" | ".*" | "->*" | ">>" | "<<" |  "||" | "<=" | ">=" | "!="
				//| (( as_xpr(">>") | "<<" | (set = '<', '>', '=', '!', '+', '-', '*', '/', '%',  '^', '|')) >> '=')
				;

	//prefix_op	= sregex::compile("[-+^!]|(\+\+)|(--)");
	prefix_op	= (set =  '+', '-', '*', '^', '!', '~');// | as_xpr("++") | as_xpr("--");

	//postfix_op	= sregex::compile("(++)|(--)");
	postfix_op	= (as_xpr('+') >> '+') | (as_xpr('-') >> '-');

	/////  EXPR
	word		=   +_w ;
	//word		= ~after(set[_w|_d|'$']) >> +(_w | _d | '$') >> ~before(set[_w|_d|'$']);
	atom		= word ; //| ch | str | by_ref(paran) | by_ref(compaund_expr);


	expr1		= (*(prefix_op >> blnk) >>   by_ref(atom)  >> *(blnk >> postfix_op));
	expr		=  expr1 >> *(blnk >> op >> blnk  >> expr1);
				;
	//////////////////////////////////////////////////////////////////////////////////////////////


	//expr1		=  word|op|str|ch|by_ref(paran)|by_ref(compaund_expr);
	//expr		=  expr1 >> *(blnk >> expr1);


	paran		= ('(' >> blnk >> !(by_ref(expr) >> blnk) >> ')') |
			  ('[' >> blnk >> !(by_ref(expr) >> blnk) >> ']') |
			  ('<' >> blnk >> !(by_ref(expr) >> blnk) >> '>');
			  //('{' >> blnk >> !(by_ref(expr) >> blnk) >> '}');

	statement	= by_ref(expr) >> blnk >> ';';

	code1		= statement | by_ref(block);
	code		= code1 >> *(blnk >> code1);
	compaund_expr	= as_xpr('(') >> '{' >>  blnk >> by_ref(code) >> blnk >> '}' >> ')';

	block		= '{' >> blnk >> by_ref(code) >> blnk >> '}';

	valid_snippet	= bos >> !(s1 = (blnk >> code >> blnk)) >> !(s2 = expr) >> (s3 = blnk) >> eos;
	with_last	= bos >> !(s1 = (blnk >> code >> blnk)) >>  (s2 = expr) >> (s3 = blnk) >> eos;
