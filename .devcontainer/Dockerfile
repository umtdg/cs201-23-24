FROM oraclelinux:8.8

RUN dnf install -y gcc gcc-c++ gdb cmake libasan valgrind wget git

# build and install cppcheck
RUN wget -O /tmp/cppcheck-2.12.0.tar.gz "https://github.com/danmar/cppcheck/archive/2.12.0.tar.gz"
RUN tar -xzf /tmp/cppcheck-2.12.0.tar.gz -C /tmp
RUN cd /tmp/cppcheck-2.12.0 \
    && mkdir -p build \
    && cmake -B build -S . \
    && cmake --build build --target install
RUN rm -rf /tmp/cppcheck-2.12.0 /tmp/cppcheck-2.12.0.tar.gz

# build and install googletest
RUN git clone https://github.com/google/googletest /tmp/googletest
RUN cd /tmp/googletest \
    && mkdir -p build \
    && cmake -B build -S . \
    && cmake --build build --target install
RUN rm -rf /tmp/googletest

# codeql
RUN wget -O /tmp/codeql-bundle.tar.gz https://github.com/github/codeql-action/releases/download/codeql-bundle-v2.15.0/codeql-bundle-linux64.tar.gz
RUN tar -xzf /tmp/codeql-bundle.tar.gz -C /tmp
RUN rm -rf /tmp/codeql-bundle.tar.gz
ENV PATH=${PATH}:/tmp/codeql


ENTRYPOINT [ "/sbin/init" ]
