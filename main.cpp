#include <iostream>

class Human{
    private:
    char *name;
    char *otak;
    public:
    void change_name(char *new_name){
        name = new_name;
    }

    void print_name(){
        std::cout << name << std::endl;
    }
};

int main(){
    Human human;
    human.print_name();
    human.change_name("Joseph");
    human.print_name();
    return 0;
}