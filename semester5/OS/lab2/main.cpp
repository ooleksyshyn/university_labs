#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>

struct ProducerConsumer
{
    ProducerConsumer() : producer([this]{ run_producer(); }), consumer([this]{ run_consumer(); }) {}

    ~ProducerConsumer() {
        if (producer.joinable()) {
            producer.join();
        }
        if (consumer.joinable()) {
            consumer.join();
        }
    }
private:
    std::mutex producer_mutex;
    std::mutex consumer_mutex;
    std::condition_variable cv_producer;
    std::condition_variable cv_consumer;
    std::thread producer;
    std::thread consumer;

    struct SomeData {
        int hmm = 1;
        std::string kek = "dgoslnzfdjbm";
        double value = 913190;
    };

    static const std::size_t max_size = 10;
    int size = 0;
    std::queue<SomeData> shared_memory;

    void run_consumer() {
        while (true) {
            if (shared_memory.empty()) {
                std::unique_lock<std::mutex> lock(consumer_mutex);
                cv_consumer.wait(lock);
            } else {
                std::cout << size - shared_memory.size() << "\n";
                shared_memory.pop();
                --size;
                if (size == max_size - 1)
                    cv_producer.notify_one();
            }
        }
    }

    void run_producer() {
        while (true) {
            if (shared_memory.size() == max_size) {
                std::unique_lock<std::mutex> lock(producer_mutex);
                cv_producer.wait(lock);
            } else {
                std::cout << size - shared_memory.size() << "\n";
                ++size;
                shared_memory.push(SomeData());
                if (size == 1)
                    cv_consumer.notify_one();
            }
        }
    }
};

int main() {
    ProducerConsumer problem;
    return 0;
}
