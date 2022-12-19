echo -e "\n\n.............\n\n"
echo -e "\n\n.............Dynamic Tests\n\n"
make -f makefile_dynamic_tests libdynamic.so
echo -e "\n\n.............Test get_json\n\n"
make -f makefile_dynamic_tests test_get_json
valgrind ./test_get_json
make -f makefile_dynamic_tests clean

echo -e "\n\n.............Test products\n\n"
make -f makefile_dynamic_tests test_products
valgrind ./test_products
make -f makefile_dynamic_tests clean

echo -e "\n\n.............Test users\n\n"
make -f makefile_dynamic_tests test_users
valgrind ./test_users
make -f makefile_dynamic_tests clean

echo -e "\n\n.............Test carts\n\n"
make -f makefile_dynamic_tests test_carts
valgrind ./test_carts
make -f makefile_dynamic_tests clean
