" source ~/.simple-vimrc | finish

set nocompatible
set encoding=utf8
set fileencoding=utf8
set fileformat=unix

call plug#begin('~/.vim/plugged')

Plug 'hzchirs/vim-material'
" Plug 'flazz/vim-colorschemes'
Plug 'itchyny/lightline.vim'
" Plug 'vim-airline/vim-airline'
Plug 'mhinz/vim-startify'

" Plug 'skywind3000/asyncrun.vim' " :AsyncRun -mode=os -cwd=$(VIM_FILEDIR) command
Plug 'preservim/nerdtree' " <F2> for toggle nerdtree
Plug 'tpope/vim-fugitive' " :G [option] for git commands
Plug 'Xuyuanp/nerdtree-git-plugin' " git status

Plug 'tpope/vim-commentary' " gc for comment
Plug 'dense-analysis/ale'
Plug 'maximbaz/lightline-ale'

Plug 'joker1007/vim-markdown-quote-syntax'
Plug 'cespare/vim-toml' " TOML syntax highlight

call plug#end() 

if has('gui_running')
    au GUIEnter * simalt ~x " maximize window
    set guioptions-=m guioptions-=e guioptions-=T guioptions-=L guioptions-=R guioptions-=l guioptions-=r
    " menu | tab page | toolbar | left scrollbar | right scrollbar | left scrollbar (split) | right scrollbar (split)
    if has('win32')
        set guifont=Microsoft\ Yahei\ Mono:h14 " for Windows
    else
        set guifont=Dejavu\ Sans\ Mono\ 14
    endif
    " set guifontwide=DFKai-SB
endif

let g:startify_custom_header = startify#center(['VIM - Vi IMproved', 'JIZZZZZZZZZZZZZZZ', '@OmeletWithoutEgg'])
let g:startify_bookmarks = ['~/.vimrc']
" :h g:lightline.colorscheme
let g:lightline = {
    \   'colorscheme': 'materia',
    \   'active': {
    \       'left': [ [ 'mode', 'paste' ], [ 'readonly', 'filename', 'modified', 'gitbranch' ],
    \           ['linter_checking', 'linter_infos', 'linter_warnings', 'linter_errors', 'linter_ok'] ],
    \       'right': [ [ 'lineinfo' ], [ 'percent' ], [ 'fileformat', 'fileencoding', 'filetype' ] ],
    \   },
    \   'component_function': {
    \       'gitbranch': 'FugitiveHead',
    \       'linter_checking': 'lightline#ale#checking',
    \       'linter_infos': 'lightline#ale#infos',
    \       'linter_warnings': 'lightline#ale#warnings',
    \       'linter_errors': 'lightline#ale#errors',
    \       'linter_ok': 'lightline#ale#ok',
    \   },
    \   'component_type': {
    \     'linter_checking': 'right',
    \     'linter_infos': 'right',
    \     'linter_warnings': 'warning',
    \     'linter_errors': 'error',
    \     'linter_ok': 'right'
    \   }
    \ }

set background=dark
color vim-material
" color desert
au ColorScheme * hi Comment cterm=none gui=none | hi Search ctermfg=yellow guifg=yellow
" disable italic comment and enable highlight search color
au ColorScheme * hi CursorLine term=NONE cterm=NONE | hi CursorLineNr cterm=NONE
" disable cursorline and cursorline number underline

let g:ale_linters_explicit = 1
let g:ale_linters = {
  \   'csh': ['shell'],
  \   'zsh': ['shell'],
  \   'go': ['gofmt', 'golint'],
  \   'python': ['flake8', 'mypy', 'pylint'],
  \   'c': ['gcc', 'cppcheck'],
  \   'cpp': ['gcc', 'cppcheck'],
  \   'text': [],
  \}
let g:ale_echo_delay = 20
let g:ale_lint_delay = 500
let g:ale_echo_msg_format = '[%severity%] %s;'
let g:ale_lint_on_text_changed = 'normal'
let g:ale_lint_on_insert_leave = 1
let g:ale_lint_on_save = 0
let g:ale_lint_on_enter = 0
let g:ale_cpp_cc_executable = 'gcc'
let g:ale_cpp_cc_options = '-std=c++17 -Wall -Wshadow -Wextra -Dlocal'
" let g:ale_completion_enabled = 1
" let g:ale_completion_delay = 500

syntax on
set nu rnu cin bs=2 et sw=4 sts=4 hls
set belloff=all laststatus=2 mouse=a
set cursorline noshowmode lazyredraw termguicolors autochdir showcmd
set ttimeoutlen=0
set listchars=trail:␣,eol:$,tab:►\ ,extends:⟩,precedes:⟨,space:·
" set listchars=tab:→\ ,trail:•
augroup rnutoggle
    au!
    au InsertEnter * set nornu
    au InsertLeave * if expand('%') != '' | set rnu | endif
augroup END

inoremap <C-c> <Esc>
inoremap {<CR> {<CR>}<C-o>O
nnoremap ya :%y+<CR>
nnoremap <silent> <C-n> :tabnew<CR>:Startify<CR>
vnoremap <silent> J :m '>+1<CR>gv=gv
vnoremap <silent> K :m '<-2<CR>gv=gv
vnoremap > >gv
vnoremap < <gv

nnoremap <silent> <F2> :if expand('%') <bar> cd %:h <bar> endif<CR>:NERDTreeToggle<CR>:call lightline#update()<CR>

function CppFastBuild()
    nnoremap <F9> :w<bar>!g++ % -o %:r -std=c++17 -Dlocal -Ofast -Wfatal-errors -fsanitize=undefined -fsanitize=address<CR>
    nnoremap <F10> :!./%:r<CR>
endfunction

function PythonFastBuild()
    nnoremap <silent> <F10> :w<bar>!python3 %<CR>
    nnoremap <F8> :w<bar>shell<CR><CR>
endfunction

function VimrcFastLoad()
    nnoremap <silent> <F10> :w<bar>so %<CR>
endfunction

function XeLaTeXBuild()
    nnoremap <F9> :w<bar>!./compile_xelatex.sh<CR>
    nnoremap <F10> :!xdg-open main.pdf<CR>
endfunction

augroup fastbuild
    au!
    au BufEnter *.cpp call CppFastBuild()
    au BufEnter *.py call PythonFastBuild()
    au BufEnter *.vim,_vimrc,.vimrc call VimrcFastLoad()
    au BufEnter *.tex call XeLaTeXBuild()
augroup END

noh
cd ~/CompetitiveProgramming/
