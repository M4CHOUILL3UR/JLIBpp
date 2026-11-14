INC=(
    -Iinclude
    -Isrc
    -I/usr/include
    -I/usr/local/include
)
SRC=(
    src/algebra.cpp
    src/vec.tpp
    src/tensor.tpp
)

WARNING=(
    -Wall
    -Wextra
    -Wpedantic
)


gcc -std=c++26 -O3 "${WARNING}" "${INC}" "${SRC}" -o bin/.out -lstdc++
 
if [ $? -eq 0 ]; then
    echo "Build OK"
else
    echo "Build FAILED"
fi
