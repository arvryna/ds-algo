
#include <iostream>
template <typename vt>

// This class is based on RAII wrapper (Resource Acquisition is Initialization)
class smart_ptr {
public:
    smart_ptr() noexcept(std::is_nothrow_default_constructible_v<vt>) {
        ptr_ = new (std::nothrow) vt();
    }

    // Move constructor
    smart_ptr(smart_ptr&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    ~smart_ptr() noexcept(std::is_nothrow_destructible_v<vt>) {
        if (ptr_ != nullptr) {
            ptr_->~vt();
            operator delete(ptr_, std::nothrow);
        }
    }

    // Explitly deleting Copy constructor and copy assignment operator
    smart_ptr(const smart_ptr& other) = delete;
    smart_ptr& operator=(const smart_ptr& other) = delete;

    // Move assignment operator
    smart_ptr& operator=(smart_ptr&& other) noexcept(std::is_nothrow_destructible_v<vt>) {
        if (this != &other) {
            this->~smart_ptr();  // may throw if destructor of vt type thows exception
            // Explitly calling the move constructor, so that other will be passed as rvalue
            new (this) smart_ptr(std::move(other));
        }
        return *this;
    }

    vt* get() const& noexcept {
        return ptr_;
    }

    vt* operator->() const noexcept {
        return ptr_;
    }

    vt& operator*() const noexcept {
        return *ptr_;
    }

private:
    vt* ptr_;
};

struct logger {
    logger() {
        std::cout << "Constructor" << std::endl;
    }
    ~logger() {
        std::cout << "Destructor" << std::endl;
    }
    void PrintAddress() {
        std::cout << "Logger Address: " << this << std::endl;
    }
};

// Testing smart_ptr class to test move semantics (std::move)
int main() {

    // calls default constructor of logger
    smart_ptr<logger> ptr;
    ptr->PrintAddress();

    // Moving resource from ptr to ptr2, this invalidates ptr2
    smart_ptr<logger> ptr2(std::move(ptr));
    std::cout << ptr.get() << std::endl;
    ptr2->PrintAddress();

    smart_ptr<logger> ptr3;
    ptr3->PrintAddress();
    ptr3 = std::move(ptr2);

    std::cout << ptr2.get() << std::endl;
    ptr3->PrintAddress();
    return 0;
}