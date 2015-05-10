/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#
/*
 * UNIX shell
 *
 * S. R. Bourne
 * Bell Telephone Laboratories
 *
 */

#include	"defs.h"
#include	"sym.h"

static INT	parent;

extern SYSTAB		commands;



/* ========	command execution	========*/


execute(argt, execflg, pf1, pf2)
	TREPTR		argt;
	INT		*pf1, *pf2;
{
	/* `stakbot' is preserved by this routine */
	REG TREPTR	t;
	STKPTR		sav=savstak();

	sigchk();

	IF (t=argt) && execbrk==0
	THEN	REG INT		treeflgs;
		INT		oldexit, type;
		REG STRING	*com;

		treeflgs = t->tretyp; type = treeflgs&COMMSK;
		oldexit=exitval; exitval=0;

		switch(type) {

		case TCOM:
			{
			STRING		a1;
			INT		argn, internal;
			ARGPTR		schain=gchain;
			IOPTR		io=t->treio;
			gchain=0;
			argn = getarg(t);
			com=scan(argn);
			a1=com[1]; gchain=schain;

			IF (internal=syslook(com[0],commands)) || argn==0
			THEN	setlist(((COMPTR)t)->comset, 0);
			FI

			IF argn && (flags&noexec)==0
			THEN	/* print command if execpr */
				IF flags&execpr
				THEN	argn=0;	prs(execpmsg);
					WHILE com[argn]!=ENDARGS
					DO prs(com[argn++]); blank() OD
					newline();
				FI

				switch(internal) {

				case SYSDOT:
					IF a1
					THEN	REG INT		f;
	
						IF (f=pathopen(getpath(a1), a1)) < 0
						THEN failed(a1,notfound);
						} else { execexp(0,f);
						FI
					FI
					break;
	
				case SYSTIMES:
					{
					L_INT	t[4]; times(t);
					prt(t[2]); blank(); prt(t[3]); newline();
					}
					break;
	
				case SYSEXIT:
					exitsh(a1?stoi(a1):oldexit);
	
				case SYSNULL:
					io=0;
					break;
	
				case SYSCONT:
					execbrk = -loopcnt; break;
	
				case SYSBREAK:
					IF (execbrk=loopcnt) && a1
					THEN breakcnt=stoi(a1);
					FI
					break;
	
				case SYSTRAP:
					IF a1
					THEN	BOOL	clear;
						IF (clear=digit(*a1))==0
						THEN	++com;
						FI
						WHILE *++com
						DO INT	i;
						   IF (i=stoi(*com))>=MAXTRAP || i<MINTRAP
						   THEN	failed(*com,badtrap);
						   } else if ( clear
						   THEN	clrsig(i);
						   } else {	replace(&trapcom[i],a1);
							IF *a1
							THEN	getsig(i);
							} else {	ignsig(i);
							FI
						   FI
						OD
					} else {	/* print out current traps */
						INT		i;
	
						FOR i=0; i<MAXTRAP; i++
						DO IF trapcom[i]
						   THEN	prn(i); prs(colon); prs(trapcom[i]); newline();
						   FI
						OD
					FI
					break;
	
				case SYSEXEC:
					com++;
					initio(io); ioset=0; io=0;
					IF a1==0 THEN break FI
	
				case SYSLOGIN:
					flags |= forked;
					oldsigs(); execa(com); done();
	
				case SYSCD:
					IF flags&rshflg
					THEN	failed(com[0],restricted);
					} else if ( (a1==0 && (a1=homenod.namval)==0) || chdir(a1)<0
					THEN	failed(a1,baddir);
					FI
					break;
	
				case SYSSHFT:
					IF dolc<1
					THEN	error(badshift);
					} else {	dolv++; dolc--;
					FI
					assnum(&dolladr, dolc);
					break;
	
				case SYSWAIT:
					await(-1);
					break;
	
				case SYSREAD:
					exitval=readvar(&com[1]);
					break;

/*
				case SYSTST:
					exitval=testcmd(com);
					break;
*/

				case SYSSET:
					IF a1
					THEN	INT	argc;
						argc = options(argn,com);
						IF argc>1
						THEN	setargs(com+argn-argc);
						FI
					} else if ( ((COMPTR)t)->comset==0
					THEN	/*scan name chain and print*/
						namscan(printnam);
					FI
					break;
	
				case SYSRDONLY:
					exitval=N_RDONLY;
				case SYSXPORT:
					IF exitval==0 THEN exitval=N_EXPORT; FI
	
					IF a1
					THEN	WHILE *++com
						DO attrib(lookup(*com), exitval) OD
					} else {	namscan(printflg);
					FI
					exitval=0;
					break;
	
				case SYSEVAL:
					IF a1
					THEN	execexp(a1,&com[2]);
					FI
					break;

                                case SYSUMASK:
                                        if (a1) {
                                                int c, i;
                                                i = 0;
                                                while ((c = *a1++) >= '0' &&
                                                        c <= '7')
                                                        i = (i << 3) + c - '0';
                                                umask(i);
                                        } else {
                                                int i, j;
                                                umask(i = umask(0));
                                                prc('0');
                                                for (j = 6; j >= 0; j -= 3)
                                                        prc(((i>>j)&07) + '0');
                                                newline();
                                        }
                                        break;
	
				default:
					internal=builtin(argn,com);

				}

				IF internal
				THEN	IF io THEN error(illegal) FI
					chktrap();
					break;
				FI
			} else if ( t->treio==0
			THEN	break;
			FI
			}
	
		case TFORK:
			IF execflg && (treeflgs&(FAMP|FPOU))==0
			THEN	parent=0;
			} else {	WHILE (parent=fork()) == -1
				DO sigchk(); alarm(10); pause() OD
			FI

			IF parent
			THEN	/* This is the parent branch of fork;    */
				/* it may or may not wait for the child. */
				IF treeflgs&FPRS && flags&ttyflg
				THEN	prn(parent); newline();
				FI
				IF treeflgs&FPCL THEN closepipe(pf1) FI
				IF (treeflgs&(FAMP|FPOU))==0
				THEN	await(parent);
				} else if ( (treeflgs&FAMP)==0
				THEN	post(parent);
				} else {	assnum(&pcsadr, parent);
				FI

				chktrap();
				break;


			} else {	/* this is the forked branch (child) of execute */
				flags |= forked; iotemp=0;
				postclr();
				settmp();

				/* Turn off INTR and QUIT if `FINT'  */
				/* Reset ramaining signals to parent */
				/* except for those `lost' by trap   */
				oldsigs();
				IF treeflgs&FINT
				THEN	signal(INTR,1); signal(QUIT,1);
				FI

				/* pipe in or out */
				IF treeflgs&FPIN
				THEN	sh_rename(pf1[INPIPE],0);
					close(pf1[OTPIPE]);
				FI
				IF treeflgs&FPOU
				THEN	sh_rename(pf2[OTPIPE],1);
					close(pf2[INPIPE]);
				FI

				/* default std input for & */
				IF treeflgs&FINT && ioset==0
				THEN	sh_rename(chkopen(devnull),0);
				FI

				/* io redirection */
				initio(t->treio);
				IF type!=TCOM
				THEN	execute(((FORKPTR)t)->forktre,1);
				} else if ( com[0]!=ENDARGS
				THEN	setlist(((COMPTR)t)->comset,N_EXPORT);
					execa(com);
				FI
				done();
			FI

		case TPAR:
			sh_rename(dup(2),output);
			execute(((PARPTR)t)->partre,execflg);
			done();

		case TFIL:
			{
			   INT pv[2]; chkpipe(pv);
			   IF execute(((LSTPTR)t)->lstlef, 0, pf1, pv)==0
			   THEN	execute(((LSTPTR)t)->lstrit, execflg, pv, pf2);
			   } else {	closepipe(pv);
			   FI
			}
			break;

		case TLST:
			execute(((LSTPTR)t)->lstlef,0);
			execute(((LSTPTR)t)->lstrit,execflg);
			break;

		case TAND:
			IF execute(((LSTPTR)t)->lstlef,0)==0
			THEN	execute(((LSTPTR)t)->lstrit,execflg);
			FI
			break;

		case TORF:
			IF execute(((LSTPTR)t)->lstlef,0)!=0
			THEN	execute(((LSTPTR)t)->lstrit,execflg);
			FI
			break;

		case TFOR:
			{
			   NAMPTR	n = lookup(((FORPTR)t)->fornam);
			   STRING	*args;
			   DOLPTR	argsav=0;

			   IF ((FORPTR)t)->forlst==0
			   THEN    args=dolv+1;
				   argsav=useargs();
			   } else {	   ARGPTR	schain=gchain;
				   gchain=0;
				   trim((args=scan(getarg(((FORPTR)t)->forlst)))[0]);
				   gchain=schain;
			   FI
			   loopcnt++;
			   WHILE *args!=ENDARGS && execbrk==0
			   DO	assign(n,*args++);
				execute(((FORPTR)t)->fortre,0);
				IF execbrk<0 THEN execbrk=0 FI
			   OD
			   IF breakcnt THEN breakcnt-- FI
			   execbrk=breakcnt; loopcnt--;
			   argfor=freeargs(argsav);
			}
			break;

		case TWH:
		case TUN:
			{
			   INT		i=0;

			   loopcnt++;
			   WHILE execbrk==0 && (execute(((WHPTR)t)->whtre,0)==0)==(type==TWH)
			   DO i=execute(((WHPTR)t)->dotre,0);
			      IF execbrk<0 THEN execbrk=0 FI
			   OD
			   IF breakcnt THEN breakcnt-- FI
			   execbrk=breakcnt; loopcnt--; exitval=i;
			}
			break;

		case TIF:
			IF execute(((IFPTR)t)->iftre,0)==0
			THEN	execute(((IFPTR)t)->thtre,execflg);
			} else {	execute(((IFPTR)t)->eltre,execflg);
			FI
			break;

		case TSW:
			{
			   REG STRING	r = mactrim(((SWPTR)t)->swarg);
			   t=(TREPTR)((SWPTR)t)->swlst;
			   WHILE t
			   DO	ARGPTR		rex=((REGPTR)t)->regptr;
				WHILE rex
				DO	REG STRING	s;
					IF gmatch(r,s=macro(rex->argval)) || (trim(s), eq(r,s))
					THEN	execute(((REGPTR)t)->regcom,0);
						t=0; break;
					} else {	rex=((ARGPTR)rex)->argnxt;
					FI
				OD
				IF t THEN t=(TREPTR)((REGPTR)t)->regnxt FI
			   OD
			}
			break;
		}
		exitset();
	FI

	sigchk();
	tdystak(sav);
	return(exitval);
}


execexp(s,f)
	STRING		s;
	UFD		f;
{
	FILEBLK		fb;
	push(&fb);
	IF s
	THEN	estabf(s); fb.feval=(STRING *)f;
	} else if ( f>=0
	THEN	initf(f);
	FI
	execute(cmd(NL, NLFLG|MTFLG),0);
	pop();
}
