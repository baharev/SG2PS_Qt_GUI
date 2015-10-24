
**Practically everything with the GUI is case sensitive**
=========================================================

The source code was searched for string literals with the following 
regex `\"(\\.|[^"])*\"`.


ConvertAllEps
-------------

It assumes that the EPS files in the subfolders of 

 - `5_PS_SEPARATED`, and
 - `6_WELL_PS_SEPARATED` have to be converted.

The EPS files are assumed to have `.eps` extension, stricly lower case.

It is assumed that the `ps2pdf` convert generates pdf files with extension
`.pdf`, and with the exact same name as its input EPS file was.


GUISettings
-----------

By default, the external programs SG2PS (back end) and the EPS to PDF 
converter ps2pdf are expected to be `sg2ps` and `ps2pdf`. 

Although the GUI is case sensitive, on Windows, the command `sg2ps` can 
invoke for example `SG2PS.exe` (note that it is case insensitive and has
an additinal `.exe` extension). This is Windows specific only.


InfoWidget
----------

The back end is supposed to work with the following extensions 
`.rgf`, `.set`, `.xy`, `.trj` (note that they must be lower case).

If a set of files in a directory have the same name ignoring the file 
extension, then they are assumed to belong to the same project. Note 
that this is again case sensitive. For example, if `abc.rgf` and 
`abc.set` are in the same directory, then they belong to the same 
project called `abc`. However, the file `Abc.xy` in the same directory
does not belong to the project `abc`.


Launcher
--------

The following command line flags must be understood by the back end: 

 - `-v` and the back end is supposed to return a single line string like
   `24 Oct 2015, 19:41:24`,
   
 - `--version-id` and the back end is supposed to return a single line 
   string like `20151024194124`.

The back end **must not** print a banner when executed with these flags.

MainWindow
----------



Runner
------

A new log file is created whenever the back end is run, **any existing 
`log.txt` in the same directory as the input files will be 
overwritten.** The log file is called `log.txt`; this name is 
hard-coded. Similarly, **any existing .set file will be overwritten** 
that has the same name as the project.

The back end is supposed to create a text file called 
`project_folder_name` in the directory of the input files and with a 
single line content, giving the generated project folder name (like 
`20151024-191518_DEMO`). This is necessary for the EPS to PDF 
conversions: The GUI must find the newly created output folder.

The Demo assumes the existence of a `demo.rgf` file. The GUI Settings 
are ignored when a project called `demo` is run, and the result 
directory is shown anyway, together with the following two result PDF 
files:

 - `5_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE.pdf`, and
 - `6_WELL_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE_TILTED.pdf`.



SettingsWidget
--------------

In the set file of the back end, the lines are assumed to look like:
`key:\tvalue`, that is, the key and the value are separated by `":\t"`. 
The back end assumes no new line at the end of the last line.



Known issues
============

The Advanced > GUI Settings is currently broken: the external programs
are apparently not found when given with full path. (Reason: 
ShellExecute?) This part of the code, responsible for executing external
programs, must be cleaned up.
