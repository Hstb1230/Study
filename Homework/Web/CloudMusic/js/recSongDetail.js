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

function getLikeIcon() {
    return `
        <i><svg class="i-like" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 28 28"><path fill="#999" d="m25.857 14.752c-.015.059-1.506 5.867-2.932 8.813-1.162 2.402-3 2.436-3.099 2.436h-12.826v-13c3 0 5.728-4 5.728-7.275 0-3.725 1.433-3.725 2.142-3.725 1.327 0 1.978 1.345 1.978 4 0 2.872-.832 4.525-.839 4.537-.161.31-.155.682.027.981.181.299.5.482.849.482h6.942c.922 0 1.551.215 1.866.64.467.626.286 1.705.164 2.112m-23.857 10.248v-10c0-1.795.659-1.981.855-2h2.145v13h-2.173c-.829 0-.827-.648-.827-1m25.309-13.54c-.713-.969-1.886-1.46-3.482-1.46h-5.519c.26-.932.519-2.285.519-4 0-5.221-2.507-6-4-6-1.909 0-4.185.993-4.185 5.725 0 2.206-1.923 5.275-3.815 5.275h-4-.011c-1.034.011-2.816.862-2.816 4v10.02c0 1.198.675 2.979 2.827 2.979h16.971.035c.364 0 3.224-.113 4.894-3.564 1.514-3.127 3.01-8.942 3.056-9.14.071-.23.664-2.289-.474-3.836"></path></svg></i>
    `;
}

Date.prototype.getFullMonth = function() {
    if(this.getMonth() + 1 < 10)
        return `0${this.getMonth() + 1}`;
    return this.getMonth() + 1;
}

Date.prototype.getFullDate = function() {
    if(this.getDate() < 10)
        return `0${this.getDate()}`;
    return this.getDate();
}

Date.prototype.getFullHours = function() {
    if(this.getHours() < 10)
        return `0${this.getHours()}`;
    return this.getHours();
}

Date.prototype.getFullMinutes = function() {
    if(this.getMinutes() < 10)
        return `0${this.getMinutes()}`;
    return this.getMinutes();
}

function formatTime(timeStamp) {
    let fmt = '';

    let now = new Date();
    now.setHours(0);
    now.setMinutes(0);
    now.setSeconds(0);
    now.setMilliseconds(0);

    let t = new Date(timeStamp);
    if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60)
        fmt = '昨天';
    else if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60 * 2)
        fmt += '前天';
    else if(now.getFullYear() === t.getFullYear())
        return `${t.getFullMonth()}月${t.getFullDate()}日`;
    else if(now.getTime() / 1000 > Math.floor(timeStamp / 1000))
        return `${t.getFullYear()}年${t.getFullMonth()}月${t.getFullDate()}日`;
    fmt += `${t.getFullHours()}:${t.getFullMinutes()}`;
    
    return fmt;
}

function parseComment(comment)
{
    let view = '';
    comment.forEach(c => {
        let userType = '';
        switch(c.user.userType) {
            case 200:
                userType = 'star';
                break;
            case 4:
                userType = 'musician';
                break;
            default:
                break;
        }
        let reply = '';
        if(c.beReplied.length > 0)
        {
            reply = `
                <div class="reply">
                    <p>@${c.beReplied[0].user.nickname}：${c.beReplied[0].content}</p>
                </div>
            `;
        }
        view += `
            <li class="comment">
                <div class="avatar">
                    <img src="${c.user.avatarUrl}">
                    <span class="${userType}"></span>
                </div>
                <div class="multi">
                    <div class="head">
                        <div class="meta">
                            <div class="user">
                                <p>${c.user.nickname}</p>
                                ${ c.user.vipType == 11 ? '<div class="i-vip"></div>' : ''}
                            </div>
                            <span>${formatTime(c.time)}</span>
                        </div>
                        <div class="like">${c.likedCount || ''}${getLikeIcon()}</div>
                    </div>
                    <div class="content">
                        ${c.content}
                    </div>
                    ${reply}
                </div>
            </li>
        `;
    })
    return view;
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

        // 歌曲列表
        // 还是不操作DOM了
        let songList = '';
        detail.data.playlist.tracks.forEach((info, index) => {
            // console.log(info);
            let singer = '';
            info.ar.forEach( ar => {
                singer += ` / ${ar.name}`;
            });
            singer = singer.slice(3);
            songList += `
            <a href="./play.html?id=${info.id}">
                <li>
                    <div class="rank">
                        ${index + 1}
                    </div>
                    <div class="song-info">
                        <p>
                            ${info.name}
                        </p>
                        <span>
                            ${singer}
                             - 
                            ${info.al.name}
                        </span>
                    </div>
                    <span class="play-icon"></span>
                </li>
            </a>
            `;
        });
        $('.song-list > ul').innerHTML = songList;

        // 热门评论
        $('.hot-comment > ul').innerHTML = parseComment(comment.data.hotComments);

        // 最新评论
        $('.recent-comment > ul').innerHTML = parseComment(comment.data.comments);
        if(comment.data.more)
            $('.recent-comment > ul').innerHTML += `
                <div class="more">
                    <p>查看全部${comment.data.total}条评论</p>
                </div>
            `;
    }
) )