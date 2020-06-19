let http = require('http');
let fs = require('fs');
let art = require('art-template');
let urlParse = require('url');
const { url } = require('inspector');

let info = [
    {
        name: '周',
        question: '111'
    },
    {
        name: '接',
        question: '222'
    },
    {
        name: '轮',
        question: '333'
    },
]

let server = http.createServer( (req, res) => {
    let url = urlParse.parse(req.url, true);
    if(req.url === '/')
    {
        fs.readFile('./view/index.html', (error, data) => {
            let htmlStr = art.render(data.toString(), {
                message: info
            });
            res.end(htmlStr);
        });
    }
    else if(req.url === '/bootstrap.css')
    {
        fs.readFile('./view/bootstrap.css', (error, data) => {
            res.end(data);
        });
    }
    else if(req.url === '/post')
    {
        fs.readFile('./view/post.html', (error, data) => {
            res.end(data);
        });
    }
    else if(url.pathname === '/comment')
    {
        // console.log(url);
        info.unshift(url.query);
        res.statusCode = 303;
        res.setHeader('Location', '/');
        res.end();
    }
} )

server.listen(80, () => {
    console.log('success');
})
