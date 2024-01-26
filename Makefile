all: worst avg treap_vs_bstree

worst: src/worst_case.c src/treap/treap.c src/treap/treap.h
	gcc -Wall -o worst src/worst_case.c src/treap/treap.c

avg: src/average_case.c src/treap/treap.c src/treap/treap.h
	gcc -Wall -o avg src/average_case.c src/treap/treap.c

treap_vs_bstree: src/treap/treap.c src/treap/treap.h src/bstree/bstree.c src/bstree/bstree.h src/treap_vs_bstree.c
	gcc -Wall -o treap_vs_bstree src/treap_vs_bstree.c src/treap/treap.c src/bstree/bstree.c

clean: 
	rm -rf avg worst treap_vs_bstree

run: all
	./worst 
	./avg
	./treap_vs_bstree
	cd plots; python3 main.py; python3 plot2.py; cd ..
