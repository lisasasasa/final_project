source = main
header = Parameter.h String.h Expression.h Keyword.h Mail.h Heap.h Order_Tree.h
run: $(source).cpp $(header)
	g++ -Wall -Wextra -Wshadow -static -O3 $< -o $@
clean:
	rm -rf run
