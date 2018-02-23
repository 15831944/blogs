syntax on						"语法支持

"------------  通用设置 ----------------
"---------- Common Configs -------------

set autoindent		        	"自动缩进
set autoread		        	"文件在 vim 外修改过，自动重新读入
set backspace=2		        	"在 insert 模式下用退格键删除
set background=dark	        	"背景色为暗
"set cursorline		        	"为光标所在行加下划线
"set expandtab                  "使用空格代替制表符
set fileencodings=utf-8,gb2312,gbk,gb18030     "打开文件时的字符编码
set fileformats=unix			"文件格式
"set foldmethod		        	"代码折叠
set helplang=cn		    	    "帮助系统为中文
set hlsearch		        	"检索时高亮匹配项
"set ignorecase		        	"检索时忽略大小写
set laststatus=2	        	"总是显示状态行
set mouse=a						"鼠标支持
set number		            	"显示行号
set nowrap						"关闭自动折行
set ruler						"显示位置指示器
set softtabstop=4				"软制表符长度
set showmode					"显示模式
set showmatch					"代码匹配
set smarttab					"智能制表符
set smartindent					"智能缩进
set shiftwidth=4				"一个缩进的长度
"set synmaxcol=256
"set termencoding=utf-8
set tabstop=4					"一个制表符的长度

"----------- 标签页设置 ---------------
"--------- Configs for tabs -----------

let mapleaders = ','
nnoremap <C-l> gt
nnoremap <C-h> gT
nnoremap <leader>t : tabe<CR>

"----------- 插件配置 ----------------
"------ Configs for plugins ----------

"powerline
"set guifont=PowerlineSymbols\ for\ Powerline
"set nocompatible
"set t_Co=256
"let g:Powerline_symbols = 'fancy'

"pathogen
call pathogen#infect()
