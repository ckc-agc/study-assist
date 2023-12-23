# 贡献

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