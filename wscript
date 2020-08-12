#! /usr/bin/env python
# encoding: utf-8

#Copyright (c) 2012 anton.feldmann@gmail.com
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation  files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the  Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE  WARRANTIES# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import os

major  = 1
minor  = 0
bugfix = 0

name = 'embedded_gdb'
application = name
version='%d.%d.%d' % (major, minor, bugfix)

top = '.'
out = 'build'

def usage(ctx):
	print('waf configure build ')

def options(opt):
	opt.load('compiler_c')
	try:
		opt.add_option('--test',
			       action='store_true',
			       default=True,
			       help='build test application')
		opt.add_option('--doxygen',
			       action = 'store',
			       default = False,
			       help = 'use doxygen documentation' + '[default: %default]')
	except:
		pass

def configure(conf):

	conf.env.CC = 'clang'

	conf.load('compiler_c')

	conf.check_cc(lib='bfd',
		      uselib_store='BFD',
		      mandatory=True)

def build(bld):
	bld(features   = 'c cprogram',
	    source     = 'src/gdb_breakpoint.c',
	    target     = name,
	    includes   = ['include/'],
	    uselib     = 'BFD',
	    cflags     = ['-O3', '-Wall','-std=gnu99'],
	    )

	bld.install_files('${PREFIX}/include/%s/' % name, bld.path.ant_glob(['**/*.h'], remove=False))

	from waflib import Options
	if Options.options.test:
		print('build project ' + bld.path.abspath())
		bld(features     = 'c cprogram',
		    source       = 'test/test.c',
		    target       = 'test.app',
		    includes     = ['include/'],
		    cflags       = ['-O2', '-Wall', '-g'],
		    install_path = '.'
		    )

	if Options.options.doxygen:
		doxygen(bld)


# doxygen docs
from waflib.Build import BuildContext
class doxy (BuildContext):
    cmd = "doxygen"
    fun = "doxygen"

from waflib import Logs
def doxygen (bld):
    if not bld.env.DOXYGEN:
        bld.fatal ("ERROR: cannot build documentation (`doxygen' is not found in $PATH)")
    Logs.pprint('CYAN', "create documents")
    bld (features="doxygen",
         doxyfile='doc/Doxyfile',
         output_dir = 'doc/html')
    Logs.pprint('YELLOW', "documents in %s" % bld.env.PREFIX)



