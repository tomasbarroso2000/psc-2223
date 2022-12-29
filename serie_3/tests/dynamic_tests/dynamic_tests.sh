#sudo cp /home/aluno/Documents/PSC-2223SI/serie_3/tests/dynamic_tests/libdynamic.so /usr/lib

echo -e "\n\n.............\n\n"
export LD_LIBRARY_PATH=.
echo -e "\n\n.............Dynamic Tests\n\n"
make
echo -e "\n\n.............Test get_json\n\n"
valgrind ./get_json_test
echo -e "\n\n.............Press enter for products test\n\n"
read skip

echo -e "\n\n.............Test products\n\n"
valgrind ./products_test
echo -e "\n\n.............Press enter for users test\n\n"
read skip

echo -e "\n\n.............Test users\n\n"
valgrind ./users_test
echo -e "\n\n.............Press enter for carts test\n\n"
read skip

echo -e "\n\n.............Test carts\n\n"
valgrind ./carts_test
echo -e "\n\n.............Dynamic Tests End\n\n"
make clean
