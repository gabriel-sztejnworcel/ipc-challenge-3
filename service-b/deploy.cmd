net user challenge3 /del
net user challenge3 User123456 /add
net localgroup "Remote Desktop Users" challenge3 /add
echo logfile_path=app.log>app.config
start PsExec.exe -i -u "NT AUTHORITY\NETWORK SERVICE" %CD%\service-a.exe
start PsExec.exe -i -s -w %CD% %CD%\service-b.exe
