echo -e 'A;\n B; A\n A\n B; A\n {}A\n B({A})\n'|
	tee /dev/tty|
	sed -rf scc.sed
