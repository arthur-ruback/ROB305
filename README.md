# ROB305

This work aims to implement the libraries and corresponding tests to the ROB305 [course](https://irfu.cea.fr/Pisp/shebli.anvar/prog-mt-rtos/index.html) from Anvar Shebli.

Since the libraries are shared between projects, they are all grouped in the same folder **src**.

Each part of the project has a corresponding test file, sometimes several questions are grouped in one executable and sometimes they are separeted. See execution instructions for more.

## Compilation instructions:

```bash
mkdir build
cd build
cmake ..
make
```

## Execution instructions:

All the executables are put automatically in the build folder. The following commands assumes that you are in the build folder.

#### TP1

```bash
./TP1-ABC
```

#### TP2

```bash
./TP2
```

#### TP3

```bash
./TP3-A
./TP3-B
./TP3-C
```

#### TP4

*nloops (int) ->* Number of loops each thread will do;
*nThreads (int) ->* Number of threads lauched concurrently;
*protection (char[ ]) ->* If a mutex will be used.

```bash
./TP4-A (nloops) (nThreads) (protection)
```

```bash
./TP4-B (nloops) (nThreads) (protection)
```

```bash
./TP4-C (nloops) (nThreads) (protection)
```


#### TP5

*invSafe (char[ ]) ->* If the mutex will use priority inheritance protocal or not. Use "prio_inversion_safe" or "prio_inversion_non_safe" for the respective options.

**[NOTE]**

This test case needs to be run on super-user mode to set the real-time scheduling policy, otherwise it will through a fatal error.

```bash
sudo ./TP5 (invSafe)
```

## Required comments

#### For TP2

**A)** The value of the counter expected is nLoops*nTasks but when nTasks > 1 the value shown is always less than that. This happends because of the rece condition around the counter value. Although a += operation seems atomic, it is devided in at least 3 parts: get the value from memory, add the value and store the value in memory. Let us imagine an example that while a thread has already got a value from memory, lets say 42, the other one also gets it, so they now both have in registers independly 42. The first one finishes this iteraction and stores 43 in memory. Afterwards thread2 executes and it also stores 43 in memory. In this case both threads ran one iteraction but the counter value was increased only once.

**B)** Although now the result is correct, using the mutexes to protect the variable creates some overhead as it makes numerous call to the kernel to get and release the mutex. Therefore we observe that the execution time has increased significantly.

#### For TP3

**B)** The class Timer is abstract and therefore should not be instantiated, the ones that should be instantiated are the classes that inherit form it. 

The function callback() is virtual and protected because it is not implemented by the currest class and should be overwritten by any other derived class. The function call_callback() on the other hand needs to be private and only implemented by Timer (and also Static), the other derived classes need to ask Timer for this call. This happends because it acts as a bridge between the OS and the class: the particular signature of this function allows it to be called by the OS, afterwars it calls the apropriate callback() function of the derived class. The constructor and destructor have to be public as they are used in the declaration and destruction of the object, the same as star() and stop(). 

