@echo off
call vcvars

md current\build
copy /Y Makefile.vc current\
cd current
nmake -nologo -f Makefile.vc distclean
nmake -nologo -f Makefile.vc AS=ml64 LOC="-DASMV -DASMINF -I." OBJA="inffasx64.obj gvmat64.obj inffas8664.obj" static shared
nmake -nologo -f Makefile.vc clean
cd ..