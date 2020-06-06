const domain = 'http://localhost:3000';

fetch(`${domain}/personalized`, {
    method: 'GET',
    mode: 'cors',
})
.then( data => data.json() )
.then( data => {
    recArr = data.result.slice(0, 6)
    recGroup = document.querySelector('.rec-song > ul')
    recArr.forEach(elem => {
        li = document.createElement('li');
        recGroup.appendChild(li);
        a = document.createElement('a');
        a.href = `./recSongDetail.html?id=${elem.id}`;
        li.appendChild(a);
        // setImgArea
        div = document.createElement('div');
        div.className = 'rec-img';
        a.appendChild(div);
        // setTilte
        p = document.createElement('p');
        p.innerText = elem.name;
        a.appendChild(p);
        // setImg
        img = document.createElement('img');
        img.src = elem.picUrl;
        div.appendChild(img);
        // setPlayNumber
        span = document.createElement('span');
        span.className = 'play-number';
        if(elem.playCount > 1e8)
            span.innerText = `${Math.floor(elem.playCount / 1e8 * 10) / 10}亿`;
        else if(elem.playCount > 1e4)
            span.innerText = `${Math.floor(elem.playCount / 1e4 * 10) / 10}万`;
        div.appendChild(span);
        
    })
})