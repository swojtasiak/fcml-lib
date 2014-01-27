export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src/.libs valgrind 
valgrind --track-origins=yes --leak-check=full check/.libs/fcml_check > valgrind-result.txt 2>&1
