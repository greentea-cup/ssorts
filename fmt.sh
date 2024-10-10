#!/bin/sh
test -d "src" && SRC='src/*.c,*.cpp' || SRC=""
test -d "include" && INCLUDE='include/*.h,*.hpp' || INCLUDE=""
astyle --project -r $SRC $INCLUDE
