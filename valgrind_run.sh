export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src/.libs valgrind 
valgrind --track-origins=yes --leak-check=full check/fcml-check > valgrind-result.txt 2>&1
