const express = require('express');
const mysql = require('mysql');
const bodyParser = require('body-parser');
const path = require('path');
const session = require('express-session');
const bcrypt = require('bcrypt');  // Import bcrypt
const { sendEmail, sendQR } = require('./mailer');
const app = express();

// Middleware для обработки данных формы
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());  // Для обработки JSON-запросов
app.use(express.static(path.join(__dirname, 'public')));

// Настройка сессий
app.use(session({
    secret: 'your_secret_key',
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false } // Для production использовать secure: true с HTTPS
}));

// Подключение к базе данных
const connection = mysql.createConnection({
    host: 'MySQL-5.7',
    user: 'root',
    password: null,
    database: 'Events'
});

connection.connect((err) => {
    if (err) {
        console.error('Error connecting to the database:', err.code);
        console.error('Fatal error:', err.fatal);
        return;
    }
    console.log('Connected to the database');
});

// Генерация случайного кода подтверждения
function generateConfirmationCode() {
    return Math.floor(100000 + Math.random() * 900000).toString();
}

// Перенаправление на страницу регистрации при обращении к корневому маршруту
app.get('/', (req, res) => {
    res.redirect('/register');
});

// Отображение страницы регистрации
app.get('/register', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'register.html'));
});

// Отображение страницы авторизации
app.get('/login', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

// Отображение страницы подтверждения
app.get('/confirm', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'confirm.html'));
});

// Отображение страницы мероприятий пользователя (только для администраторов)
app.get('/userevents', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'userevents.html'));
});

// Отображение страницы создания мероприятия (только для администраторов)
app.get('/createevent', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'createevent.html'));
});

// Отображение страницы всех мероприятий (для участников)
app.get('/allevents', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'allevents.html'));
});

app.post('/register', async (req, res) => {
    const { userEmail, userPasswd, name, surname, type } = req.body;

    // Проверка существования пользователя
    connection.query(
        'SELECT * FROM Users WHERE userEmail = ?',
        [userEmail],
        (err, results) => {
            if (err) {
                console.error('Error checking user existence:', err);
                res.status(500).send('Ошибка при проверке пользователя.');
                return;
            }

            if (results.length > 0) {
                res.redirect(`/register?error=Учетная запись уже существует.`);
            } else {
                const confirmationCode = generateConfirmationCode();
                req.session.userEmail = userEmail;
                req.session.confirmationCode = confirmationCode;
                req.session.type = type; // Сохраняем тип пользователя в сессии
                req.session.name = name;
                req.session.surname = surname;

                // Hash password before saving to session
                bcrypt.hash(userPasswd, 10, (err, hash) => {
                    if (err) {
                        console.error('Error hashing password:', err);
                        res.status(500).send('Ошибка при хэшировании пароля.');
                        return;
                    }
                    req.session.userPasswd = hash;

                    sendEmail(userEmail, confirmationCode)
                        .then(() => {
                            res.redirect(`/confirm?email=${encodeURIComponent(userEmail)}`);
                        })
                        .catch((err) => {
                            console.error('Error sending confirmation email:', err);
                            res.status(500).send('Ошибка при отправке подтверждающего письма.');
                        });
                });
            }
        }
    );
});

// Обработка авторизации
app.post('/login', (req, res) => {
    const { userEmail, userPasswd } = req.body;
    connection.query(
        'SELECT * FROM Users WHERE userEmail = ?',
        [userEmail],
        (err, results) => {
            if (err) {
                console.error('Error during login:', err);
                res.status(500).send('Ошибка при авторизации.');
                return;
            }
            if (results.length > 0) {
                const user = results[0];
                bcrypt.compare(userPasswd, user.userPasswd, (err, result) => {
                    if (err) {
                        console.error('Error during password comparison:', err);
                        res.status(500).send('Ошибка при сравнении паролей.');
                        return;
                    }
                    if (result) {
                        const confirmationCode = generateConfirmationCode();
                        req.session.userEmail = userEmail;
                        req.session.confirmationCode = confirmationCode;
                        req.session.userID = user.userID;
                        req.session.type = user.TypeID;

                        sendEmail(userEmail, confirmationCode)
                            .then(() => {
                                res.redirect(`/confirm?email=${encodeURIComponent(userEmail)}`);
                            })
                            .catch((err) => {
                                console.error('Error sending confirmation email:', err);
                                res.status(500).send('Ошибка при отправке подтверждающего письма.');
                            });
                    } else {
                        res.redirect('/login?error=Неправильный email или пароль.');
                    }
                });
            } else {
                res.redirect('/login?error=Неправильный email или пароль.');
            }
        }
    );
});

// Обработка подтверждения
app.post('/confirm', (req, res) => {
    const { userEmail, confirmationCode } = req.body;
    const session = req.session;

    if (session && session.confirmationCode === confirmationCode) {
        if (session.name && session.surname && session.type) {
            // Завершение регистрации
            const { userPasswd, name, surname, type } = session;
            connection.query(
                'INSERT INTO Users (userEmail, userPasswd, name, surname, TypeID) VALUES (?, ?, ?, ?, ?)',
                [userEmail, userPasswd, name, surname, type],
                (err, results) => {
                    if (err) {
                        console.error('Error during registration:', err);
                        res.status(500).send('Ошибка при регистрации.');
                        return;
                    }
                    const userID = results.insertId; // Получение userID из результатов вставки
                    req.session.userID = userID; // Сохранение userID в сессии
                    req.session.type = type;
                    if (type == 1) {
                        res.redirect(`/userevents?email=${encodeURIComponent(userEmail)}&userID=${userID}`);
                    } else {
                        res.redirect(`/allevents?email=${encodeURIComponent(userEmail)}&userID=${userID}`);
                    }
                }
            );
        } else {
            // Завершение авторизации
            const { userID, type } = session;
            if (type === 1) {
                res.redirect(`/userevents?email=${encodeURIComponent(userEmail)}&userID=${userID}`);
            } else {
                res.redirect(`/allevents?email=${encodeURIComponent(userEmail)}&userID=${userID}`);
            }
        }
    } else {
        res.redirect(`/confirm?email=${encodeURIComponent(userEmail)}&error=Неправильный код подтверждения.`);
    }
});

// Обработка создания мероприятия (только для администраторов)
app.post('/createevent', (req, res) => {
    const { userEmail, title, count, start, end, info, adress } = req.body;
    const session = req.session;
    connection.query(
        'INSERT INTO Event (count, start, end, adress, title, userID, info) VALUES (?, ?, ?, ?, ?, ?, ?)',
        [count, start, end, adress, title, session.userID, info],
        (err, results) => {
            if (err) {
                console.error('Error during event creation:', err);
                res.status(500).send('Ошибка при создании мероприятия.');
                return;
            }
            res.redirect(`/userevents?email=${encodeURIComponent(userEmail)}`);
        }
    );
});

// Обработка запроса на получение списка мероприятий для конкретного пользователя
app.get('/api/events', (req, res) => {
    const { email } = req.query;
    connection.query(
        'SELECT * FROM Event WHERE userID = (SELECT userID FROM Users WHERE userEmail = ?)',
        [email],
        (err, results) => {
            if (err) {
                console.error('Error fetching events:', err);
                res.status(500).send('Ошибка при получении списка мероприятий.');
                return;
            }
            res.json(results);
        }
    );
});

app.get('/api/allevents', (req, res) => {
    const userID = req.session.userID;
    const query = `
        SELECT e.*, 
        CASE WHEN r.userID IS NULL THEN 0 ELSE 1 END AS isRegistered
        FROM Event e
        LEFT JOIN Registration r ON e.eventID = r.eventID AND r.userID = ?
    `;
    connection.query(query, [userID], (err, results) => {
        if (err) {
            console.error('Error fetching all events:', err);
            res.status(500).send('Ошибка при получении всех мероприятий.');
            return;
        }
        res.json(results);
    });
});


app.post('/api/registerevent', (req, res) => {
    const { eventID } = req.body;
    const session = req.session;
    connection.query(
        'INSERT INTO Registration (eventID, userID) VALUES (?, ?)',
        [eventID, session.userID],
        (err, results) => {
            if (err) {
                console.error('Error registering for event:', err);
                res.status(500).send('Ошибка при регистрации на мероприятие.');
                return;
            }
            sendQR(req.session.userEmail, session.userID, eventID);
            res.send('Регистрация успешна.');
        }
    );
});

app.post('/deleteevent', (req, res) => {
    const { eventID } = req.body;

    connection.query(
        'DELETE FROM Registration WHERE eventID = ?',
        [eventID],
        (err, results) => {
            if (err) {
                console.error('Error deleting registrations:', err);
                res.status(500).send('Ошибка при удалении регистраций.');
                return;
            }

            connection.query(
                'DELETE FROM Event WHERE eventID = ?',
                [eventID],
                (err, results) => {
                    if (err) {
                        console.error('Error deleting event:', err);
                        res.status(500).send('Ошибка при удалении мероприятия.');
                        return;
                    }
                    res.send('Мероприятие успешно удалено.');
                }
            );
        }
    );
});

app.get('/api/eventParticipants', (req, res) => {
    const { eventID } = req.query;
    connection.query(
        `SELECT u.name, u.surname, u.userEmail
         FROM Registration r
         JOIN Users u ON r.userID = u.userID
         WHERE r.eventID = ?`,
        [eventID],
        (err, results) => {
            if (err) {
                console.error('Error fetching participants:', err);
                res.status(500).send('Ошибка при получении списка участников.');
                return;
            }
            res.json(results);
        }
    );
});


app.listen(3000, () => {
    console.log('Server is running on http://localhost:3000');
});
