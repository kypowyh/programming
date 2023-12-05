from flask import Flask, render_template, request, jsonify
import socket
import json
from datetime import datetime, timedelta

app = Flask(__name__)

statistics_data = []
db_server_address = ('127.0.0.1', 6379) # информация о базе данных 
json_file_path = 'output.json' # имя Json файла
with open(json_file_path, "r") as file:
        json_data = json.load(file) 

@app.route('/')
def index():
    return render_template('index2.html', statistics_data=statistics_data)

@app.route('/collect_statistics', methods=['POST'])
def collect_statistics():
    # Получаем данные из запроса
    data = request.json

    # Проверяем наличие необходимых полей в данных
    if 'ip' not in data or 'url' not in data or 'time' not in data:
        return jsonify({'error': 'Invalid data format'}), 400

    # Добавляем данные в хранилище
    statistics_data.append(data)

    send_data_to_database(data)

    return jsonify({'message': 'Statistics collected successfully'}), 200

@app.route('/report', methods=['POST'])
def report():
    send_query_to_database()

    generated_report = generate_report(json_data)

    report_html = render_template('report.html', report=generated_report)

    return report_html

    

def send_query_to_database():
    # Создаем сокет
    db_client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Устанавливаем соединение с сервером базы данных
    db_client_socket.connect(db_server_address)

    query = "JGET" # запрос 

    # Отправляем запрос на сервер
    db_client_socket.send(query.encode())
    response = db_client_socket.recv(1024).decode()

    # Преобразуем ответ в формат JSON
    json_data = json.loads(response)
    # Сохраняем JSON в файл
    with open(json_file_path, 'w') as json_file:
        json.dump(json_data, json_file, indent=4)

    # Закрываем соединение с сервером базы данных
    db_client_socket.close()

def send_data_to_database(data):
    # Создаем сокет
    db_client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Устанавливаем соединение с сервером базы данных
    db_client_socket.connect(db_server_address)

    # Преобразуем данные в строку
    data_str = f"JADD {data['ip']} {data['url']} {data['time']}"

    # Отправляем данные на сервер
    db_client_socket.send(data_str.encode())

    # Закрываем соединение с сервером базы данных
    db_client_socket.close()

def get_time_key(time_str):
    time = datetime.strptime(time_str, "%Y-%m-%dT%H:%M:%S")
    time_key = f"{time.hour:02d}:{time.minute:02d}-{(time + timedelta(minutes=1)).hour:02d}:{(time + timedelta(minutes=1)).minute:02d}"
    return time_key
    
def generate_report(json_data):
    report = {} # создаем словарь для хранения отчета 

    for entry in json_data:
        ip = entry["ip"]
        time = entry["time"]
        url = entry["url"]

        time_key = get_time_key(time)

        if ip not in report:
            report[ip] = {"Total": 0, "TimeData": {}} # создаем запись для ip

        if time_key not in report[ip]["TimeData"]:
            report[ip]["TimeData"][time_key] = {"Total": 0, "URLs": {}} # создаем запись для времени

        report[ip]["Total"] += 1 # увеличиваем количество посещений 
        report[ip]["TimeData"][time_key]["Total"] += 1 # увеличиваем количество посещений

        if url not in report[ip]["TimeData"][time_key]["URLs"]:
            report[ip]["TimeData"][time_key]["URLs"][url] = 1 # создаем запись для сайта 
        else:
            report[ip]["TimeData"][time_key]["URLs"][url] += 1 # увеличиваем количество почещений 

    return report

if __name__ == '__main__':
    app.run(debug=True, host='127.0.0.1', port=5555) # запуск сервиса 