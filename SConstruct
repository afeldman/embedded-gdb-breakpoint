#Copyright (c) 2012 anton.feldmann@gmail.com
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation  files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the  Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the  Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE  WARRANTIES# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


import os
import sys
import platform

if not File( 'custom.py' ).exists():
 print 'Warning!!! custom.py is not present.\n default settings will be used\n\n'

binname = 'gdb_brakpoints'
includeheader = 'include/breakpoint.h'
binsource = 'src/gdb_breakpoint.c'

# prozess comands
vars = Variables( 'custom.py' )
vars.Add(BoolVariable('debug',  'set the prozessqueu to debug mode', False))
vars.Add(BoolVariable('release','set the prozessqueu to release mode', True))
vars.Add('compiler', 'compilersettings', 'clang')
vars.Add('prefix','path to the install directory', '/usr/local/')
vars.Add('bindir','install binary path',  '/usr/local/bin/')
vars.Add('includedir','install header path', '/usr/local/include/')

rootEnv = Environment(variables=vars)

Help(vars.GenerateHelpText(rootEnv))

rootEnv.Replace(CC = rootEnv['compiler'])

if rootEnv['debug'] == True:
  rootEnv.Append( CDEFINES =['DEBUG'] )
 
rootEnv['CFLAGS'] = Split(""" -Wall -std=c99 -lbfd """)

if rootEnv['CC'] == 'clang':
  rootEnv['CFLAGS'] = '-v'

print 'include installing'
rootEnv.Install( rootEnv['includedir'], includeheader )

print 'crate program: clang -Wall -v -std=c99 -lbfd -o gdb_breakpoints src/gdb_breakpoints.c'
gdbBreakpoint = rootEnv.Program( binsource,  binname )
print 'install program'
rootEnv.Install( rootEnv['prefix'], gdbBreakpoint )