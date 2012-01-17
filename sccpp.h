
	// full C++ grammar 
	// 	BNF -- http://www.nongnu.org/hcb/#escape-sequence
	// 	C++ lexer in spirit -- http://boost-spirit.com/repository/applications/cpp_lexer.zip

	sregex	id, atom, word, paran, str, ch, esc,
		comment_cpp, comment_c, comment, blnk,
		op, postfix_op, prefix_op,
		seq, expr1, expr, code1, code, block, initializer_block, compaund_expr,
		statement_semicolon, declaration_initialized, statement_with_block,
		valid_snippet, with_last;

	// BLANK
	comment_cpp	= as_xpr('/') >> '/' >> *~_ln >> (_ln | eos);
	comment_c	= as_xpr('/') >> '*' >>  -*_ >>  '*' >> '/';
	comment		= comment_c | comment_cpp;
	blnk		= *_s >> *(comment >> *_s);


	///  STRING
	esc		= as_xpr('\\') >>
				(
					(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
					|         repeat<1,3>(_d)	// octal
					| (as_xpr('x') >> +_d  )	// hex
					| ('u' >> repeat<4,4>(_d))	// unicode
					| ('U' >> repeat<8,8>(_d))	// unicode
				);


	str		= as_xpr('\"') >> -*(~(set='\"','\\') | esc) >> '\"';
	ch		= as_xpr('\'') >> -+~as_xpr('\'') >> '\'';

	////  OP
	op		= (set= '+','-', '*', '/', '%',    '|', '&', '^',   '<', '>',   '=', ',', '.', '?', ':')
				| "::" |  "->" | ".*" | "->*" | ">>" | "<<" |  "||" | "&&"| "<=" | ">=" | "!=" | "==" | ">>" | "<<" |
				(((set = '<', '>', '=', '!', '+', '-', '*', '/', '%',  '^', '|') ) >> '=')
				;
	prefix_op	= (set =  '+', '-', '*', '^', '!', '~') | "++" | "--";

	postfix_op	= as_xpr("++") | "--";

	/////  EXPR
	word		= ~after(set[_w|_d|'$']) >> +(_w | _d | '$') >> ~before(set[_w|_d|'$']);
	id		= ~after(set[_w|_d|'$']) >> +(_w | '$') >> *(_w | _d | '$') >> ~before(set[_w|_d|'$']);
	atom		= word  | ch | str | by_ref(paran) | by_ref(compaund_expr);
	seq		= (atom | by_ref(paran)) >> *( blnk >> (atom | by_ref(paran) | by_ref(initializer_block)));

	expr1		= *(prefix_op >> blnk) >>   by_ref(seq)  >> *(blnk >> postfix_op);
	expr		=  expr1 >> *(blnk >> op >> blnk  >> expr1);
				;
	paran		= ('(' >> blnk >> !(by_ref(expr) >> blnk) >> ')') |
			  ('[' >> blnk >> !(by_ref(expr) >> blnk) >> ']') |
			  ('<' >> blnk >> !(by_ref(expr) >> blnk) >> '>');
			  //('{' >> blnk >> !(by_ref(expr) >> blnk) >> '}');

	//////  CODE


	initializer_block = /*~after(')') >> blnk >>*/ '{' >> blnk >> !(( expr | by_ref(initializer_block)) >> blnk ) >>  '}';

	declaration_initialized = id >> blnk
			>> !(~before('(') >> expr >> ~after(')') >> blnk)
			>> !('=' >> blnk ) >>  initializer_block;

	statement_with_block =
			id >> blnk >> '(' >> blnk >> expr >> blnk >> ')' >> blnk >> by_ref(block);

	statement_semicolon	= (expr | declaration_initialized) >> blnk >> ';';

	code1		= statement_semicolon | by_ref(block) | statement_with_block;
	code		= code1 >> *(blnk >> code1);
	compaund_expr	= as_xpr("({") >>  blnk >> by_ref(code) >> blnk >> "})";

	block		= '{' >> blnk >> !(by_ref(code) >> blnk ) >> '}';

	valid_snippet	= bos >> !(s1 = (blnk >> code >> blnk)) >> !(s2 = expr) >> (s3 = blnk) >> eos;
	with_last	= bos >> !(s1 = (blnk >> code >> blnk)) >>  (s2 = expr) >> (s3 = blnk) >> eos;
