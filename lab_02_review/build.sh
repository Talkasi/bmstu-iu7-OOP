mkdir -p out

g++ -std=c++20 -c -Wall -Werror -I ./inl/ -I ./inc/ -I ./test/ -O0 -g3 ./src/base_matrix.cpp -o ./out/base_matrix.o
g++ -std=c++20 -c -Wall -Werror -I ./inl/ -I ./inc/ -I ./test/ -O0 -g3 ./src/base_exception.cpp -o ./out/base_exception.o
g++ -std=c++20 -c -Wall -Werror -I ./inl/ -I ./inc/ -I ./test/ -O0 -g3 ./src/base_iterator.cpp -o ./out/base_iterator.o
g++ -std=c++20 -c -Wall -Werror -I ./inl/ -I ./inc/ -I ./test/ -O0 -g3 ./main.cpp -o ./out/main.o

g++ -std=c++20 -lgtest -lgtest_main -lpthread -Wall -Werror -O0 -g3 -I ./inl/ -I ./inc/ -I ./test/ ./out/main.o ./out/base_matrix.o ./out/base_exception.o ./out/base_iterator.o -o ./out/app.exe
