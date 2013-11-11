#! /usr/bin/env python
# encoding: utf-8

#Copyright (c) 2012 anton.feldmann@gmail.com
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation  files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the  Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE  WARRANTIES# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import os

VERSION='0.0.1'

top = '.'
out = 'build'

def usage(ctx):
	print('waf configure build ')

def options(opt):
	try:
		opt.add_option('--doxygen', action = 'store', default = False, help = 'use doxygen documentation' + '[default: %default]')
		print('doxygen option is: ' + opt.options.doxygen)
	except:
		pass

	opt.load('compiler_c')

def configure(conf):
	print('configure project ' + conf.path.abspath())

	conf.env.CC = 'clang'

        conf.load('compiler_c')

	conf.check_cc(lib='bfd',
		      uselib_store='BFD', 
		      mandatory=True)

def build(bld):
	bld.recurse('src')
	bld.recurse('include')
	bld.recurse('test')



