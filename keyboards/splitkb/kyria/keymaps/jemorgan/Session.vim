let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/dev/qmk_firmware/keyboards/splitkb/kyria/keymaps/jemorgan
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +28 config.h
badd +31 keymap.c
badd +1 rules.mk
badd +1 ~/dev/qmk_firmware/users/jemorgan/buffer.c
badd +1 ~/dev/qmk_firmware/users/jemorgan/buffer.h
badd +1 ~/dev/qmk_firmware/users/jemorgan/config.h
argglobal
%argdel
$argadd config.h
$argadd keymap.c
$argadd rules.mk
edit ~/dev/qmk_firmware/users/jemorgan/config.h
argglobal
if bufexists(fnamemodify("~/dev/qmk_firmware/users/jemorgan/config.h", ":p")) | buffer ~/dev/qmk_firmware/users/jemorgan/config.h | else | edit ~/dev/qmk_firmware/users/jemorgan/config.h | endif
if &buftype ==# 'terminal'
  silent file ~/dev/qmk_firmware/users/jemorgan/config.h
endif
balt ~/dev/qmk_firmware/users/jemorgan/buffer.h
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=1
setlocal fml=1
setlocal fdn=1
setlocal fen
let s:l = 1 - ((0 * winheight(0) + 30) / 60)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
