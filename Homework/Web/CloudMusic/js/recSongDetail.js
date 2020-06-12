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
    (detail, comment) => {
        console.log(detail);
        console.log(comment);

        let coverImg = document.querySelector('.cover-img > img');
        let bgImg = document.querySelector('.bg-blur > img');
        let playCount = document.querySelector('.cover-img > .play-number');
        // 替换封面
        bgImg.src = coverImg.src = detail.data.playlist.coverImgUrl;
        // 替换播放数据
        if(detail.data.playlist.playCount > 1e8)
            playCount.innerHTML = `${Math.floor(detail.data.playlist.playCount / 1e8 * 10) / 10}亿`;
        else if(detail.data.playlist.playCount > 1e4)
            playCount.innerHTML = `${Math.floor(detail.data.playlist.playCount / 1e4 * 10) / 10}万`;
        else
            playCount.innerHTML = detail.data.playlist.playCount;
        
        let title = document.querySelector('.title > h3');
        let authorName = document.querySelector('.author > p');
        let authorAvatar = document.querySelector('.author > .avatar > img');
        // 歌单标题
        document.title = detail.data.playlist.name;
        title.innerText = detail.data.playlist.name;
        // 歌单作者的昵称和头像
        authorName.innerText = detail.data.playlist.creator.nickname;
        authorAvatar.src = detail.data.playlist.creator.avatarUrl;
        // 作者类型
        // console.log(detail.data.playlist.creator);
        if(detail.data.playlist.creator.accountStatus === 0)
        {
            // 账户状态正常
            let createType = $('.author > .avatar > span');
            switch (detail.data.playlist.creator.userType) {
                // 音乐达人
                case 200:
                    createType.setAttribute('class', 'star');
                    break;
                // 音乐人
                case 4:
                    createType.setAttribute('class', 'musician');
                    break;
            
                default:
                    createType.removeAttribute('class');
                    break;
            }
        }
        // 设置标签
        let tag = $('.intro_title');
        detail.data.playlist.tags.forEach(t => {
            span = $make('span');
            span.innerText = t;
            tag.append(span);
        });

        // 设置介绍
        let intro_content = $('.intro_content');
        (detail.data.playlist.description.split('\n')).forEach(s => {
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
            $('#intro_expand').checked = true;
            $('#intro_expand').disabled = true;
            $('.intro_content > icon').style.display = 'none';
        }
    }
) )