ljudge --max-multipass-iteration 20 -u std.cpp -a inter.cpp \
    -i 01 -o 01.a \
    -i 11 -o 11.a \
    -i 21 -o 21.a \
    -i 31 -o 31.a \
    -i 41 -o 41.a \
    -i 51 -o 51.a \
    -- debug
ljudge --max-multipass-iteration 20 -u bloom.cpp -a inter.cpp \
    -i 01 -o 01.a \
    -i 11 -o 11.a \
    -i 21 -o 21.a \
    -i 31 -o 31.a \
    -i 41 -o 41.a \
    -i 51 -o 51.a \
    -- debug # WA???
ljudge --max-multipass-iteration 20 -u tsr.cpp -a inter.cpp \
    -i 01 -o 01.a \
    -i 11 -o 11.a \
    -i 21 -o 21.a \
    -i 31 -o 31.a \
    -i 41 -o 41.a \
    -i 51 -o 51.a \
    -- debug
ljudge --max-multipass-iteration 20 -u deepseek.cpp -a inter.cpp \
    -i 01 -o 01.a \
    -i 11 -o 11.a \
    -i 21 -o 21.a \
    -i 31 -o 31.a \
    -i 41 -o 41.a \
    -i 51 -o 51.a \
    -- debug