Handler Agent
===

Handler Agent is an application for MS-Windows. The programmes compiled by mingw-gcc are also launch with a console, 
and for the languages like Haskell, you can not close the console, because the exception will raise for invailed standard i/o handlers.
So I write this programme to "agent" the handlers of the console.

## Usgae

If you want to use this, this part will be helpful.

If there is a program named `a.exe`, you need to rename that programme to `a.hreal.exe`. Then you need to copy one this programme, and rename it to `a.exe`.
Then you can launch it.

## TODO

This programme can not pass the params.