#!/usr/bin/env python
# Copyright (C) 2016 by Ali Baharev <ali.baharev@gmail.com>
# All rights reserved.
# BSD license.
from os import walk
from os.path import normpath, join
from sys import argv, exit
from PyPDF2 import PdfFileMerger

def main():
    root = normpath(argv[1])
    pdfs_merged = argv[2]
    merger = PdfFileMerger()
    for path, f in visit(root, '.pdf'):
        merger.append(file((join(path, f)), 'rb'))
    merger.write(pdfs_merged)

def visit(root, extension):
    for path, dirs, files in walk(root):
        dirs[:] = sorted(dirs)
        files = sorted(f for f in files if f.endswith(extension))
        for f in files:
            yield path, f

if __name__ == '__main__':
    try:
        main()
    except:
        exit(1)

