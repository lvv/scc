
ASCIIDOC_FILTERS ?= /usr/share/asciidoc/filters


ifeq ($(USER),lvv)
	HOMEDIR := /home/lvv/p/volnitsky.com/
	INCLUDE := $(HOMEDIR)/include.mk 
else
	INCLUDE := /dev/null
endif


include $(INCLUDE)

index.txt: 
	head -n-1 README.asciidoc > /tmp/t.ad


#CLEAN_LIST += $(wildcard *.png)
#COPY_LIST += $(wildcard *.png)

###########################################################
CXXFLAGS=   -std=gnu++11 -Wall -I/home/lvv/p/ 
t-buf-r: t-buf



BENCH_FILE=/tmp/bf

bench_lines: $(BENCH_FILE)
	#sh -c "[ -x /tmp/x ] && mv /tmp/x{,.old}"
	scc -O -x /tmp/x -n 'WRL n++; n'
	cat $(BENCH_FILE) > /dev/null
	/usr/bin/time -f'\t%Es (%Us+%Ss) \t%MKB\n'  /tmp/x < $(BENCH_FILE)

$(BENCH_FILE):
	scc 'char C[]="123456789\n"; REP(40*1000*1000) _ C;' > $(BENCH_FILE)
