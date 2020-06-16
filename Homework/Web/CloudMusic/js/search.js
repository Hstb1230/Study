function showContainer(obj) {
    let child = $('.search-container').children;
    for (let i = 0; i < child.length; i++) 
        child[i].style.display = 'none';
    obj.style.display = 'block';
}

function getSearchHotKey()
{
    fetch(`${domain}/search/hot`, {
        method: 'get',
        mode: 'cors'
    })
    .then((data) => {
        return data.json();
    })
    .then((data) => {
        return data.result.hots;
    })
    .then((data) => {
        let hotKeyView = $('.search-hot-key');
        data.forEach(k => {
            let span = document.createElement('span');
            span.innerText = k.first;
            span.setAttribute('onclick', `searchTo('${k.first}')`);
            hotKeyView.appendChild(span);
        });
    })
}

function updateSearchHistory()
{
    let history = JSON.parse(localStorage.getItem('searchHistory')) || [];
    let view = $('.search-default > .search-list');
    while (view.children.length > 0) {
        view.removeChild(view.children[0]);
    }
    history.forEach(elem => {
        let li = document.createElement('li');
        view.appendChild(li);
        let i = document.createElement('i');
        i.setAttribute('class', 'icon-clock');
        li.appendChild(i);
        let div = document.createElement('div');
        div.setAttribute('class', 'search-list-item');
        li.appendChild(div);
        let p = document.createElement('p');
        p.innerText = elem;
        p.setAttribute('onclick', `searchTo('${elem}')`);
        div.appendChild(p);
        let span = document.createElement('span');
        span.innerText = '×';
        span.setAttribute('onclick', `deleteSearchHistory('${elem}')`);
        div.appendChild(span);
    });
}

function newSearchHistory(searchKey)
{
    let history = JSON.parse(localStorage.getItem('searchHistory')) || [];
    for(i = 0; i < history.length; i++)
    {
        if(history[i] == searchKey)
            history.splice(i, 1);
    }
    history.unshift(searchKey);
    localStorage.setItem('searchHistory', JSON.stringify(history));
    updateSearchHistory();
}

function deleteSearchHistory(searchKey)
{
    let history = JSON.parse(localStorage.getItem('searchHistory')) || [];
    for(i = 0; i < history.length; i++)
    {
        if(history[i] == searchKey)
            history.splice(i, 1);
    }
    localStorage.setItem('searchHistory', JSON.stringify(history));
    updateSearchHistory();
}

function highLightAll(str, key)
{
    // https://stackoverflow.com/questions/1144783/how-to-replace-all-occurrences-of-a-string
    // https://stackoverflow.com/questions/3598042/how-can-i-replace-a-regex-substring-match-in-javascript
    if(key.length === 0) return str;
    // 避免匹配到括号
    key = key[0].replace(/\(/g, '\\(').replace(/\)/g, '\\)');
    let rep = str.replace(new RegExp(`(${key})`, 'ig'), '<div class="text-highlight">$1</div>');
    // console.log(str, rep);
    return rep;
}

function getSearchSongList(searchKey) {
    return axios.get(`${domain}/search/`, {
        params: {
            keywords: searchKey,
            type: 1,
            strategy: 5
        }
    }); 
}

function getSearchMultiMatch(searchKey) {
    return axios.get(`${domain}/search/multimatch`, {
        params: {
            keywords: searchKey
        }
    }); 
}

function searchTo(searchKey)
{
    searchInput.value = searchKey;
    newSearchHistory(searchKey);
    axios.all( [ getSearchMultiMatch(searchKey), getSearchSongList(searchKey) ] )
    .then(axios.spread(
        ( multiMatch, songList ) => {
            songList = songList.data.result;
            let highLightWord = songList.highlights || [searchKey];

            let view = $('.search-result');
            while (view.children.length > 0) {
                view.removeChild(view.children[0]);
            }
            console.log(multiMatch.data.result);
            if(Object.keys(multiMatch.data.result).length != 0)
            {
                // 多重匹配
                multiMatch = multiMatch.data.result;
                let h3 = document.createElement('h3');
                h3.innerText = '最佳匹配';
                view.appendChild(h3);
                // 输出具体匹配
                multiMatch.orders.forEach(m => {
                    if(m == 'video') return;
                    console.log(m, multiMatch[m]);
                    if(m == 'mv')
                    {
                        let link = document.createElement('a');
                        link.href = `./mv.html?id=${multiMatch[m][0].id}`;
                        view.appendChild(link);
                        let mvView = document.createElement('div');
                        mvView.setAttribute('class', 'item-cover');
                        link.appendChild(mvView);
                        let coverImgView = document.createElement('div');
                        coverImgView.setAttribute('class', 'cover-img mv');
                        mvView.appendChild(coverImgView);
                        let img = document.createElement('img');
                        img.src = multiMatch[m][0].cover;
                        coverImgView.appendChild(img);
                        let infoView = document.createElement('div');
                        infoView.setAttribute('class', 'info')
                        mvView.appendChild(infoView);
                        let h3 = document.createElement('h3');
                        h3.innerHTML = `MV：${highLightAll(multiMatch[m][0].name, highLightWord)}`;
                        infoView.appendChild(h3);
                        let p = document.createElement('p');
                        multiMatch[m][0].artists.forEach(artist => {
                            if(p.innerText.length > 0)
                                p.innerText += ' / ';
                            p.innerText += artist.name;
                        });
                        p.innerText = highLightAll(p.innerText, highLightWord)
                        infoView.appendChild(p);
                        let iconEnter = document.createElement('i');
                        iconEnter.setAttribute('class', 'icon-enter');
                        mvView.appendChild(iconEnter);
                    }
                    else if(m == 'artist')
                    {
                        let mvView = document.createElement('div');
                        mvView.setAttribute('class', 'item-cover');
                        view.appendChild(mvView);
                        let coverImgView = document.createElement('div');
                        coverImgView.setAttribute('class', 'cover-img artist');
                        mvView.appendChild(coverImgView);
                        let img = document.createElement('img');
                        img.src = `${multiMatch[m][0].img1v1Url}`;
                        coverImgView.appendChild(img);
                        let infoView = document.createElement('div');
                        infoView.setAttribute('class', 'info')
                        mvView.appendChild(infoView);
                        let h3 = document.createElement('h3');
                        h3.innerHTML = `歌手：${highLightAll(multiMatch[m][0].name, highLightWord)}`;
                        if(multiMatch[m][0].alias.length > 0)
                            h3.innerHTML += `（${highLightAll(multiMatch[m][0].alias[0], highLightWord)}）`;
                        infoView.appendChild(h3);
                        let iconEnter = document.createElement('i');
                        iconEnter.setAttribute('class', 'icon-enter');
                        mvView.appendChild(iconEnter);
                    }
                    else if(m == 'album')
                    {
                        let mvView = document.createElement('div');
                        mvView.setAttribute('class', 'item-cover');
                        view.appendChild(mvView);
                        let coverImgView = document.createElement('div');
                        coverImgView.setAttribute('class', 'cover-img album');
                        mvView.appendChild(coverImgView);
                        let img = document.createElement('img');
                        img.src = `${multiMatch[m][0].blurPicUrl}`;
                        coverImgView.appendChild(img);
                        let infoView = document.createElement('div');
                        infoView.setAttribute('class', 'info')
                        mvView.appendChild(infoView);
                        let h3 = document.createElement('h3');
                        h3.innerHTML = `专辑：${highLightAll(multiMatch[m][0].name, highLightWord)}`;
                        if(multiMatch[m][0].alias.length > 0)
                            h3.innerHTML += `（${highLightAll(multiMatch[m][0].alias[0], highLightWord)}）`;
                        infoView.appendChild(h3);
                        let iconEnter = document.createElement('i');
                        iconEnter.setAttribute('class', 'icon-enter');
                        mvView.appendChild(iconEnter);
                    }
                });

            }
            console.log(songList.songs.slice(0, 3));
            if(songList.songCount == 0)
            {
                let div = document.createElement('div');
                div.innerText = '暂无搜索结果';
                div.setAttribute('class', 'no-result');
                view.appendChild(div);
            }
            else
            {

                let div = document.createElement('div');
                // div.setAttribute('class', 'new-song');
                div.setAttribute('class', 'song-list search');
                view.appendChild(div);
                let newSongGroup = document.createElement('ul');
                div.appendChild(newSongGroup);
                let list = '';
                songList.songs.forEach(song => {
                    // 副标题
                    let subtitle = '';
                    let alia = song.alia || song.alias;
                    if(alia.length > 0)
                        subtitle = `(${highLightAll(alia[0], highLightWord)})`;
                    
                    // 音质
                    let sqVersion = ''
                    let privilege = song.privilege || null;
                    if(privilege === null || privilege.maxbr === 999000)
                        sqVersion = '<span class="sq-icon"></span>';
                    // 歌手
                    let singer = '';
                    let artist = song.ar || song.artists;
                    artist.forEach(ar => {
                        if(singer !== "")
                            singer += " / ";
                        singer += highLightAll(ar.name, highLightWord);
                    });

                    let album = song.al || song.album;
                    
                    // 复用song-list
                    list += `
                        <a href="./play.html?id=${song.id}">
                            <li>
                                <div class="song-info">
                                    <div class="song-name">
                                        ${highLightAll(song.name, highLightWord)}
                                        ${subtitle}
                                    </div>
                                    <span>
                                        ${sqVersion}
                                        ${singer}
                                        - 
                                        ${highLightAll(album.name, highLightWord)}
                                    </span>
                                </div>
                                <span class="play-icon"></span>
                            </li>
                        </a>
                    `;

                    return;
                    /*
                    // DOM
                    // 原样式已删除
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

                    let alia = song.alia || song.alias;
                    if(alia.length > 0)
                    {
                        songSubtitleDiv = document.createElement('div');
                        songSubtitleDiv.className = 'song-subtitle';
                        songTitleContainer.appendChild(songSubtitleDiv);
            
                        songSubtitle = document.createElement('p');
                        songSubtitle.innerText = `(${alia[0]})`;
                        songSubtitleDiv.appendChild(songSubtitle);
                    }
            
                    songSingerDiv = document.createElement('div');
                    songSingerDiv.className = 'singer';

                    let artist = song.ar || song.artists;
                    artist.forEach(ar => {
                        if(songSingerDiv.innerText != "")
                            songSingerDiv.innerText += " / ";
                        songSingerDiv.innerText += ar.name;
                    });

                    let album = song.al || song.album;
                    if(album !== '')
                        songSingerDiv.innerText += ` - ${album.name}`;
                    li.appendChild(songSingerDiv);

                    let privilege = song.privilege || null;
                    if(privilege === null || privilege.maxbr === 999000)
                    {
                        songSingerDiv.innerHTML = '<span class="sq-icon"></span>' + songSingerDiv.innerHTML ;
                    }

                    // console.log(a);
                    newSongGroup.appendChild(a);
                    */
                });
                console.log(list);
                if(list !== '')
                    newSongGroup.innerHTML = list;
                if(songList.songs[0].privilege === undefined)
                {
                    let note = document.createElement('div');
                    note.setAttribute('class', 'note');
                    note.innerHTML = `
                        待高亮文本、音质数据不准确，
                        <br>
                        可修改"NeteaseCloudMusicApi\\module\\search.js"：
                        <br>
                        增加请求参数「 strategy: query.strategy || 0 」并重新运行API
                    `;
                    view.insertBefore(note, view.childNodes[0]);
                }
            }
        }
    ))
    showContainer(searchResult);
}

function clearSearchInput()
{
    searchInput.value = '';
    showContainer(searchDefault);
}

function getSearchRecommand()
{
    fetch(`${domain}/search/suggest?keywords=${searchInput.value}&type=mobile`, {
        method: 'get',
        mode: 'cors'
    })
    .then(data => {
        return data.json();
    })
    .then(data => {
        return data.result.allMatch;
    })
    .then(data => {
        let view = $('.search-recommand');
        while (view.children.length > 0) {
            view.removeChild(view.children[0]);
        }
        let h3 = document.createElement('h3');
        h3.innerText = `搜索“${searchInput.value}”`;
        h3.setAttribute('onclick', `searchTo('${searchInput.value}')`);
        view.appendChild(h3);
        let ul = document.createElement('ul');
        ul.setAttribute('class', 'search-list');
        view.appendChild(ul);
        data = data || [];
        data.forEach(elem => {
            let li = document.createElement('li');
            ul.appendChild(li);
            let i = document.createElement('i');
            i.setAttribute('class', 'icon-search');
            li.appendChild(i);
            let div = document.createElement('div');
            div.setAttribute('class', 'search-list-item');
            li.appendChild(div);
            let p = document.createElement('p');
            p.innerText = elem.keyword;
            p.setAttribute('onclick', `searchTo('${elem.keyword}')`);
            div.appendChild(p);
        });
    })
}

let searchInput = $('.search-bar > input[type="text"]');
let searchDefault = $('.search-container > .search-default');
let searchRecommand = $('.search-container > .search-recommand');
let searchResult = $('.search-container > .search-result');

searchInput.onfocus = () => {
    if(searchInput.value.length > 0)
    {
        showContainer(searchRecommand);
        getSearchRecommand();
    }
    searchInput.onkeyup = (e) => {
        if(searchInput.value.length == 0)
        {
            showContainer(searchDefault);
        } 
        else if(e.keyCode == 13) // 回车
        {
            searchTo(searchInput.value);
        }
        else if(searchInput.value.length > 0)
        {
            showContainer(searchRecommand);
            getSearchRecommand();
        }
    }
}

getSearchHotKey();

updateSearchHistory();
