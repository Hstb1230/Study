const id = getParam('id');
console.log(id);

// 空请求，跳转首页
if(id === null || id.length == 0)
{
    window.location.href= '.';
}

// 获取封面
function getDetail()
{
    return axios.get(`${domain}/mv/detail`, {
        params: {
            mvid: id
        }
    })
    .then( data => {
        return data.data;
    });
}

// 获取Link
function getResource()
{
    return axios.get(`${domain}/mv/url`, {
        params: {
            id: id
        }
    })
    .then( data => {
        return data.data;
    });
}

// 获取评论
function getComment() 
{
    return axios.get(`${domain}/comment/mv`, {
        params: {
            id: id
        }
    })
    .then( data => {
        return data.data;
    });
}

let video = $('.video > video');

const makeVideoPause = () => {
    video.volume = Math.max(0, Math.floor((video.volume - 0.05) * 100) / 100);
    if(video.volume <= 0)
        video.pause();
    else
        setTimeout(makeVideoPause, Math.floor(video.volume * 100));
};

const makeVideoPlay = () => {
    video.volume = Math.min(1, Math.floor((video.volume + 0.04) * 100) / 100);
    if(video.volume < 1)
        setTimeout(makeVideoPlay, Math.floor(video.volume * 100));
};

let cover = $('.video > .cover');
let coverOpacity = 1;

const makeCoverTransparent = () => {
    coverOpacity = Math.max(0, Math.floor((coverOpacity - 0.06) * 100) / 100);
    cover.style.opacity = coverOpacity;
    if(cover.style.opacity <= 0)
        cover.style.display = 'none';
    else
        setTimeout(makeCoverTransparent, Math.floor(cover.style.opacity * 100));
}

const makeCoverOpaque = () => {
    if(cover.style.display === 'none')
        cover.style.display = '';
    coverOpacity = Math.min(1, Math.floor((coverOpacity + 0.03) * 100) / 100);
    cover.style.opacity = coverOpacity;
    if(cover.style.opacity < 1)
        setTimeout(makeCoverOpaque, Math.floor(cover.style.opacity * 100));
}

// 处理
function e(detail, resource, comment) {
    console.log(detail);
    // console.log(resource);
    console.log(comment);

    video.src = resource.data.url;
    video.onended = () => {
        setTimeout(makeCoverOpaque, (cover.style.opacity || 1) * 100);
    }

    document.onkeydown = e => {
        if(e.code === 'Space')
        {
            if(video.paused)
                cover.click();
            else
                setTimeout(makeVideoPause, Math.floor(video.volume));
            event.preventDefault();
        }
    }

    let coverView = $('.video > .cover > img');
    coverView.src = detail.data.cover;
    cover.onclick = () => {
        setTimeout(makeCoverTransparent, (cover.style.opacity || 1) * 100);
        video.play();
        setTimeout(makeVideoPlay, Math.floor(Math.max(video.volume, 0.01) * 100));
    }

    $('.mv-info .name').innerText = detail.data.name;

    let singer = '';
    detail.data.artists.forEach((a, i) => {
        if(i > 0)
            singer += ` / `;
        singer += a.name;
    });
    $('.mv-info > .artist').innerText = `歌手：${singer}`;

    document.title = `${detail.data.name} - ${singer}`;

    $('.mv-info > .data > .release').innerText = `发布时间：${detail.data.publishTime}`;
    $('.mv-info > .data > .play').innerText = `播放数：${detail.data.playCount}`;

    if(comment.hotComments.length > 0)
        $('.hot-comment > ul').innerHTML = parseComment(comment.hotComments);
    else 
        $('.hot-comment').style.display = 'none';
    
    $('.recent-comment > h3').innerText += `(${comment.total})`;
    $('.recent-comment > ul').innerHTML = parseComment(comment.comments);

}

axios.all( [ getDetail(), getResource(), getComment() ] )
.then( axios.spread(e) );
