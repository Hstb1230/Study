const userID = parseInt(localStorage.getItem('userID') || '');

function getLikeIcon() {
    return `
        <i><svg class="i-like" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 28 28"><path fill="#999" d="m25.857 14.752c-.015.059-1.506 5.867-2.932 8.813-1.162 2.402-3 2.436-3.099 2.436h-12.826v-13c3 0 5.728-4 5.728-7.275 0-3.725 1.433-3.725 2.142-3.725 1.327 0 1.978 1.345 1.978 4 0 2.872-.832 4.525-.839 4.537-.161.31-.155.682.027.981.181.299.5.482.849.482h6.942c.922 0 1.551.215 1.866.64.467.626.286 1.705.164 2.112m-23.857 10.248v-10c0-1.795.659-1.981.855-2h2.145v13h-2.173c-.829 0-.827-.648-.827-1m25.309-13.54c-.713-.969-1.886-1.46-3.482-1.46h-5.519c.26-.932.519-2.285.519-4 0-5.221-2.507-6-4-6-1.909 0-4.185.993-4.185 5.725 0 2.206-1.923 5.275-3.815 5.275h-4-.011c-1.034.011-2.816.862-2.816 4v10.02c0 1.198.675 2.979 2.827 2.979h16.971.035c.364 0 3.224-.113 4.894-3.564 1.514-3.127 3.01-8.942 3.056-9.14.071-.23.664-2.289-.474-3.836"></path></svg></i>
    `;
}

function getDeleteIcon() {
    return `
        <i>
            <svg class="i-delete" t="1592328402250" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="2948" width="200" height="200"><path d="M637.5424 775.0144a25.088 25.088 0 0 0 25.088-25.088V398.1312a25.088 25.088 0 0 0-50.176 0v351.7952a25.088 25.088 0 0 0 25.088 25.088zM386.304 775.0144a25.088 25.088 0 0 0 25.088-25.088V398.1312a25.088 25.088 0 0 0-50.176 0v351.7952c0 13.8752 11.2128 25.088 25.088 25.088zM511.9488 775.0144a25.088 25.088 0 0 0 25.088-25.088V398.1312a25.088 25.088 0 0 0-50.176 0v351.7952c0 13.8752 11.2128 25.088 25.088 25.088z" fill="#8a8a8a" p-id="2949"></path><path d="M888.8832 251.648h-167.168V199.3216c0-34.2016-27.8528-62.0544-62.0544-62.0544H364.3392c-16.5888 0-32.1536 6.4512-43.8784 18.176a61.7472 61.7472 0 0 0-18.2272 43.8784v52.3264H135.0656a25.088 25.088 0 0 0 0 50.176H210.432v559.8208c0 13.7728 11.1616 25.088 25.088 25.088h552.8576a25.088 25.088 0 0 0 25.088-25.088V301.824h75.3664a25.1392 25.1392 0 0 0 0.0512-50.176zM346.2144 199.3216c0-4.8128 1.8944-9.3696 5.2736-12.8a18.2784 18.2784 0 0 1 12.8512-5.2736h295.3216c9.984 0 18.0736 8.1408 18.0736 18.0736v52.3264h-15.0016v-0.1024H361.216v0.1024h-15.0016V199.3216z m416.9728 637.1328H260.7104V301.824h502.4768v534.6304z" fill="#8a8a8a" p-id="2950"></path></svg>
        </i>
    `;
}

function parseComment(comment, type, id)
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
            <li class="comment-info">
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
                        <div class="like"
                             onclick="likeComment(${type}, ${id}, ${c.commentId})"
                            >
                            ${c.likedCount || ''}
                            ${getLikeIcon()}
                        </div>
                        <div class="delete"
                             ${ userID == c.user.userId ? '' : 'style="display: none;"' }
                             onclick="deleteComment(${type}, ${id}, ${c.commentId})"
                            >
                            ${getDeleteIcon()}
                        </div>
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

function generateCommentView(div, type, id) 
{
    fetch(`${domain}/login/status`, {
        method: 'get',
        mode: 'cors',
        // 跨域Cookie
        credentials: 'include'
    })
    .then( data => data.json() )
    .then( data => {
        let isLogin = (data.code === 200);
        let form = $make('form');
        form.setAttribute('class', 'send-comment');
        form.innerHTML = `
            <div class="sc-send${isLogin ? '' : ' disable'}">
                <input type="text" id="sc-type" value="${type}" style="display: none;" />
                <input type="text" id="sc-id" value="${id}" style="display: none;" />
                <input type="text" id="sc-content" required placeholder="发表评论${isLogin ? '' : '(请先登录)'}">
                <img class="i-send" src="/img/send.svg"></img>
                <input type="submit" style="display: none;" />
            </div>
            ${ (!isLogin) ? '<img class="i-user" src="/img/user.svg"></img>' : ''}
        `;
        div.insertBefore(form, div.childNodes[0]);
        if(!isLogin)
        {
            $('.send-comment > .i-user').onclick = () => {
                window.location.href = `./login.html?ref=${escape(window.location.href)}`;
            }
        }
        $('.sc-send .i-send').onclick = form.onsubmit = sendComment;
    } );
}

function addCommentToView(c, type, id) {
    let li = $make('li');
    li.setAttribute('class', 'comment-info');
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
    li.innerHTML = `
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
                <div class="like"
                    onclick="likeComment(${type}, ${id}, ${c.commentId})"
                    >
                    ${getLikeIcon()}
                </div>
                <div class="delete"
                    ${ userID == c.user.userId ? '' : 'style="display: none;"' }
                    onclick="deleteComment(${type}, ${id}, ${c.commentId})"
                    >
                    ${getDeleteIcon()}
                </div>
            </div>
            <div class="content">
                ${c.content}
            </div>
        </div>
    `;
    let ul = $('.send-comment ~ ul');
    ul.insertBefore(li, ul.children[0]);
}

function sendComment() 
{
    let content = escape($('#sc-content').value);
    let type = $('#sc-type').value;
    let id = $('#sc-id').value;
    fetch(`${domain}/comment?t=1&type=${type}&id=${id}&content=${content}`, {
        method: 'get',
        mode: 'cors',
        // 跨域Cookie
        credentials: 'include'
    })
    .then( data => data.json() )
    .then( data => {
        console.log(data);
        if(data.code === 200)
            addCommentToView(data.comment, type, id);
        // location.reload();
    } )
    return false;
}

function likeComment(type, resourceID, commentID) 
{
    console.log('like', type, resourceID, commentID);
}

function deleteComment(type, resourceID, commentID) 
{
    console.log('delete', type, resourceID, commentID);
    fetch(`${domain}/comment?t=0&type=${type}&id=${resourceID}&commentId=${commentID}`, {
        method: 'get',
        mode: 'cors',
        // 跨域Cookie
        credentials: 'include'
    })
    .then( data => data.json() )
    .then( data => {
        console.log(data);
        location.reload();
    } )
}
