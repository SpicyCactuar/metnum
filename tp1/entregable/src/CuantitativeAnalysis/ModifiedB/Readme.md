Para compilar el generador de b: g++ -o gen_b gen_b.cpp -std=c++11

Para crear las instancias de b:
-(1: output directory)
-(2: teams initial qty)
-(3: results qty)

./main io/ 50 20
./main io/ 100 20
./main io/ 150 20
./main io/ 200 20
./main io/ 250 20
./main io/ 300 20
./main io/ 350 20
./main io/ 400 20
./main io/ 450 20
./main io/ 500 20


Para compilar este archivo: g++ -o main main.cpp -std=c++11

Para simular los experimento:

./main io/test_50.out io/test50.in io/20b_50.in;
./main io/test_100.out io/test100.in io/20b_100.in;
./main io/test_150.out io/test150.in io/20b_150.in;
./main io/test_200.out io/test200.in io/20b_200.in;
./main io/test_250.out io/test250.in io/20b_250.in;
./main io/test_300.out io/test300.in io/20b_300.in;
./main io/test_350.out io/test350.in io/20b_350.in;
./main io/test_400.out io/test400.in io/20b_400.in;
./main io/test_450.out io/test450.in io/20b_450.in;
./main io/test_500.out io/test500.in io/20b_500.in;


