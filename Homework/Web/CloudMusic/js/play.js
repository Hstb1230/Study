$('html').style.height = '100%';

const id = getParam('id');

// 空请求，跳转首页
if(id === null || id.length == 0)
{
    window.location.href= '.';
}

let audio = $('.disc-container > audio');
const makeAudioPause = () => {
    audio.volume = Math.max(0, Math.floor((audio.volume - 0.05) * 100) / 100);
    if(audio.volume <= 0)
    {
        audio.pause();
        discView.classList.replace('playing', 'paused');
    }
    else
        setTimeout(makeAudioPause, Math.floor(audio.volume * 100));
}

const makeAudioPlay = () => {
    audio.volume = Math.min(1, Math.floor((audio.volume + 0.04) * 100) / 100);
    if(audio.volume < 1)
        setTimeout(makeAudioPlay, Math.floor(audio.volume * 100));
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
        },
        withCredentials: true
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
        albumImgView = $('.disc > .album > img');
        albumImgView.src = albumImg;

        backgroundImgView = $('.background-blur img');
        backgroundImgView.src = albumImg;

        songNameView = $('.song-title > .song-name');
        songNameView.innerText = info.data.songs[0].name;
        if(info.data.songs[0].tns != undefined)
        {
            songNameView.innerText += `（${info.data.songs[0].tns[0]}）`;
        }

        singerView = $('.song-title > .singer');
        info.data.songs[0].ar.forEach(
            singer => {
                singerView.innerText += ` / ${singer.name}`;
            }
        );
        singerView.innerText = singerView.innerText.slice(2);

        document.title = $('.song-title').innerText;

        // console.log(resource);
        audioView = $('.disc-container > audio');
        // if(resource.data.data[0].url !== null)
            audioView.src = resource.data.data[0].url;
        audioView.load();

        playBtn = $('.play-btn');

        rangeBarView = $('.range-container > input[type=range]');

        // console.log(lyric);
        lyricView = $('.lyric');
        lyricScrollView = $('.lyric-scroll');

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
                discView.classList.replace('paused', 'playing');
                lyricPlay.togglePlay();
                audioView.play();
                setTimeout(makeAudioPlay, audioView.volume);
            }
            else 
            {
                let d = () => {
                    if(audioView.paused)
                    {
                        clearInterval(interval);
                        lyricPlay.togglePlay();
                        playBtn.style.opacity = '1';
                        playBtn.removeAttribute('style');
                    }
                };
                let interval = setInterval(d, 10);
                setTimeout(makeAudioPause, audioView.volume);
            }
        }

        discView = $('.disc');

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
            playBtn.style.opacity = '1';
            discView.classList.replace('playing', 'paused'); 
        });

        document.onkeydown = e => {
            if(e.code === 'Space')
            {
                tryPlay();
                e.preventDefault();
            }
        }
    }
));