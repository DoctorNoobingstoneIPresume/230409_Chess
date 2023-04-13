@echo off

printf "Running...\n{\n"
if not exist "_Build/Main.exe" goto :EOF
xtimeq "_Build/Main.exe" %* 2>&1 | tee "_run" | tee -a "_run_a"
printf "}\n\n"
