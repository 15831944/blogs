# GitHub Pages

免费的静态网站托管平台

# Site Type

| site type                 | branch          |
| ------------------------- | --------------- |
| User or organization site | master branch   |
| Project site              | gh-pages branch |

# publishing source

# automatic generator

# Repository

用于保存网页或模板

| file or directory | 说明                   |
| ----------------- | --------------------- |
| _includes         | 模板引用文件的位置, 对 {% include %} 标记扩展成对应的在此文件夹中的文件 |
| _layouts          | 公共页面的位置, 模板文件           |
| _posts            | 博客文章存放位置, 文件名为 YYYY-MM-DD-title |
| _site             | 本地调试时存放静态页面            |
| .gitignore        | 不纳入版本控制的文件              |
| _config.yml       | jekyll 模板引擎的配置文件         |
| index.html        | 网站主页                        |
| assets            | 存放资源文件, 图片, 样式表, 脚本等 |

# YAML front matter block

以 key: value 的形式对全局变量进行赋值

# liquid

解析引擎

标记

1. {{ ... }}: 输入标记，其中的内容将被转换为文本输出
2. \{\% ... \%\}: 操作标记，通常包含控制流代码, 比如：{% if %}, {% for xx in xx %}

filter, 对输出标记的扩展

# Jekyll

静态网站生成器 static site generator, 基于 ruby 开发, 将模板转化为静态网站

对象(模板数据API)

1. site: 全局站点对象, 比如 site.posts 返回当前站点所有在 \_post 目录下的文章, 上面的例子结合 for 循环来罗列所有的文章
2. page：文章对象, 比如 page.url 将返回 page 对象的 url, 上面的例子用该对象和属性返回了文章的链接

# Bundler

用于安装 Jekyll, 管理 Ruby gem 依赖关系, 减少 Jekyll 构建错误, 防止环境相关的 bug

# Ruby Gems

Ruby 的一个包管理器, 用于安装 Bundler

# Gemfile

文件保存在 Jekyll 网站仓库的根目录, 用于定义 gem 的源, 安装 Jekyll 的插件

# Jekyll site files

本地仓库中的基本的 Jekyll 模板网站

# Jekyll theme

修改 \_config.yml 文件中的 theme 字段

# 参考

我的博客

1. [windwanghuiyong](https://windwanghuiyong.github.io/)

官方网站

1. [GitHub Pages](https://pages.github.com/)
2. [jekyll](https://github.com/jekyll/jekyll)

官方文档

1. [GitHub Pages Basics](https://help.github.com/categories/github-pages-basics/)
2. [Customizing GitHub Pages](https://help.github.com/categories/customizing-github-pages/)

博客

1. [一步步在GitHub上创建博客主页](http://www.pchou.info/ssgithubPage/2013-01-03-build-github-blog-page-01.html)
