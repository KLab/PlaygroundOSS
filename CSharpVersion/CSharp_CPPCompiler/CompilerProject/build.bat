cls
flex.exe -i -c -n -I -olexParser.inc csharp.l
bison.exe -t --debug --verbose --yacc --output=csharpCompiler.cpp csharp.y
