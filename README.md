# C++ HTTP SERVER

This is a barebones http server that serves HTML, css, images, and more.

If compiling within VSCode these are the settings I used to run the application within .vscode/settings.json

```
{
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: g++.exe build all files",
      "command": "C:/msys64/ucrt64/bin/g++.exe",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "${workspaceFolder}/main.cpp", // List all .cpp files explicitly
        "${workspaceFolder}/TcpListener.cpp", // Add other .cpp files here
        "${workspaceFolder}/MultiClientChat.cpp", // Add other .cpp files here
        "${workspaceFolder}/WebServer.cpp", // Add other .cpp files here
        "-o",
        "${workspaceFolder}/output.exe", // Output executable
        "-lws2_32" // Link against the Winsock library
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "Task generated by Debugger."
    }
  ],
  "version": "2.0.0"
}
```
