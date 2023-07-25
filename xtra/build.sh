fnames=$(ls src| sort -r)
echo "">xtra.h
if [ "$1" = "true" ]; then
printf "#define __thenfi__ 1\n\n" >> xtra.h
fi
for file in $fnames; do
cat src/$file >> xtra.h
done
gcc -Wall -Werror -pedantic -Wextra xtra.h && echo "\033[0;32mNo errors\033[0m found in source"
if [ $? = 1 ]; then
echo "\033[0;31mErrors\033[0m in source"
rm -rf xtra.h
exit 1
fi
gcc -w test/main.c -o test/main.out # Doesn't need error, is already checked
test/main.out

if [ $? = 1 ]; then
printf "\n\033[0;31mFailed\033[0m test suite - not running."
rm -rf xtra.h
else 
printf "\n\033[0mAll tests \033[0;32mpassed\033[0m - compilation successful"
fi
rm -rf xtra.h.gch test/main.out main.out a.out
