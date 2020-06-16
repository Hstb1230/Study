fetch(`${domain}/personalized/newsong`, {
    method: 'GET',
    mode: 'cors',
})
.then((data) => {
    // console.log(data)
    return data.json()
})
.then((data) => {
    recArr = data.result.slice(0, 10)
    // newSongGroup = document.querySelector('.new-song > ul');
    newSongGroup = $('.song-list.new > ul');
    let songList = '';
    recArr.forEach(elem => {
        song = elem.song;
        // console.log(song);

        /*
        // DOM
        a = document.createElement('a');
        a.href = `play.html?id=${song.id}`;
        li = document.createElement('li');
        a.appendChild(li);

        playIcon = document.createElement('div');
        playIcon.className = 'play-icon';
        li.appendChild(playIcon);

        songTitleContainer = document.createElement('div');
        songTitleContainer.className = 'song-title-container';
        li.appendChild(songTitleContainer);

        songTitleDiv = document.createElement('div');
        songTitleDiv.className = 'song-title';
        songTitleDiv.innerText = song.name;
        songTitleContainer.appendChild(songTitleDiv);

        // songTitle = document.createElement('p');
        // songTitle.innerText = song.name;
        // songTitleDiv.appendChild(songTitle);

        if(song.alias.length > 0)
        {
            songSubtitleDiv = document.createElement('div');
            songSubtitleDiv.className = 'song-subtitle';
            songTitleContainer.appendChild(songSubtitleDiv);

            songSubtitle = document.createElement('p');
            songSubtitle.innerText = `(${song.alias[0]})`;
            songSubtitleDiv.appendChild(songSubtitle);
        }

        songSingerDiv = document.createElement('div');
        songSingerDiv.className = 'singer';


        song.artists.forEach(singer => {
            if(songSingerDiv.innerText != "")
                songSingerDiv.innerText += " / ";
            songSingerDiv.innerText += singer.name;
        });
        songSingerDiv.innerText += ` - ${song.album.name}`;
        li.appendChild(songSingerDiv);

        if(song.privilege.maxbr == 999000)
        {
            songSingerDiv.innerHTML = '<span class="sq-icon"></span>' + songSingerDiv.innerHTML ;
        }

        newSongGroup.appendChild(a);
        return;
        */
        
        let singer = '';
        song.artists.forEach( ar => {
            singer += ` / ${ar.name}`;
        });
        singer = singer.slice(3);

        let subtitle = '';
        if(song.alias.length > 0)
            subtitle = `<span class="subtitle">(${song.alias[0]})</span>`;

        let sqVersion = '';
        if(song.privilege.maxbr == 999000)
            sqVersion = '<span class="sq-icon"></span>';

        songList += `
        <a href="./play.html?id=${song.id}">
            <li>
                <div class="song-info">
                    <p class="song-name">
                        ${song.name}
                        ${subtitle}
                    </p>
                    <span>
                        ${sqVersion}
                        ${singer}
                         - 
                        ${song.album.name}
                    </span>
                </div>
                <span class="play-icon"></span>
            </li>
        </a>
        `;
    })
    if(songList !== '')
        newSongGroup.innerHTML = songList;
})