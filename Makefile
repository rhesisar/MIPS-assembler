MAIN := emul-mips
SRC_C := $(wildcard src/*.c)

$(MAIN): $(SRC_C)
	gcc $^ -o $@ -Wall -Wextra -O2 -lm

CLITMP := /tmp/emul-mips-test

test-cli: $(MAIN)
	@ [ -e ./$(MAIN) ] \
	  || echo "error: emul-mips does not exist!"; \
	touch $(CLITMP).in; \
	rm -f $(CLITMP).out1 $(CLITMP).out2; \
	./$(MAIN) $(CLITMP).in $(CLITMP).out1 $(CLITMP).out2 \
	  || echo "error: emul-mips in automatic mode returned $$?!"; \
	[ -e $(CLITMP).out1 ] \
	  || echo "error: assembled output file does not exist!"; \
	[ -e $(CLITMP).out2 ] \
	  || echo "error: final state output file does not exist!"; \
	rm -f $(CLITMP).out1 $(CLITMP).out2

clean:
	rm -f $(MAIN) src/*~ src/*.swap tests/*~ tests/*.swap
	rm -rf __pycache__ .pytest_cache tests/*.hex tests/*.state

tests: $(MAIN)
	@ python3 test.py -v

.PHONY: test-cli clean tests tar
