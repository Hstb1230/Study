const domain = 'http://localhost:3000';

document.querySelector('html').style.height = '100%';

// 捕获ID
let query = location.search.slice(1).split('&');
let id = null;
query.forEach(element => {
    param = element.split('=');
    if(param[0] === 'id')
    {
        id = param[1];
        return;
    }
});

// 空请求，跳转首页
if(id === null || id.length == 0)
{
    window.location.href= '.';
}

// 获取歌曲信息
function getSongInfo()
{
    return axios.get(`${domain}/song/detail`, {
        params: {
            ids: id
        }
    });
}

// 获取资源
function getSongResource()
{
    return axios.get(`${domain}/song/url`, {
        params: {
            id: id
        }
    });
}

// 获取歌词
function getSongLyric() 
{
    return axios.get(`${domain}/lyric`, {
        params: {
            id: id
        }
    });
}

// 解析
axios.all( [ getSongInfo(), getSongResource(), getSongLyric() ] )
.then( axios.spread(
    ( info, resource, lyric ) => {
        // Both requests are now complete

        // console.log(info);

        albumImg = info.data.songs[0].al.picUrl;
        albumImgView = document.querySelector('.disc > .album > img');
        albumImgView.src = albumImg;

        backgroundImgView = document.querySelector('.background-blur img');
        backgroundImgView.src = albumImg;

        songNameView = document.querySelector('.song-title > .song-name');
        songNameView.innerText = info.data.songs[0].name;
        if(info.data.songs[0].tns != undefined)
        {
            songNameView.innerText += `（${info.data.songs[0].tns[0]}）`;
        }

        singerView = document.querySelector('.song-title > .singer');
        info.data.songs[0].ar.forEach(
            singer => {
                singerView.innerText += ` / ${singer.name}`;
            }
        );
        singerView.innerText = singerView.innerText.slice(2);

        document.title = document.querySelector('.song-title').innerText;

        // console.log(resource);
        audioView = document.querySelector('.disc-container > audio');
        audioView.src = resource.data.data[0].url;
        audioView.load();

        playBtn = document.querySelector('.play-btn');

        rangeBarView = document.querySelector('.range-container > input[type=range]');

        // console.log(lyric);
        lyricView = document.querySelector('.lyric');
        lyricScrollView = document.querySelector('.lyric-scroll');

        // 歌词组合
        let lyricMap = new Map();

        // 原版
        const oLyric = lyric.data.lrc.lyric;
        let oLyricRegexp = /((\[\d+:\d+.\d+\]){1,})([^\[\n]+)/g;
        let oLyricMatch = oLyricRegexp.exec(oLyric);
        do
        {
            oLyricMatch[1].match(/(\[\d+:\d+.\d+\])/g).forEach(time => {
                lyricMap.set(time, oLyricMatch[3]);
            });
        } while((oLyricMatch = oLyricRegexp.exec(oLyric)) !== null);

        // 翻译
        const tLyric = lyric.data.tlyric.lyric;
        if(tLyric !== null)
        {
            let tLyricRegexp = /((\[\d+:\d+.\d+\]){1,})([^\[\n]+)/g;
            let tLyricMatch = tLyricRegexp.exec(tLyric);
            do
            {
                tLyricMatch[1].match(/(\[\d+:\d+.\d+\])/g).forEach(time => {
                    lyricMap.set(time, lyricMap.get(time) + '<br>' + tLyricMatch[3]);
                });
            } while((tLyricMatch = tLyricRegexp.exec(tLyric)) !== null);
        }

        let lyricListString = '';

        for(let [key, value] of lyricMap) 
        {
            lyricListString += key + value
            lyricListString += '\n';
        }
        // console.log(lyricListString);

        let lyricPlay = new window.Lyric(
            lyricListString,
            (obj) => {
                console.log(
                    obj,
                    lyricView.offsetTop, 
                    lyricView.childNodes[obj.lineNum].offsetTop
                );
                if(obj.lineNum > 0)
                    lyricView.childNodes[obj.lineNum - 1].removeAttribute('style');
                lyricView.childNodes[obj.lineNum].style.color = 'white';
                if(obj.lineNum >= 3)
                {
                    // lyricView.childNodes[obj.lineNum - 3].classList.add('hide');
                    // lyricView.childNodes[obj.lineNum - 3].classList.add('hide-remove');
                    lyricView.style.transform = `translateY(${(lyricView.childNodes[0].offsetTop - lyricView.childNodes[obj.lineNum - 2].offsetTop)}px)`;
                }
                else
                {
                    lyricView.removeAttribute('style');
                }
            }
        );

        lyricPlay.lines.forEach(obj => {
            // console.log(obj);
            p = document.createElement('p');
            p.innerHTML = obj.txt;
            lyricView.appendChild(p);
        });

        tryPlay = () => {
            if(audioView.paused)
            {
                playBtn.style.opacity = '0';
                audioView.play();
                discView.classList.replace('paused', 'playing');
                lyricPlay.togglePlay();
            }
            else 
            {
                playBtn.removeAttribute('style');
                audioView.pause();
                discView.classList.replace('playing', 'paused');
                lyricPlay.togglePlay();
            }
        }

        discView = document.querySelector('.disc');

        audioView.addEventListener('loadedmetadata', () => {
            rangeBarView.max = audioView.duration;
            discView.addEventListener('click', tryPlay);
            audioView.ontimeupdate = () => {
                rangeBarView.value = audioView.currentTime;
            }
            rangeBarView.onchange = () => {
                audioView.currentTime = rangeBarView.value;
                lyricView.childNodes.forEach(element => {
                    element.removeAttribute('style');
                });
                lyricPlay.seek(audioView.currentTime * 1000);
                if(audioView.paused)
                {
                    lyricPlay.togglePlay();
                    // audioView.play();
                    // discView.classList.replace('paused', 'playing');
                }
            }
        });

        audioView.addEventListener('ended', () => { 
            discView.classList.replace('playing', 'paused'); 
        });
    }
));