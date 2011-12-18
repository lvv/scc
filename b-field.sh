#!/bin/bash
# vim:set ts=4 sw=4 syntax=sh:   


N=1000000

# generate input file (N records, 10 fields)

if [ ! -f b-field.in ]  ; then  
	scc 'for(; l<'$N'; l++) { for(i=1;i<=10; i++) _ l*10+i," "; _ l, "\t"; }' > b-field.in
else
	cat b-field.in > /dev/null
fi

# sup-up 10th field

# string-field
rm -f /tmp/sf
CXXFLAGS='-O3' scc -x /tmp/sf 'WRL n+=F10; n'
echo -n "scc: ";	command time -f %U   /tmp/sf                       < b-field.in
echo -n "scc: ";	command time -f %U   /tmp/sf                       < b-field.in
echo -n "scc: ";	command time -f %U   /tmp/sf                       < b-field.in
echo -n "scc: ";	command time -f %U   /tmp/sf                       < b-field.in
echo -n "scc: ";	command time -f %U   /tmp/sf                       < b-field.in
echo -n "gawk: ";	command time -f %U   gawk '{s+=$10} END{print s}'  < b-field.in
echo -n "mawk: ";	command time -f %U   mawk '{s+=$10} END{print s}'  < b-field.in







