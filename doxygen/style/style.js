(function () {
    const container = document.createElement("div");
    container.id = "lang-switch";
    const path = window.location.pathname;
    const isEN = path.includes("/en/");
    const isZH = path.includes("/zh/");
    let enPath = path.replace("/zh/", "/en/");
    let zhPath = path.replace("/en/", "/zh/");
    if (!isEN && !isZH) {
        enPath = "/en/index.html";
        zhPath = "/zh/index.html";
    }

    container.innerHTML = ` 
        <a href="${zhPath}">中文</a> |
        <a href="${enPath}">English</a>
    `;
    document.body.appendChild(container);
    const parentElement = document.getElementById('titlearea');
    parentElement.appendChild(container);

    const link = document.createElement("div");
    link.innerHTML = `
        <a href="https://github.com/DreamDonghao/DaoUI" target="_blank"
           style="color: #9d1dc9; font-weight: bold;">
           github.com/DreamDonghao/DaoUI
        </a>
    `;
    parentElement.appendChild(link);
})();
