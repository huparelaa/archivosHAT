## How to run?

```sh
g++ -o hat HatCreator.cpp
./hat
g++ -o programa test.cpp -std=c++11 -Wall -Wextra `pkg-config --cflags --libs opencv4`
./programa
```