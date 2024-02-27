#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;

struct UserRequest {
    string query;
};

// Структура очереди
struct QueueNode {
    UserRequest* data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
    mutex mtx;
    condition_variable cv;

    Queue() : front(nullptr), rear(nullptr), size(0) {}
};

// Функция добавления запроса в очередь
void enqueue(Queue& queue, UserRequest* request) {
    unique_lock<mutex> lock(queue.mtx);
    QueueNode* newNode = new QueueNode;
    newNode->data = request;
    newNode->next = nullptr;

    if (queue.size == 0) {
        queue.front = newNode;
    }
    else {
        queue.rear->next = newNode;
    }

    queue.rear = newNode;
    queue.size++;
    lock.unlock();
    queue.cv.notify_one(); // Уведомляем другие потоки о наличии нового запроса
}

// Функция извлечения запроса из очереди
UserRequest* dequeue(Queue& queue) {
    unique_lock<mutex> lock(queue.mtx);
    if (queue.size == 0) {
        return nullptr;
    }

    QueueNode* frontNode = queue.front;
    UserRequest* request = frontNode->data;
    queue.front = frontNode->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }

    queue.size--;
    delete frontNode;
    return request;
}

// функция для обработки запроса пользователя
void process(UserRequest* request) {

    unique_lock<mutex> lock(m);
    // происходит обработка запроса пользователя
    cout << "Processing: " << request->query << endl;
}

// обработка запросов
void request(Queue& queue) {
    while (true) {
        UserRequest* request = dequeue(queue);
        if (request == nullptr) {
            // поток ждет уведомления о появлении нового запроса
            unique_lock<mutex> lock(queue.mtx);
            queue.cv.wait(lock);
        }
        else {
            process(request);
            delete request;
        }
    }
}

int main() {
    Queue requestQueue;

    // Запуск трех потоков для обработки запросов
    vector<thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(request, ref(requestQueue));
    }

    // Добавление 10 запросов в очередь
    for (int i = 0; i < 10; ++i) {
        UserRequest* request = new UserRequest{ "query" + to_string(i) };
        enqueue(requestQueue, request);
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
