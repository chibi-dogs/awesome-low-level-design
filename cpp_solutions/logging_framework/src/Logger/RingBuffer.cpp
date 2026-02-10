#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <semaphore>

using namespace std::literals;
constexpr int MAX_SIZE = 5000;
std::mutex m;
std::counting_semaphore semaphore_(1);

struct Element {
    int value;
    std::thread::id thread_id;

    friend std::ostream& operator<<(std::ostream& os, const Element& element)
    {
        os << element.value << element.thread_id;
        return os;
    }
};


void addStuff(std::vector<Element>& numbers)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        std::lock_guard<std::mutex> lock(m);
        numbers.push_back(Element{
            .value = i,
            .thread_id = std::this_thread::get_id()
        });
    }
}

int main()
{
    std::vector<Element> values{};
    values.reserve(MAX_SIZE);
    // jthread would be better!
    std::thread t1(addStuff, std::ref(values));
    std::thread t2(addStuff, std::ref(values));
    std::thread t3(addStuff, std::ref(values));
    t1.join();
    t2.join();
    t3.join();
    for (const auto& element : values)
    {
        std::cout << element << std::endl;
    }
}