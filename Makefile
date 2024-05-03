CC=gcc

%.o: %.c
	$(CC) $< -o $@

clean:
	-rm ./*/*/*.o
	-cd ./projects/project-2/Elevator && make clean 
	-cd ./steps/step-10/Garage && make clean
	-cd ./steps/step-14/Robot && make clean
