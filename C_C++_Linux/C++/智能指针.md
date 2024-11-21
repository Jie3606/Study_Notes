#### auto_ptr的实现



#### auto_ptr被舍弃的原因?

- copy和=会改变资源的拥有权，不符合编程习惯。
- 在STL容器中使用auto_ptr存在重大的风险，因为容器的元素必须支持（copy constructable）和可赋值（assignable）。
- 不支持对象数组的操作。（delete 和 delete[] 出错）

```c++
template <class Ty>
    class My_auto_ptr
    {
    private:
        Ty* _M_ptr;
    public:
        typedef Ty element_type;

        explicit My_auto_ptr(Ty* p = nullptr) : _M_ptr(p) {}

        ~My_auto_ptr() { delete _M_ptr; }

        element_type* get() const { return _M_ptr; }

        element_type& operator*() const
        {
            return *_M_ptr;
        }
        element_type* operator->() const
        {
            return _M_ptr;
        }
        void reset(Ty* p = nullptr)
        {
            if (p != _M_ptr)
            {
                delete _M_ptr;
            }
            _M_ptr = p;
        }
        element_type* releace()
        {
            Ty* _tmp = _M_ptr;
            _M_ptr = nullptr;
            return _tmp;
        }
        void swap(My_auto_ptr& _other)
        {
            std::swap(this->_M_ptr, _other._M_ptr);
        }
        My_auto_ptr(My_auto_ptr& _other) : _M_ptr(_other.releace()) {}

        My_auto_ptr& operator=(My_auto_ptr& _other)
        {
            reset(_other.releace());
            return *this;
        }
    };
```

