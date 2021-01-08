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
" Plug 'dense-analysis/ale'
" Plug 'maximbaz/lightline-ale'

Plug 'joker1007/vim-markdown-quote-syntax'
Plug 'cespare/vim-toml' " TOML syntax highlight

" Plug 'jiangmiao/auto-pairs'

Plug 'tpope/vim-surround' " s for surrounding text object. e.g. cs'" for changing surrounding ' to "
Plug 'terryma/vim-expand-region' " +/_ for expand/shrink visual select region

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
    \       'left': [ [ 'mode', 'paste' ], [ 'readonly', 'filename', 'modified', 'gitbranch' ], ],
    \       'right': [ [ 'lineinfo' ], [ 'percent' ], [ 'fileformat', 'fileencoding', 'filetype' ] ],
    \   },
    \   'component_function': {
    \       'gitbranch': 'FugitiveHead',
    \   },
    \ }

set background=dark
color vim-material
" color desert
au ColorScheme * hi Comment cterm=NONE gui=NONE | hi Search ctermfg=yellow guifg=yellow
" disable italic comment and enable highlight search color
au ColorScheme * hi CursorLine term=NONE cterm=NONE | hi CursorLineNr cterm=NONE
" disable cursorline and cursorline number underline
" au ColorScheme * hi Normal guibg=NONE

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
nnoremap <silent> <C-n> :tabnew<CR>:Startify<CR>
vnoremap <silent> J :m '>+1<CR>gv=gv
vnoremap <silent> K :m '<-2<CR>gv=gv
vnoremap > >gv
vnoremap < <gv
command Codeforces %d<bar>r ~/CompetitiveProgramming/templates/main.cpp<bar>1d<bar>15,95fo<bar>103

nnoremap <silent> <F2> :if expand('%') <bar> cd %:h <bar> endif <bar> NERDTreeToggle <bar> call lightline#update()<CR>

function s:CppFastBuild()
    nnoremap <F9> :w<bar>!g++ % -o %:r -std=c++17 -Dlocal -Ofast -Wfatal-errors -fsanitize=undefined -fsanitize=address<CR>
    nnoremap <F10> :!./%:r<CR>
endfunction

function s:PythonFastBuild()
    nnoremap <silent> <F10> :w<bar>!python3 %<CR>
    nnoremap <F8> :w<bar>shell<CR><CR>
endfunction

function s:VimrcFastLoad()
    nnoremap <silent> <F10> :w<bar>so %<CR>
endfunction

function s:XeLaTeXBuild()
    nnoremap <F9> :w<bar>!./compile_xelatex.sh<CR>
    nnoremap <F10> :!xdg-open main.pdf<CR>
endfunction

augroup fastbuild
    au!
    au BufEnter *.cpp call <SID>CppFastBuild()
    au BufEnter *.py call <SID>PythonFastBuild()
    au BufEnter *.vim,_vimrc,.vimrc call <SID>VimrcFastLoad()
    au BufEnter *.tex call <SID>XeLaTeXBuild()
augroup END

noh
cd ~/CompetitiveProgramming/
