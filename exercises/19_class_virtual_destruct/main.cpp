#include "../exercise.h"

struct A {
    // 1. 类内声明静态字段
    static int num_a;

    A() {
        ++num_a;
    }
    // 2. 必须定义虚析构函数，确保派生类对象能被正确销毁
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 3. 在类外定义并初始化静态字段
int A::num_a = 0;

struct B final : public A {
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

// 4. 同理初始化 B 的静态字段
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    
    // a 是 A，b 是 B。注意：创建 B 会自动先创建 A（继承关系）
    ASSERT(A::num_a == 2, "A was created twice (once for a, once for b)");
    ASSERT(B::num_b == 1, "B was created once");
    ASSERT(a->name() == 'A', "a is an instance of A");
    ASSERT(b->name() == 'B', "b is an instance of B");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B; // 向上转型
    ASSERT(A::num_a == 1, "Creating B also creates A");
    ASSERT(B::num_b == 1, "One B created");
    // 因为 name() 是虚函数，所以即使是 A* 指针，也会调用 B 的实现
    ASSERT(ab->name() == 'B', "Dynamic dispatch to B::name()");

    // TODO: 补全正确的转换语句（将 A* 转换为 B&）
    // 使用 dynamic_cast 或 static_cast。这里已知 ab 确实指向 B，可用 static_cast
    B &bb = static_cast<B &>(*ab);
    ASSERT(bb.name() == 'B', "bb is a reference to the B object");

    delete ab; // 如果 A 没有虚析构函数，这里会出问题
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}