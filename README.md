### What is this?

I wanted to learn how to monitor file changes in a directory on macOS. As such, I implemented a simple program to listen for changes on a specific directory and print the information to stdout.

### What did I learn?

* How to interface with Apples File System Events API
* That if I want more fine grained information I should is the [kqueue](https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/kevent.2.html) API.
* For debugging - at least for LLDB - if you set a break point beyond where CFRunLoopRun() is called the debugger will spin up a new thread to run that such that you can look at the values in the callback function.

### Additional Resource

