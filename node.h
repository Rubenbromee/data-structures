// A simple node class, used for other data structures
namespace rb {
    template <typename T>
    struct node {
        T data;
        node* next;
        node(T value) {
            data = value;
            next = nullptr;
        }
    };
}
