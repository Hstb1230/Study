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

const domain = 'http://localhost:3000';

function getPlaylistDetail()
{
    return axios.get(`${domain}/playlist/detail?id=${id}`)
}

function getPlaylistComment()
{
    return axios.get(`${domain}/comment/playlist?id=${id}`)
}

function $(e) {
    return document.querySelector(e);
}

function $make(e) {
    return document.createElement(e);
}

axios.all( [ getPlaylistDetail(), getPlaylistComment() ] )
.then( axios.spread(
    (deatil, comment) => {
        console.log(deatil);
        console.log(comment);

        let coverImg = document.querySelector('.cover-img > img');
        let bgImg = document.querySelector('.bg-blur > img');
        let playCount = document.querySelector('.cover-img > .play-number');
        // 替换封面
        bgImg.src = coverImg.src = deatil.data.playlist.coverImgUrl;
        // 替换播放数据
        if(deatil.data.playlist.playCount > 1e8)
            playCount.innerHTML = `${Math.floor(deatil.data.playlist.playCount / 1e8 * 10) / 10}亿`;
        else if(deatil.data.playlist.playCount > 1e4)
            playCount.innerHTML = `${Math.floor(deatil.data.playlist.playCount / 1e4 * 10) / 10}万`;
        else
            playCount.innerHTML = deatil.data.playlist.playCount;
        
        let title = document.querySelector('.title > h3');
        let authorName = document.querySelector('.author > p');
        let authorAvatar = document.querySelector('.author > .avatar > img');
        // 歌单标题
        document.title = deatil.data.playlist.name;
        title.innerText = deatil.data.playlist.name;
        // 歌单作者的昵称和头像
        authorName.innerText = deatil.data.playlist.creator.nickname;
        authorAvatar.src = deatil.data.playlist.creator.avatarUrl;

        // 设置标签
        let tag = $('.intro_title');
        deatil.data.playlist.tags.forEach(t => {
            span = $make('span');
            span.innerText = t;
            tag.append(span);
        });

        // 设置介绍
        let intro_content = $('.intro_content');
        (deatil.data.playlist.description.split('\n')).forEach(s => {
            span = $make('span');
            if(s.length == 0)
                s = '&nbsp;';
            span.innerHTML = s;
            intro_content.append(span);
        });
        if(intro_content.children.length > 5)
        {
            span = $make('span');
            span.innerText = '...';
            intro_content.insertBefore(span, $('.intro_content > span:nth-child(5)'));
        }
        else
        {
            $('.intro_content > icon').style.display = 'none';
        }
    }
) )