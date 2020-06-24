let account = {};

fetch('/api/')
.then( data => data.json())
.then( data => {
    // console.log(data);
    account.isLogin = (data.code === 200 && toString(data.data) !== '{}');
} )

