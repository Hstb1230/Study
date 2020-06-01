const domain = 'http://localhost:3000';

fetch(`${domain}/personalized`, {
    method: 'GET',
    mode: 'cors',
})
.then((data) => {
    // console.log(data)
    return data.json()
})
.then((data) => {
    recArr = data.result.slice(0, 6)
    recGroup = document.querySelector('.rec-song > ul')
    recArr.forEach(elem => {
        li = document.createElement('li');
        recGroup.appendChild(li);
        // setImgArea
        div = document.createElement('div');
        div.className = 'rec-img';
        li.appendChild(div);
        // setTilte
        p = document.createElement('p');
        p.innerText = elem.name;
        li.appendChild(p);
        // setImg
        img = document.createElement('img');
        img.src = elem.picUrl;
        div.appendChild(img);
        // setPlayNumber
        span = document.createElement('span');
        span.className = 'play-number';
        span.innerText = `${Math.ceil(elem.playCount / 10000)}万`;
        div.appendChild(span);
        
    })
})