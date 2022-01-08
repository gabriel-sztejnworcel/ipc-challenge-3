# PSM Securithon 2021
## Windows Interprocess Commnunication - Challenge #3

In this exercise, we have two applications that simulate Windows services:
1. Service A: an HTTP server that accepts commands to run. The idea is to simulate an application with an RCE vulnerability. To run commands, use the following URL: http://localhost:8080/run?cmd=notepad.exe (here we run notepad.exe, you can replace it with your command)
2. Service B: an HTTP server that accepts log requests and writes them to a log file. To send a log request, use the following URL: http://localhost:8081/log?msg=hello (replace "hello" with your message)

The project also contains a deployment script, deploy.cmd, that:
1. Creates a local user, challenge3, to simulate the attacker
2. Run service A with the NETWORK SERVICE account
3. Run service B with the SYSTEM account

Your goal is to run code as SYSTEM, using the techniques we discussed in class. You are allowed to make changes in the folder where the applications are deployed (but you cannot replace the executables).
