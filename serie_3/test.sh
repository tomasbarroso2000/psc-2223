echo -e "\n\n.............Teste get_json\n\n"
cd get_json
make test
valgrind ./test_get_json
make clean

echo -e "\n\n.............Teste products\n\n"
cd ../products
make test
valgrind ./test_products
make clean

echo -e "\n\n.............Teste users\n\n"
cd ../users
make test
valgrind ./test_users
make clean

echo -e "\n\n.............Teste carts\n\n"
cd ../carts
make test
valgrind ./test_carts
make clean
