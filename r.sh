rm out_build

echo "Compiling with cmake..."

cmake . && make

echo "\n ****** OUTPUT ****** \n"

./out_build

echo "\n\n ****** END ***** \n"
