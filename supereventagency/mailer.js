const nodemailer = require('nodemailer');
const qrcode = require('qrcode');

// Настройки для вашего почтового аккаунта mail.ru
const transporter = nodemailer.createTransport({
    host: 'smtp.mail.ru',
    port: 465,
    secure: true, 
    auth: {
        user: 'supereventagency@mail.ru', 
        pass: 'wGakZpqEvaugdT9gHUZt'   
    }
});

function sendEmail(userEmail, Code) {
    const mailOptions = {
        from: 'supereventagency@mail.ru',
        to: userEmail,
        subject: 'Подтверждение входа.',
        text: `Ваш код подтверждения: ${Code}`
    };

    return transporter.sendMail(mailOptions);
}

async function sendQR(userEmail, userID, eventID) {
    const qrCodeData = `userID: ${userID}, eventID: ${eventID}`;
    try {
        const qrCode = await qrcode.toDataURL(qrCodeData);

        const mailOptions = {
            from: 'supereventagency@mail.ru',
            to: userEmail,
            subject: 'Ваш QR-код для мероприятия',
            text: 'Спасибо за регистрацию на мероприятие! Ваш QR-код для входа:',
            attachments: [{
                filename: 'qrcode.png',
                content: qrCode.split("base64,")[1],
                encoding: 'base64'
            }]
        };

        return transporter.sendMail(mailOptions);
    } catch (error) {
        console.error('Error generating or sending QR code:', error);
        throw error;
    }
}

module.exports = {
    sendEmail,
    sendQR
};