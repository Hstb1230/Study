
fetch(`${domain}/top/list?idx=1`, {
    mode: 'cors',
    method: 'get'
})
.then( data => data.json() )
.then( data => {
    console.log(data);
    // console.log(data.privileges.slice(0, 20));
    // 更新日期
    $('.hsh-content > .update > span').innerText = timestampToDate(data.playlist.updateTime);

    // 歌曲列表
    let songList = '';
    (data.playlist.tracks.slice(0, 20)).forEach( (song, index) => {
        // console.log(song);
        let singer = '';
        song.ar.forEach( ar => {
            singer += ` / ${ar.name}`;
        });
        singer = singer.slice(3);
        let sqVersion = '';
        if(data.privileges[index].playMaxbr === 999000)
            sqVersion = '<span class="sq-icon"></span>';
        songList += `
        <a href="./play.html?id=${song.id}">
            <li>
                <div class="rank">
                    ${(index < 9 ? '0' : '') + (index + 1)}
                </div>
                <div class="song-info">
                    <p class="song-name">
                        ${song.name}
                    </p>
                    <span>
                        ${sqVersion}
                        ${singer}
                         - 
                        ${song.al.name}
                    </span>
                </div>
                <span class="play-icon"></span>
            </li>
        </a>
        `;
    } );;
    $('.song-list.hot > ul').innerHTML = songList;
} )
