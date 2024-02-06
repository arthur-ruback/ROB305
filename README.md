# ROB305

Compilation instructions:

mkdir build

cd build

cmake ..

make

## For TP1

./test_timespec

## For TP2

./test_pthread

### Question answers

A) 

The value of the counter expected is nLoops*nTasks but when nTasks > 1 the value shown is always less than that. This happends because of the rece condition around the counter value. Although a += operation seems atomic, it is devided in at least 3 parts: get the value from memory, add the value and store the value in memory. Let us imagine an example that while a thread has already got a value from memory, lets say 42, the other one also gets it, so they now both have in registers independly 42. The first one finishes this iteraction and stores 43 in memory. Afterwards thread2 executes and it also stores 43 in memory. In this case both threads ran one iteraction but the counter value was increased only once.

B) 

Although now the result is correct, using the mutexes to protect the variable creates some overhead as it makes numerous call to the kernel to get and release the mutex. Therefore we observe that the execution time has increased significantly.

## For TP3

./test_timer

### Question answers

B) 

The class Timer is abstract and therefore should not be instantiated, the ones that should be instantiated are the classes that inherit form it. 

The function callback() is virtual and protected because it is not implemented by the currest class and should be overwritten by any other derived class. The function call_callback() on the other hand needs to be private and only implemented by Timer (and also Static), the other derived classes need to ask Timer for this call. This happends because it acts as a bridge between the OS and the class: the particular signature of this function allows it to be called by the OS, afterwars it calls the apropriate callback() function of the derived class. The constructor and destructor have to be public as they are used in the declaration and destruction of the object, the same as star() and stop(). 

