make:
	cd ./dependencies/ && make
	mv ./dependencies/main ./exec

clean:
	cd ./dependencies/ && rm -f *~ *.o
	rm -f exec