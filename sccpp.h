	sregex	id, atom, word, str, ch, esc,
		round_paran, square_paran, angle_paran,
		comment_cpp, comment_c, comment, s,
		infix_op, postfix_op, prefix_op,
		seq, expr1, expr, code1, code, block, initializer_block, compaund_expr,
		type, expr_type, decl_id, ctor,
		statement_semicolon, statement_scc, declaration, statement_with_block,
		valid_snippet, with_last;

	// BLANK
	comment_cpp	= keep("//") >> *~_ln >> (_ln | eos);
	comment_c	= as_xpr("/*") >>  -*_ >>  "*/";
	comment		= comment_c | comment_cpp;
	s		= *_s >> *(comment >> *_s);


	///  STRING
	esc		= as_xpr('\\') >>
				(
					(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
					|         repeat<1,3>(_d)	// octal
					| (as_xpr('x') >> +_d  )	// hex
					| ('u' >> repeat<4,4>(_d))	// unicode
					| ('U' >> repeat<8,8>(_d))	// unicode
				);


	str		= keep(as_xpr('\"') >> -*(~(set='\"','\\') | esc) >> '\"');
	ch		= keep(as_xpr('\'') >> -+~as_xpr('\'') >> '\'');

	////  OP
	infix_op		= (set= '+','-', '*', '/', '%',    '|', '&', '^',   '<', '>',   '=', ',', '.', '?', ':')
				| "::" |  "->" | ".*" | "->*" | ">>" | "<<" |  "||" | "&&"| "<=" | ">=" | "!=" | "==" | ">>" | "<<" |
				(((set = '<', '>', '=', '!', '+', '-', '*', '/', '%',  '^', '|') ) >> '=')
				;
	prefix_op	= (set =  '+', '-', '*', '^', '!', '~') | "++" | "--";

	postfix_op	= as_xpr("++") | "--" | by_ref(round_paran) | by_ref(square_paran);



	/////  EXPR
	word		= ~after(set[_w|_d|'$']) >> +(_w | _d | '$') >> ~before(set[_w|_d|'$']);
	id		= ~after(set[_w|_d|'$']) >> +(_w | '$') >> *(_w | _d | '$') >> ~before(set[_w|_d|'$']);
	atom		= word  | ch | str | by_ref(round_paran) | by_ref(compaund_expr) | by_ref(ctor);

	expr1		= *(prefix_op >> s) >>   by_ref(atom)  >> *(s >> postfix_op);
	expr		=  expr1 >> *(s >> infix_op >> s  >> expr1);
				;
	round_paran	= ('(' >> s >> !(by_ref(expr) >> s) >> ')');
	square_paran	= ('[' >> s >> !(by_ref(expr) >> s) >> ']');
	angle_paran	= ('<' >> s >> !(by_ref(expr) >> s) >> '>');


	//////  TYPE

	initializer_block = /*~after(')') >> s >>*/ '{' >> s >> !(( expr | by_ref(initializer_block)) >> s ) >>  '}' ;

	type		=           *(id >> s) >> id >> !(s >> angle_paran) >> !( s >> "::" >> s >> id);
	expr_type	=  ( '(' >> *(id >> s) >> id >> !(s >> angle_paran) >> !( s >> "::" >> s >> id) >>')' )
			 | (                      id >> !(s >> angle_paran) >> !( s >> "::" >> s >> id)       );

	decl_id		=  id >> *( s >> square_paran)
				>> !( s >>
					( (!as_xpr('=') >> s >> initializer_block)	// = {exp}
					|  round_paran					// (ctro-arg)
					| ( as_xpr('=') >> s >> expr)			// = expr
					)
				);

	declaration	= type >> !(s >> (set='*','&')) >> s
			>> decl_id >> *( s >> ',' >> s >> decl_id);

	ctor		=  expr_type >> s >> ( round_paran |  initializer_block );


	//////  CODE
	statement_with_block =
			id >> s >> '(' >> s >> expr >> s >> ')' >> !( s >> (by_ref(block)|expr));

	statement_semicolon	= (expr | declaration) >> s >> ';';
	statement_scc	= keep(as_xpr("_") | "__" | "WRL") >> s >> ((by_ref(block) | by_ref(expr))) >> s >> ';' ;

	code1		= statement_semicolon | statement_scc | by_ref(block) | statement_with_block;
	code		= code1 >> *(s >> code1);
	compaund_expr	= keep("({") >>  s >> by_ref(code) >> s >> keep("})");

	block		= keep('{') >> s >> !(by_ref(code) >> s ) >> keep('}');

	valid_snippet	= bos >> !(s1 = (s >> code >> s)) >> !(s2 = expr) >> (s3 = s) >> eos;
	with_last	= bos >> !(s1 = (s >> code >> s)) >>  (s2 = expr) >> (s3 = s) >> eos;

	//  	C++ grammar:
	//		BNF -- http://www.nongnu.org/hcb/#escape-sequence
	//		http://homepages.e3.net.nz/~djm/cppgrammar.html
	//	C++ lexer in spirit -- http://boost-spirit.com/repository/applications/cpp_lexer.zip
	//	http://www.nobugs.org/developer/parsingcpp/
	//	yacc-able C++ grammar -- http://www.parashift.com/c++-faq-lite/compiler-dependencies.html#faq-38.11
