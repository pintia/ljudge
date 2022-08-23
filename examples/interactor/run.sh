ljudge -u ac.cpp -a interactor.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # no checker
ljudge -u ac.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # with checker
ljudge -u wa.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # wa
ljudge -u pe.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # pe?
ljudge -u too-many-iter.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # TLE
ljudge --max-cpu-time 10 --max-real-time 10 --max-interactor-cpu-time 10 --max-interactor-real-time 10 -u too-many-iter.cpp -a interactor.cpp -c check.cpp -i 01 -o 01.out -i 19 -o 19.out -i 20 -o 20.out -i 21 -o 21.out --debug # wa
