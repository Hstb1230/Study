function showContainer(obj) {
    let child = document.querySelector('.search-container').children;
    for (let i = 0; i < child.length; i++) {
        child[i].style.display = 'none';
    }
    obj.style.display = 'block';
}

function getSearchHotKey()
{
    fetch("http://localhost:3000/search/hot", {
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
        let hotKeyView = document.querySelector('.search-hot-key');
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
    let view = document.querySelector('.search-default > .search-list');
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

function getSearchSongList(searchKey) {
    return axios.get(`http://localhost:3000/search/`, {
        params: {
            keywords: searchKey,
            type: 1,
            strategy: 5
        }
    }); 
}

function getSearchMultiMatch(searchKey) {
    return axios.get(`http://localhost:3000/search/multimatch`, {
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
            let view = document.querySelector('.search-result');
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
                        let mvView = document.createElement('div');
                        mvView.setAttribute('class', 'item-cover');
                        view.appendChild(mvView);
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
                        h3.innerText = `MV：${multiMatch[m][0].name}`;
                        infoView.appendChild(h3);
                        let p = document.createElement('p');
                        multiMatch[m][0].artists.forEach(artist => {
                            if(p.innerText.length > 0)
                                p.innerText += ' / ';
                            p.innerText += artist.name;
                        });
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
                        h3.innerText = `歌手：${multiMatch[m][0].name}`;
                        if(multiMatch[m][0].alias.length > 0)
                            h3.innerText += `（${multiMatch[m][0].alias[0]}）`;
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
                        h3.innerText = `专辑：${multiMatch[m][0].name}`;
                        if(multiMatch[m][0].alias.length > 0)
                            h3.innerText += `（${multiMatch[m][0].alias[0]}）`;
                        infoView.appendChild(h3);
                        let iconEnter = document.createElement('i');
                        iconEnter.setAttribute('class', 'icon-enter');
                        mvView.appendChild(iconEnter);
                    }
                });

            }
            songList = songList.data.result;
            console.log(songList);
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
                div.setAttribute('class', 'new-song');
                view.appendChild(div);
                let newSongGroup = document.createElement('ul');
                div.appendChild(newSongGroup);
                songList.songs.forEach(song => {
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
            
                    if(song.alia.length > 0)
                    {
                        songSubtitleDiv = document.createElement('div');
                        songSubtitleDiv.className = 'song-subtitle';
                        songTitleContainer.appendChild(songSubtitleDiv);
            
                        songSubtitle = document.createElement('p');
                        songSubtitle.innerText = `(${song.alia[0]})`;
                        songSubtitleDiv.appendChild(songSubtitle);
                    }
            
                    songSingerDiv = document.createElement('div');
                    songSingerDiv.className = 'singer';
            
            
                    song.ar.forEach(singer => {
                        if(songSingerDiv.innerText != "")
                            songSingerDiv.innerText += " / ";
                        songSingerDiv.innerText += singer.name;
                    });
                    songSingerDiv.innerText += ` - ${song.al.name}`;
                    li.appendChild(songSingerDiv);
            
                    if(song.privilege.maxbr == 999000)
                    {
                        songSingerDiv.innerHTML = '<span class="sq-icon"></span> ' + songSingerDiv.innerHTML ;
                    }

                    // console.log(a);
                    newSongGroup.appendChild(a);
                });
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
    fetch(`http://localhost:3000/search/suggest?keywords=${searchInput.value}&type=mobile`, {
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
        let view = document.querySelector('.search-recommand');
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

let searchInput = document.querySelector('.search-bar > input[type="text"]');
let searchDefault = document.querySelector('.search-container > .search-default');
let searchRecommand = document.querySelector('.search-container > .search-recommand');
let searchResult = document.querySelector('.search-container > .search-result');

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