echo -e "\n\n.............Teste get_json\n\n"
make -f makefile_standart_tests test_get_json
valgrind ./test_get_json
make -f makefile_standart_tests clean

echo -e "\n\n.............Teste products\n\n"
make -f makefile_standart_tests test_products
valgrind ./test_products
make -f makefile_standart_tests clean

echo -e "\n\n.............Teste users\n\n"
make -f makefile_standart_tests test_users
valgrind ./test_users
make -f makefile_standart_tests clean

echo -e "\n\n.............Teste carts\n\n"
make -f makefile_standart_tests test_carts
valgrind ./test_carts
make -f makefile_standart_tests clean
