#include <stdio.h>
#include <CoreServices/CoreServices.h>

void mycallback(
        ConstFSEventStreamRef streamRef,
        void *clientCallBackInfo,
        size_t numEvents,
        void *eventPaths,
        const FSEventStreamEventFlags eventFlags[],
        const FSEventStreamEventId eventIds[])
{
    int i;
    char **paths = eventPaths;

    for (i=0; i<numEvents; i++) {
        /* flags are unsigned long, IDs are uint64_t */
        printf("Num Events: %zu - Change %llu in %s, flags %u\n", numEvents, eventIds[i], paths[i], eventFlags[i]);
    }
}

int main(int argc, char **argv) {
    CFStringRef path = CFSTR("{FULL_PATH_TO_THE_DIRECTORY_YOU_WANT_TO_WATCH}");

    CFArrayRef watching = CFArrayCreate(NULL, (const void **)&path, 1, NULL);

    void *callbackInfo = NULL; 

    FSEventStreamRef stream;

    CFAbsoluteTime latency = 3.0; // seconds

    stream = FSEventStreamCreate(
            NULL,
            &mycallback,
            callbackInfo,
            watching,
            kFSEventStreamEventIdSinceNow, // or previous event id
            latency,
            kFSEventStreamCreateFlagFileEvents
            );

    FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    FSEventStreamStart(stream);

    CFRunLoopRun();

    return 0;
}
