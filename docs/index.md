# 欢迎来到竺院辅学计划网站

😉 你好~

这里是竺可桢学院学业指导中心辅学计划的站点。辅学计划为竺院大一新生提供数学分析（H）、线性代数（H）、微积分（H）、普通物理学（H）、普通化学（H）、程序设计基础等**荣誉课程**的学习指导与帮助。

你可以通过网站上方或左侧的导航栏浏览我们的网站。普通辅学版块使用 📚 标注，精品课程版块使用 🏫 标注。

<!-- prettier-ignore-start -->
::cards:: cols=2

[
  {
    "title": "[微积分 I/II（H）](calculus/index.md)",
    "content": "23-24辅学群：204755170",
    "image": "graph/calculus.webp"
  },
  {
    "title": "[数学分析 I/II（H）](analysis/index.md)",
    "content": "23-24辅学群：618962803",
    "image": "graph/analysis.jpg"
  },
  {
    "title": "[线性代数 I/II（H）](algebra/index.md)",
    "content": "23-24辅学群：913067714<br>
                [【精品课程】线性代数：未竟之美](lalu/index.md)",
    "image": "graph/algebra.jpg"
  },
  {
    "title": "[程序设计](programming/index.md)",
    "content": "23-24辅学群：728919863<br>
                [每日一题](programming/2024_daily_problem.md)<br>
                [【精品课程】系统知识拾遗](programming_lecture/index.md)<br>
                [【精品课程】实用技能拾遗](https://slides.tonycrane.cc/PracticalSkillsTutorial/2023-fall-ckc/#/)",
    "image": "graph/programming.jpg"
  },
  {
    "title": "[普通化学（H）](chemistry/index.md)",
    "content": "23-24辅学群：635023447",
    "image": "graph/chem.jpg"
  },
  {
    "title": "[普通物理学 I（H）](physics/index.md)",
    "content": "22-23辅学群：727382522 ",
    "image": "graph/physics.png"
  },
]

::/cards::
<!-- prettier-ignore-end -->

## 辅学简介

-   每个长学期初，我们会招募优秀的学长学姐作为辅学学长。所有辅学学长都会在辅学群内进行**答疑**，部分辅学学长会进行**授课**。
-   授课一般依照课程进度进行，对专题的知识进行总结复习，或是在期中期末考前进行复习和习题讲解。**开展授课前一周，辅学群内会发布授课信息和报名问卷**，同学们可以根据自己的需求选择参加。
-   辅学授课的形式自由，不论你是否填写问卷，都可以参加授课。你可以随时来到课堂，也可以随时离开，但请不要打扰到其他同学，并注意维护教室环境卫生。参与辅学的同学每次能够获得参与度纪实分数 0.5 分，每个长学期最多通过辅学系列活动获得 1 分。
-   此外，部分课程开设了**辅学精品课程**。授课学长学姐以课程组的形式组织起来，编写系统的配套的讲义，进行连贯的授课，深度契合竺院荣誉课程的内容。我们希望能携手优秀的学长学姐，为竺院学子打造高质量的辅学课程。

## 录播/回放

[![](https://stats.justsong.cn/api/bilibili/?id=3546574332365752&lang=zh-CN&theme=vue#only-light){align=right}![](https://stats.justsong.cn/api/bilibili/?id=3546574332365752&lang=zh-CN&theme=dracula#only-dark){align=right}](https://space.bilibili.com/3546574332365752)


> 致谢：竺可桢学院全媒体工作室

在竺院全媒体的人员和设备支持下，大部分辅学授课都有了优质的录播。一般情况下录播都将上传到竺院学指的 Bilibili 账号中，点击卡片即可跳转到 Bilibili 页面。

## 大文件存放处

超过 20MB 的大文件都放置在学业指导中心公共网盘的分享链接中，同学们可以点击下面的链接查看。如果有需要放置的大文件，请联系学业指导中心的同学上传。

-   [百度网盘-竺院辅学资料](https://pan.baidu.com/s/1OB8pDdSDJ_718Fx2nelyVg?pwd=c6mx)

## 相关网站

-   [浙江大学图灵班课程学习指南](https://github.com/ZJU-Turing/TuringCourses)
-   [浙江大学课程攻略共享计划](https://qsctech.github.io/zju-icicles/)

## 贡献

如果您愿意参与该网站的建设，请到 GitHub 中本项目的[仓库](https://github.com/ckc-agc/study-assist)进行贡献。

每个辅学科目的文件夹组织如下：

```text
subject
├── year
│   ├── some_file.md
│   └── some_file.pdf
├── exam
│   ├── some_paper.pdf
│   └── some_paper_answer.pdf
└── index.md
```

-   每个辅学科目的主页放置是 `index.md`，包含了该科目文件夹内各个资料的链接。页面侧边栏不需要有东西，不需要在 `mkdocs.yml` 中再为这些文件添加索引。
-   每年的辅学资料放置在同一个文件夹中，依次命名为 `lecture1_contents.pdf` 等。
-   所有历年卷及其答案放置在 `exam` 文件夹中，文件命名为 `subject_year_exam.pdf` 等，答案添加后缀 `_answer`。

精品课程的文件夹由该课程组自行组织和维护。