#include <iostream>
#include <vector>

// --------------------- 1. Singleton ---------------------
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}  // Constructor is private

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;

// --------------------- 2. Factory Method ---------------------
class Product {
public:
    virtual void use() = 0;  // Pure virtual function
};

class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "Using Product A" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "Using Product B" << std::endl;
    }
};

class Creator {
public:
    virtual Product* factoryMethod() = 0;  // Factory method
};

class ConcreteCreatorA : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductA();
    }
};

class ConcreteCreatorB : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductB();
    }
};

// --------------------- 3. Abstract Factory ---------------------
class AbstractProductA {
public:
    virtual void use() = 0;
};

class AbstractProductB {
public:
    virtual void use() = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Concrete Product A1" << std::endl;
    }
};

class ConcreteProductA2 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Concrete Product A2" << std::endl;
    }
};

class ConcreteProductB1 : public AbstractProductB {
public:
    void use() override {
        std::cout << "Using Concrete Product B1" << std::endl;
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    void use() override {
        std::cout << "Using Concrete Product B2" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ConcreteProductA1();
    }

    AbstractProductB* createProductB() override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ConcreteProductA2();
    }

    AbstractProductB* createProductB() override {
        return new ConcreteProductB2();
    }
};

// --------------------- 4. Builder ---------------------
class ProductBuilder {
private:
    std::string partA;
    std::string partB;

public:
    void setPartA(const std::string& part) {
        partA = part;
    }

    void setPartB(const std::string& part) {
        partB = part;
    }

    void show() {
        std::cout << "Product Parts: " << partA << ", " << partB << std::endl;
    }
};

class Builder {
protected:
    ProductBuilder* product;

public:
    Builder() { product = new ProductBuilder(); }

    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;

    ProductBuilder* getProduct() {
        return product;
    }
};

class ConcreteBuilder : public Builder {
public:
    void buildPartA() override {
        product->setPartA("Part A");
    }

    void buildPartB() override {
        product->setPartB("Part B");
    }
};

// --------------------- 5. Adapter ---------------------
class Adaptee {
public:
    void specificRequest() {
        std::cout << "Specific request." << std::endl;
    }
};

class Target {
public:
    virtual void request() = 0;
};

class Adapter : public Target {
private:
    Adaptee* adaptee;

public:
    Adapter(Adaptee* a) : adaptee(a) {}

    void request() override {
        adaptee->specificRequest();
    }
};

// --------------------- 6. Decorator ---------------------
class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "ConcreteComponent operation." << std::endl;
    }
};

class Decorator : public Component {
protected:
    Component* component;

public:
    Decorator(Component* comp) : component(comp) {}

    void operation() override {
        component->operation();
    }
};

class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator(Component* comp) : Decorator(comp) {}

    void operation() override {
        Decorator::operation();
        std::cout << "ConcreteDecorator operation." << std::endl;
    }
};

// --------------------- 7. Observer ---------------------
class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

class ConcreteObserver : public Observer {
public:
    void update() override {
        std::cout << "Observer updated!" << std::endl;
    }
};

// --------------------- 8. Strategy ---------------------
class Strategy {
public:
    virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute() override {
        std::cout << "Executing strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute() override {
        std::cout << "Executing strategy B" << std::endl;
    }
};

class Context {
private:
    Strategy* strategy;

public:
    Context(Strategy* strat) : strategy(strat) {}

    void setStrategy(Strategy* strat) {
        strategy = strat;
    }

    void executeStrategy() {
        strategy->execute();
    }
};

// --------------------- 9. Command ---------------------
class Command {
public:
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
private:
    std::string name;

public:
    ConcreteCommand(const std::string& n) : name(n) {}

    void execute() override {
        std::cout << "Executing command: " << name << std::endl;
    }
};

class Invoker {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void invoke() {
        command->execute();
    }
};

// --------------------- 10. Mediator ---------------------
class Mediator;

class Colleague {
protected:
    Mediator* mediator;

public:
    Colleague(Mediator* med) : mediator(med) {}
    virtual void send() = 0;
    virtual void receive() = 0;
};

class Mediator {
public:
    virtual void notify(Colleague* colleague) = 0;
};

class ConcreteColleagueA : public Colleague {
public:
    ConcreteColleagueA(Mediator* med) : Colleague(med) {}

    void send() override {
        std::cout << "Colleague A sends a message." << std::endl;
        mediator->notify(this);
    }

    void receive() override {
        std::cout << "Colleague A received a message." << std::endl;
    }
};

class ConcreteMediator : public Mediator {
private:
    ConcreteColleagueA* colleagueA;

public:
    ConcreteMediator(ConcreteColleagueA* a) : colleagueA(a) {}

    void notify(Colleague* colleague) override {
        if (colleague == colleagueA) {
            colleagueA->receive();
        }
    }
};

// --------------------- Main Function ---------------------
int main() {
    // Example of Singleton
    Singleton* singleton = Singleton::getInstance();

    // Example of Factory Method
    Creator* creatorA = new ConcreteCreatorA();
    Product* productA = creatorA->factoryMethod();
    productA->use();

    // Example of Abstract Factory
    AbstractFactory* factory1 = new ConcreteFactory1();
    AbstractProductA* product1A = factory1->createProductA();
    AbstractProductB* product1B = factory1->createProductB();
    product1A->use();
    product1B->use();

    // Example of Builder
    ConcreteBuilder* builder = new ConcreteBuilder();
    builder->buildPartA();
    builder->buildPartB();
    ProductBuilder* builtProduct = builder->getProduct();
    builtProduct->show();

    // Example of Adapter
    Adaptee* adaptee = new Adaptee();
    Target* adapter = new Adapter(adaptee);
    adapter->request();

    // Example of Decorator
    Component* component = new ConcreteComponent();
    Decorator* decorator = new ConcreteDecorator(component);
    decorator->operation();

    // Example of Observer
    Subject* subject = new Subject();
    ConcreteObserver* observer = new ConcreteObserver();
    subject->attach(observer);
    subject->notify();

    // Example of Strategy
    Strategy* strategyA = new ConcreteStrategyA();
    Context* context = new Context(strategyA);
    context->executeStrategy();
    Strategy* strategyB = new ConcreteStrategyB();
    context->setStrategy(strategyB);
    context->executeStrategy();

    // Example of Command
    Invoker* invoker = new Invoker();
    Command* command = new ConcreteCommand("MyCommand");
    invoker->setCommand(command);
    invoker->invoke();

    // Example of Mediator
    ConcreteColleagueA* colleagueA1 = new ConcreteColleagueA(nullptr);
    ConcreteMediator* mediator = new ConcreteMediator(colleagueA1);
    colleagueA1->send();

    // Clean up memory
    delete productA;
    delete creatorA;
    delete product1A;
    delete product1B;
    delete factory1;
    delete builtProduct;
    delete builder;
    delete adaptee;
    delete adapter;
    delete component;
    delete decorator;
    delete subject;
    delete observer;
    delete strategyA;
    delete strategyB;
    delete context;
    delete command;
    delete invoker;
    delete colleagueA1;
    delete mediator;

    return 0;
}
