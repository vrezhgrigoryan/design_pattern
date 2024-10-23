#include <iostream>
#include <mutex>
std::mutex mutex;
class Singleton
{
    private:
        static Singleton* instance;
        int m_num{0};
        Singleton(const int num) : m_num{num}
        {
            std::lock_guard<std::mutex> myLock(mutex);
        }
        Singleton()
        {
            std::lock_guard<std::mutex> myLock(mutex);
        }
    public:
        Singleton(const Singleton &) = delete;
        void operator=(const Singleton &) = delete;
        static Singleton* getInstance(int num = 0)
        {
            if(instance == nullptr)
            {
                instance = new Singleton(num);
            }
            return instance;
        }
        void setNum(const int num)
        {
            m_num = num;
        }
        int getNum() const
        {
            return m_num;
        }
    
};

Singleton* Singleton::instance = nullptr;
int main() 
{
    Singleton* inst = Singleton::getInstance();
    std::cout << inst->getNum() << "\n";
    Singleton* inst1 = Singleton::getInstance(2);
    std::cout << inst->getNum() << "\n";
    inst1->setNum(2);
    std::cout << inst->getNum() << " " << inst1->getNum() << "\n";
    return 0;
}
