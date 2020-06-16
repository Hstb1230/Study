const id = getParam('id');

// 空请求，跳转首页
if(id === null || id.length == 0)
{
    window.location.href= '.';
}

function getPlaylistDetail()
{
    return axios.get(`${domain}/playlist/detail?id=${id}`)
}

function getPlaylistComment()
{
    return axios.get(`${domain}/comment/playlist?id=${id}`)
}

axios.all( [ getPlaylistDetail(), getPlaylistComment() ] )
.then( axios.spread(
    (detail, comment) => {
        console.log(detail);
        console.log(comment);

        let coverImg = $('.cover-img > img');
        let bgImg = $('.bg-blur > img');
        let playCount = $('.cover-img > .play-number');
        // 替换封面
        bgImg.src = coverImg.src = detail.data.playlist.coverImgUrl;
        // 替换播放数据
        if(detail.data.playlist.playCount > 1e8)
            playCount.innerHTML = `${Math.floor(detail.data.playlist.playCount / 1e8 * 10) / 10}亿`;
        else if(detail.data.playlist.playCount > 1e4)
            playCount.innerHTML = `${Math.floor(detail.data.playlist.playCount / 1e4 * 10) / 10}万`;
        else
            playCount.innerHTML = detail.data.playlist.playCount;
        
        let title = $('.title > h3');
        let authorName = $('.author > p');
        let authorAvatar = $('.author > .avatar > img');
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