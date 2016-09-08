# libmapuid
Shared library mapping random OpenShift 3 container UIDs to well-known UID. Useful for applications which require a passwd entry for their running user.

For now the behaviour is hardcoded. For getpwuid and getpwuid_r calls all UIDs >= 1000000000 are mapped to UID 1001, which is user "default" in OpenShift base images and has a passwd entry.

## Usage

Dockerfile:

    RUN curl https://raw.githubusercontent.com/appuio/libmapuid/master/lib/libmapuid.so -o /usr/local/lib/libmapuid.so && \
        chmod 755 /usr/local/lib/libmapuid.so
    
    CMD ["/usr/bin/env", "LD_PRELOAD=/usr/local/lib/libmapuid.so", "mycommand", "myargs"]
    
## Building yourself

    mkdir build
    cd build
    cmake ..
    make
