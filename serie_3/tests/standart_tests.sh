echo -e "\n\n.............Standart Tests\n\n"
echo -e "\n\n.............Test get_json\n\n"
make -f makefile_standart_tests test_get_json
valgrind ./test_get_json
make -f makefile_standart_tests clean

echo -e "\n\n.............Test products\n\n"
make -f makefile_standart_tests test_products
valgrind ./test_products
make -f makefile_standart_tests clean

echo -e "\n\n.............Test users\n\n"
make -f makefile_standart_tests test_users
valgrind ./test_users
make -f makefile_standart_tests clean

echo -e "\n\n.............Test carts\n\n"
make -f makefile_standart_tests test_carts
valgrind ./test_carts
make -f makefile_standart_tests clean
