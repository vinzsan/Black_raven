#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <string>

void thread(int &value,int new_val,std::promise<int> retval){
    value = new_val;
    retval.set_value(value);
}

int main(){
    std::promise<int> ret;
    std::future<int> future = ret.get_future();

    std::cout << "Hello world" << std::endl;

    int value = 10;
    std::thread tid(thread,std::ref(value),20,std::move(ret));
    int retval = future.get();

    std::cout << retval << std::endl;
    tid.join();
    return 0;
}