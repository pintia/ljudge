ljudge -u ac.cpp -a interactor.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # no checker
ljudge -u ac.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # with checker
ljudge -u wa.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # wa
ljudge -u pe.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # pe?
ljudge -u too-many-iter.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # TLE
ljudge --max-cpu-time 15 --max-real-time 30 --max-interactor-cpu-time 15 --max-interactor-real-time 30 -u too-many-iter.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out # wa
