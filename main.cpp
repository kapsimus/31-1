#include <iostream>

class Toy {
private:
    std::string name;
public:
    Toy(): name("NoName"){};
    Toy (std::string _name): name(_name){};
};

class Shared_Ptr_Toy {
private:
    Toy* obj;
    int ptrCount;
public:
    Shared_Ptr_Toy() {
        obj = new Toy();
        ptrCount = 0;
    }
    Shared_Ptr_Toy(std::string _name) {
        obj = new Toy(_name);
        ptrCount = 0;
    }
    Shared_Ptr_Toy(const Shared_Ptr_Toy& other) {
        obj = new Toy(*other.obj);
        ptrCount++;
    }
    Shared_Ptr_Toy& operator = (const Shared_Ptr_Toy& other) {
        if (this == &other) {
            return *this;
        }
        if (obj != nullptr) {
            delete obj;
        }
        obj = new Toy(*other.obj);
        ptrCount++;
        return *this;
    }
    ~Shared_Ptr_Toy() {
        ptrCount--;
        if (ptrCount == 0 && obj != nullptr) {
            delete obj;
        }
    }
};

class Dog {
private:
    std::string name;
    int age;
    Shared_Ptr_Toy lovelyToy;
public:

    Dog(std::string _name, std::string _toyName, int _age): name(_name), lovelyToy(_toyName) {
        if (_age >= 0 && _age <= 30) {
            age = _age;
        }
    }
    Dog(): Dog("Druzhok", "sometoy", 0) {}
    Dog (std::string _name): Dog(_name, "sometoy", 0) {}
    Dog(int _age): Dog("Druzhok", "sometoy", _age) {}
    Dog (std::string _name, int _age): Dog(_name, "sometoy", _age) {}

    Shared_Ptr_Toy getLovelyToy() {
        return lovelyToy;
    }
    void setLovelyToy(Shared_Ptr_Toy _lovelyToy) {
        lovelyToy = _lovelyToy;
    }
    void setLovelyToy(std::string  _lovelyToy) {
        lovelyToy = _lovelyToy;
    }
};



int main() {
    Dog* a = new Dog();
    Dog c;
    {
        Dog b;
        b.setLovelyToy("Ball");
        a->setLovelyToy(b.getLovelyToy());
        c.setLovelyToy(a->getLovelyToy());
    }
    delete a;
    return 0;
}
