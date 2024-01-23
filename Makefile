all: worst avg

worst: src/worst_case.cpp src/rtreap/rtreap.c src/rtreap/rtreap.h
	g++ -Wall -o worst src/worst_case.cpp src/rtreap/rtreap.c

avg: src/average_case.cpp src/rtreap/rtreap.c src/rtreap/rtreap.h
	g++ -Wall -o avg src/average_case.cpp src/rtreap/rtreap.c

clean: 
	rm -rf avg worst

run: all
	./worst 
	./avg
	cd plots; python3 main.py; cd ..
