# Copyright (C) 2016 Ali Baharev <ali.baharev@gmail.com>
# All rights reserved.
# BSD license.

from distutils.core import setup
import py2exe

opts = { 'compressed': 1,
         'bundle_files': 2,
         #'optimize' : 2,
         'excludes': ['exportedFunctions', 'Tkconstants', 'tkinter', 
                      '_ssl', 'pyreadline', 'doctest', 
                      'optparse', 'calendar', 'email', 'pydoc', 
                      'pyexpat',
                      'matplotlib', 'PyQt4', 'PyQt4.QtGui', 'PyQt4.QtCore', ],
         
         'includes' : [ ],

         'packages': ['PyPDF2'],
         'dll_excludes': ['w9xpopen.exe'],
       }

setup(console = ['pdf_concat.py'], options = {'py2exe': opts })
