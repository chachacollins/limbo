CC="gcc"
BUILD_FILE="main.c lexer.c memory.c chunk.c value.c"
BUILD_FLAGS="-Wextra -Wall -Werror --pedantic -std=c23 -fanalyzer"

set -xe

gcc -g -O3 $BUILD_FLAGS $BUILD_FILE -o limbo
