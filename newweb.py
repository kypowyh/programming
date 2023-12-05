from flask import Flask, render_template, request, redirect
import hashlib
import socket
import requests
from datetime import datetime  # Добавлен импорт datetime

app = Flask(__name__)

# Словарь для хранения сокращенных ссылок
shortened_links = {}

server_ip = '127.0.0.1'
server_port = 6379

statistics_server_ip = '127.0.0.1'  
statistics_server_port = 5555 

def send_data_to_server(short_link, original_link):
    # Создаем сокет
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Устанавливаем соединение с сервером
    client_socket.connect((server_ip, server_port))

    # Создаем сообщение, которое будет отправлено серверу
    message = f"HSET {original_link} {short_link}"

    # Отправляем сообщение на сервер
    client_socket.send(message.encode())

    # Получаем ответ от сервера
    response = client_socket.recv(1024).decode()

    # Закрываем соединение с сервером
    client_socket.close()

def get_short_link_from_server(original_link):
    # Создаем сокет
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Устанавливаем соединение с сервером
    client_socket.connect((server_ip, server_port))

    # Создаем сообщение, которое будет отправлено серверу
    message = f"HGET {original_link}"

    # Отправляем сообщение на сервер
    client_socket.send(message.encode())

    # Получаем ответ от сервера
    response = client_socket.recv(1024).decode()

    # Закрываем соединение с сервером
    client_socket.close()

    return response

def send_statistics(ip, link):
    # Создаем временную метку
    current_datetime = datetime.now()

# Преобразуем дату и время в строку
    time = current_datetime.strftime("%Y-%m-%dT%H:%M:%S")

    # Создаем сообщение для отправки на сервер статистики
    data = {'ip': ip, 'url': link, 'time': time}
    
    # Отправляем POST-запрос на сервер статистики
    statistics_url = f'http://{statistics_server_ip}:{statistics_server_port}/collect_statistics'
    requests.post(statistics_url, json=data)

def generate_short_link(original_link):
    # Пытаемся получить короткую ссылку из базы данных
    existing_short_link = get_short_link_from_server(original_link)

    if existing_short_link == "Key not found in the hash table.":
        # Если ключ не найден, генерируем новую короткую ссылку
        hash_value = hashlib.sha256(original_link.encode()).hexdigest()
        short_link = f'http://localhost:5000/{hash_value[:8]}'

        # Сохраняем новую короткую ссылку в базе данных
        send_data_to_server(short_link, original_link)

        return short_link
    else:
        # Возвращаем существующую короткую ссылку
        return existing_short_link

@app.route('/')
def Decor():
    return render_template('index.html')

@app.route('/shorten', methods=['POST'])
def shorten_link():
    if request.method == 'POST':
        original_link = request.form.get('original_link')

        # Генерируем уникальную короткую ссылку на основе оригинальной
        shortened_link = generate_short_link(original_link)

        # Сохраняем соответствие в словаре
        shortened_links[shortened_link] = original_link

        return f"Сокращенная ссылка: <a href='{shortened_link}'>{shortened_link}</a>"

@app.route('/<string:link_id>')
def redirect_to_original(link_id):
    shortened_link = f'http://localhost:5000/{link_id}'
    original_link = shortened_links.get(shortened_link)

    if original_link:
        # Получаем IP адрес клиента
        client_ip = request.remote_addr

        link = original_link + '(' + link_id + ')'
        
        # Отправляем статистику на сервер
        send_statistics(client_ip, link)

        return redirect(original_link)
    else:
        return "Ссылка не найдена!"

if __name__ == '__main__':
    app.run(debug=True, host='localhost', port=5000)
