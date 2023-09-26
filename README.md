# [竺院辅学计划站点](https://ckc-agc.github.io/study-assist/)

😉你好~

## 简介

这里是竺可桢学院学业指导中心辅学计划站点。辅学计划为竺院大一新生提供数学分析（H）、线性代数（H）、微积分（H）、普通物理学（H）、普通化学（H）、程序设计基础等**荣誉课程**的学习指导与帮助。该仓库用于存储和部署我们的辅学计划网站。

## 构建

该仓库已经设置了 GitHub Action，您的每次推送都会自动触发构建与部署，无需在本地执行 `mkdocs gh-deploy` 等操作。

本网站基于 MkDocs Material 构建，额外使用的插件有：

- [neoteroi.cards](https://www.neoteroi.dev/mkdocs-plugins/cards/)
- [GLightbox](https://github.com/blueswen/mkdocs-glightbox)
- [mkdocs-heti-plugin](https://github.com/TonyCrane/mkdocs-heti-plugin)

安装 MkDocs 及相关插件：

```bash
pip install mkdocs mkdocs-material neoteroi-mkdocs mkdocs-glightbox mkdocs-heti-plugin
```

本地构建与查看：

```bash
mkdocs serve
```

手动部署到 GitHub Pages：

```bash
mkdocs gh-deploy
```

## 贡献

我们欢迎辅学学长以及其他同学为我们的网站贡献内容。如果你有任何想法，欢迎提出 issue 或者 PR。

请不要将大于 20MB 的文件（扫描版电子书）等上传到本仓库，大文件请联系学业指导中心同学转存至百度网盘。
