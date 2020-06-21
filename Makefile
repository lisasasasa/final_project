source = main
header = Parameter.h String.h Expression.h Keyword.h Mail.h Heap.h Order_Tree.h
run: $(source).cpp $(header)
	g++ -Drun -Wall -Wextra -Wshadow -static -O3 $< -o $@
WD := final\_project
DISTFILES := $(source).cpp $(header) Makefile
zip: $(DISTFILES)
	(cd .. && zip $(WD)/gogo.zip $(addprefix $(WD)/,$^))
clean:
	rm -rf run gogo.zip
