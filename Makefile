
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


#COPY_LIST += $(wildcard *.png)

###########################################################

CLEAN_LIST += t-print  t-regex t-meta

CXXFLAGS=   -std=gnu++11 -Wall -I/home/lvv/p/ 
t-buf-r: t-buf



BENCH_FILE=/tmp/bf

bench_lines: $(BENCH_FILE)
	#sh -c "[ -x /tmp/x ] && mv /tmp/x{,.old}"
	scc -O -x /tmp/x -n 'WRl n++; n'
	cat $(BENCH_FILE) > /dev/null
	/usr/bin/time -f'\t%Es (%Us+%Ss) \t%MKB\n'  /tmp/x < $(BENCH_FILE)

bench: $(BENCH_FILE)
	cat $(BENCH_FILE) > /dev/null
	@echo 
	LC_ALL=C time wc -wl $(BENCH_FILE)
	@echo 
	LC_ALL=C time gawk '{n+=NF}; END{print n, NR}'  $(BENCH_FILE)
	@echo 
	LC_ALL=C time mawk '{n+=NF}; END{print n, NR}'  $(BENCH_FILE)
	@echo 
	scc -O -x /tmp/x -n 'WRl n+=NF; __ NR ^ n;'
	LC_ALL=C time  /tmp/x < $(BENCH_FILE)


$(BENCH_FILE):
	scc 'char C[]="123456789"; REP(5*1000*1000) { REP(10) _ C << " "; __ "";}' > $(BENCH_FILE)
