format:
	clang-format -style=file -i $(shell find . -type f -name '*.cpp') $(shell find . -type f -name '*.hpp')
	
all:
	$(foreach dir, $(wildcard */), cd $(dir) && $(MAKE) all -j 8 && cd ..;)

copy:
	$(foreach dir, $(wildcard */), cd $(dir) && $(MAKE) copy COPY_DIR="$(COPY_DIR)" && cd ..;)

clean:
	$(foreach dir, $(wildcard */), cd $(dir) && $(MAKE) clean && cd ..;)