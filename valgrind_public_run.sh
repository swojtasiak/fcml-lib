export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src/.libs
valgrind --track-origins=yes --leak-check=full check/public-tests/.libs/fcml_public_check > valgrind-result.txt 2>&1

