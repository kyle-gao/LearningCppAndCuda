#include <iostream>
#include <vector>

using namespace std;


class MyClass {       // The class
public:             // Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
    int traverseMethod(int number);
    string emptyAttribute;
   

    void setAttribute(string attribute) {
        emptyAttribute = attribute;   //a method can be used to substitute object attribute, note that we don't need self.attribute() unlike python
    }

    void printAttribute() {
        cout << "printing from MyClass object " << emptyAttribute << endl;
    }


    string inheritThis = "This is inherited";
};

class WithConstructor {
public:
    int fill;

    WithConstructor(int var) { //The constructor is a function with the same name as class, and is not required.
        fill = var;
    }
};

class MyPrivateClass { //by default all attributes are private
    int x;   // Private attribute
    int y;   // Private attribute

public: //Since the class's methods have access to private:, they can be used to set and retrieve private attributes. This is called encapsulation.

    void setX(int var) {
        x = var;
    }
    int getX() {
        return x;
    }
};

class SubClass : public MyClass {
public:
    void subClassMethod(){
        cout << "This is a subclass" << inheritThis;  //Note that private attributes and methods cannot be inherited.
    }
};


int MyClass::traverseMethod(int num) {  //The :: operator is the scope resolution operator. It can be used to go inside a class or function.
        return num; //In this case, we use it to go inside MyClass and change the definition of traverseMethod.
}


int main() {
    MyClass myObj;  // Create an object of MyClass Note that it does not populate the attribute unlike Python

// Access attributes and set values
    myObj.myNum = 15;
    myObj.myString = "Some text";

    // Print attribute values
    cout << myObj.myNum << "\n";
    cout << myObj.myString << endl;
    cout << myObj.emptyAttribute; //Doesnt print but no error

    myObj.setAttribute("Not Empty");
    myObj.printAttribute();
    
    int varnum;
    varnum = myObj.traverseMethod(3);
    cout << varnum << endl;

    WithConstructor myobj2(314);
    cout << myobj2.fill << endl;

    MyPrivateClass privateobj;
    privateobj.setX(3000);
    int x = privateobj.getX();
    cout << x << endl;

    SubClass mySubClass;
    mySubClass.subClassMethod();
}

// Multiple inheritence
class MyChildClass : public MyClass, public MyPrivateClass {  //Note that multiple classes can be simultaneously inherited from
};

//Polymorphism is when methods are overwritten in inherited classes so that that same name methnod name calls to
//a different function depending on the class 

