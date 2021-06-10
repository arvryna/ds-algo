CPP_VER=c++17
rm -rf out; mkdir out
BUILD=out/build.o

echo "Compling code with ($CPP_VER) version"
g++ -I lib/ -fsanitize=address,undefined -fno-sanitize-recover=all -std=$CPP_VER -o2 -Wall -Werror -Wsign-compare -o $BUILD $1.cpp

# If $2 is empty, -z will give 1
if [ -z "$2" ]
then
      echo "\n\n********Linting***********\n\n"
      clang-format -i $1.cpp
      clang-tidy $1.cpp -- -std=$CPP_VER
else
      # Checks if second param is equal to string deb
      if [ $2 = "deb" ]
      then
            # Rebuild to generate debug symbols
            g++ -g -std=$CPP_VER -o $BUILD $1.cpp
            echo "\n\nStarting Debugger in TUI mode \n\n"
            gdb $BUILD
      fi
fi

echo "\n*******Output*******\n"
./$BUILD

echo "\n******User Warnings*****\n"
ag "WARN" $1.cpp
echo "\n******END*****\n"