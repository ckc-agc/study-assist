# 贡献

在向 ckc-agc 仓库提交 PR 之前，请确保你已经阅读了本文档。

每个辅学科目的文件夹组织如下：

- 科目
    - 当前学期：特定学期的资料
    - 通用：跨学期的通用资料，比如历年卷
        - 历年卷
        - 笔记
        - ...
    - 归档
        - 学期
        - 学期

其中学期使用年份 + 季节命名，如：`23spring`、`24fall`。

文档的附件（如图片等），应当放置在 `文档名.assets` 文件夹中，以便于管理。

!!! example

    程设的文件夹结构如下：

    ```text
    programming
    ├── 24fall
    │   ├── index.md
    │   ├── lec1.md
    │   └── ...
    ├── common
    │   ├── exam
    │   │   ├── exam1.pdf
    │   │   └── exam1_answer.pdf
    │   └── notes
    ├── archive
    │   └── 23fall
    │       ├── index.md
    │       └── lec1
    │           ├── lec1.assets
    │           └── lec1.md
    └── index.md
    ```

- 每个辅学科目的主页放置是 `index.md`，包含了该科目文件夹内各个资料的链接。
- 每年的辅学资料放置在同一个文件夹中，依次命名为 `lec*.pdf` 等。
- 所有历年卷及其答案放置在 `exam` 文件夹中，文件命名为 `subject_year_exam.pdf` 等，答案添加后缀 `_answer`。

我们使用 [`markdownlint`](https://marketplace.visualstudio.com/items?itemName=DavidAnson.vscode-markdownlint)、[`autocorrect`](https://marketplace.visualstudio.com/items?itemName=huacnlee.autocorrect) 和 [`editorconfig`](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig) 插件对文档进行格式化。
