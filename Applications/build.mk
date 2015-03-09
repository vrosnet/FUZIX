# Simple, one-source-file utilities that live in Applications/util.
# Ideally we'd like to do this using a pattern (something like
# .../%: .../%.o), but Make doesn't support adding prerequisites
# via pattern rules. So we have to list each one individually.
# We could automate this using make scripting, but it'd actually be
# more code and about 1000% less understandable.
$(OBJ)/Applications/util/banner:   $(OBJ)/Applications/util/banner.$O
$(OBJ)/Applications/util/basename: $(OBJ)/Applications/util/basename.$O
$(OBJ)/Applications/util/bd:       $(OBJ)/Applications/util/bd.$O
$(OBJ)/Applications/util/cal:      $(OBJ)/Applications/util/cal.$O
$(OBJ)/Applications/util/cat:      $(OBJ)/Applications/util/cat.$O
$(OBJ)/Applications/util/chgrp:	   $(OBJ)/Applications/util/chgrp.$O
$(OBJ)/Applications/util/chmod:    $(OBJ)/Applications/util/chmod.$O
$(OBJ)/Applications/util/chown:    $(OBJ)/Applications/util/chown.$O
$(OBJ)/Applications/util/cksum:    $(OBJ)/Applications/util/cksum.$O
$(OBJ)/Applications/util/cmp:      $(OBJ)/Applications/util/cmp.$O
$(OBJ)/Applications/util/cp:       $(OBJ)/Applications/util/cp.$O
$(OBJ)/Applications/util/cut:      $(OBJ)/Applications/util/cut.$O
$(OBJ)/Applications/util/date:     $(OBJ)/Applications/util/date.$O
$(OBJ)/Applications/util/dd:       $(OBJ)/Applications/util/dd.$O
$(OBJ)/Applications/util/decomp16: $(OBJ)/Applications/util/decomp16.$O
$(OBJ)/Applications/util/df:       $(OBJ)/Applications/util/df.$O
$(OBJ)/Applications/util/dirname:  $(OBJ)/Applications/util/dirname.$O
$(OBJ)/Applications/util/dosread:  $(OBJ)/Applications/util/dosread.$O
$(OBJ)/Applications/util/du:       $(OBJ)/Applications/util/du.$O
$(OBJ)/Applications/util/echo:     $(OBJ)/Applications/util/echo.$O
$(OBJ)/Applications/util/ed:       $(OBJ)/Applications/util/ed.$O
$(OBJ)/Applications/util/false:    $(OBJ)/Applications/util/false.$O
$(OBJ)/Applications/util/fdisk:    $(OBJ)/Applications/util/fdisk.$O
$(OBJ)/Applications/util/fgrep:    $(OBJ)/Applications/util/fgrep.$O
$(OBJ)/Applications/util/fsck:     $(OBJ)/Applications/util/fsck.$O
$(OBJ)/Applications/util/grep:     $(OBJ)/Applications/util/grep.$O
$(OBJ)/Applications/util/head:     $(OBJ)/Applications/util/head.$O
$(OBJ)/Applications/util/id:       $(OBJ)/Applications/util/id.$O
$(OBJ)/Applications/util/init:     $(OBJ)/Applications/util/init.$O
$(OBJ)/Applications/util/kill:     $(OBJ)/Applications/util/kill.$O
$(OBJ)/Applications/util/ll:       $(OBJ)/Applications/util/ll.$O
$(OBJ)/Applications/util/ln:       $(OBJ)/Applications/util/ln.$O
$(OBJ)/Applications/util/logname:  $(OBJ)/Applications/util/logname.$O
$(OBJ)/Applications/util/ls:       $(OBJ)/Applications/util/ls.$O
$(OBJ)/Applications/util/man:      $(OBJ)/Applications/util/man.$O
$(OBJ)/Applications/util/mkdir:    $(OBJ)/Applications/util/mkdir.$O
$(OBJ)/Applications/util/mkfs:     $(OBJ)/Applications/util/mkfs.$O
$(OBJ)/Applications/util/mkfifo:   $(OBJ)/Applications/util/mkfifo.$O
$(OBJ)/Applications/util/mknod:    $(OBJ)/Applications/util/mknod.$O
$(OBJ)/Applications/util/more:     $(OBJ)/Applications/util/more.$O
$(OBJ)/Applications/util/mount:    $(OBJ)/Applications/util/mount.$O
$(OBJ)/Applications/util/mv:       $(OBJ)/Applications/util/mv.$O
$(OBJ)/Applications/util/od:       $(OBJ)/Applications/util/od.$O
$(OBJ)/Applications/util/pagesize: $(OBJ)/Applications/util/pagesize.$O
$(OBJ)/Applications/util/passwd:   $(OBJ)/Applications/util/passwd.$O
$(OBJ)/Applications/util/patchcpm: $(OBJ)/Applications/util/patchcpm.$O
$(OBJ)/Applications/util/printenv: $(OBJ)/Applications/util/printenv.$O
$(OBJ)/Applications/util/prtroot:  $(OBJ)/Applications/util/prtroot.$O
$(OBJ)/Applications/util/ps:       $(OBJ)/Applications/util/ps.$O
$(OBJ)/Applications/util/pwd:      $(OBJ)/Applications/util/pwd.$O
$(OBJ)/Applications/util/rm:       $(OBJ)/Applications/util/rm.$O
$(OBJ)/Applications/util/rmdir:    $(OBJ)/Applications/util/rmdir.$O
$(OBJ)/Applications/util/sleep:    $(OBJ)/Applications/util/sleep.$O
$(OBJ)/Applications/util/ssh:      $(OBJ)/Applications/util/ssh.$O
$(OBJ)/Applications/util/sort:     $(OBJ)/Applications/util/sort.$O
$(OBJ)/Applications/util/stty:     $(OBJ)/Applications/util/stty.$O
$(OBJ)/Applications/util/sum:      $(OBJ)/Applications/util/sum.$O
$(OBJ)/Applications/util/su:       $(OBJ)/Applications/util/su.$O
$(OBJ)/Applications/util/sync:     $(OBJ)/Applications/util/sync.$O
$(OBJ)/Applications/util/tee:      $(OBJ)/Applications/util/tee.$O
$(OBJ)/Applications/util/tail:     $(OBJ)/Applications/util/tail.$O
$(OBJ)/Applications/util/touch:    $(OBJ)/Applications/util/touch.$O
$(OBJ)/Applications/util/tr:       $(OBJ)/Applications/util/tr.$O
$(OBJ)/Applications/util/true:     $(OBJ)/Applications/util/true.$O
$(OBJ)/Applications/util/umount:   $(OBJ)/Applications/util/umount.$O
$(OBJ)/Applications/util/uniq:     $(OBJ)/Applications/util/uniq.$O
$(OBJ)/Applications/util/uud:      $(OBJ)/Applications/util/uud.$O
$(OBJ)/Applications/util/uue:      $(OBJ)/Applications/util/uue.$O
$(OBJ)/Applications/util/wc:       $(OBJ)/Applications/util/wc.$O
$(OBJ)/Applications/util/which:    $(OBJ)/Applications/util/which.$O
$(OBJ)/Applications/util/who:      $(OBJ)/Applications/util/who.$O
$(OBJ)/Applications/util/whoami:   $(OBJ)/Applications/util/whoami.$O
$(OBJ)/Applications/util/write:    $(OBJ)/Applications/util/write.$O
$(OBJ)/Applications/util/xargs:    $(OBJ)/Applications/util/xargs.$O
$(OBJ)/Applications/util/yes:      $(OBJ)/Applications/util/yes.$O

# Build levee, the text editor.
$(OBJ)/Applications/levee/levee: \
	$(OBJ)/Applications/levee/beep.$O \
	$(OBJ)/Applications/levee/blockio.$O \
	$(OBJ)/Applications/levee/display.$O \
	$(OBJ)/Applications/levee/doscall.$O \
	$(OBJ)/Applications/levee/editcor.$O \
	$(OBJ)/Applications/levee/exec.$O \
	$(OBJ)/Applications/levee/find.$O \
	$(OBJ)/Applications/levee/flexcall.$O \
	$(OBJ)/Applications/levee/gemcall.$O \
	$(OBJ)/Applications/levee/globals.$O \
	$(OBJ)/Applications/levee/insert.$O \
	$(OBJ)/Applications/levee/main.$O \
	$(OBJ)/Applications/levee/misc.$O \
	$(OBJ)/Applications/levee/modify.$O \
	$(OBJ)/Applications/levee/move.$O \
	$(OBJ)/Applications/levee/rmxcall.$O \
	$(OBJ)/Applications/levee/ucsd.$O \
	$(OBJ)/Applications/levee/undo.$O \
	$(OBJ)/Applications/levee/unixcall.$O \
	$(OBJ)/Applications/levee/wildargs.$O