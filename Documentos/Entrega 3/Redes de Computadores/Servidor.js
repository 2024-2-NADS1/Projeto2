const express = require('express');
const app = express();
const port = 3000;

app.use(express.json());

app.post('/api/dados', (req, res) => {
    console.log(req.body);
    res.sendStatus(200);
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
});
