FROM fedora:42

# install app dependencies
RUN dnf -y install opencv-devel ninja-build cmake gcc-c++ ccache cxxopts-devel

# transfer src files to container
WORKDIR /app

COPY include/ ./include
COPY src/ ./src
COPY CMakeLists.txt .

# compile the code
RUN mkdir build \
    && cd build \
    && cmake -G Ninja .. \
    && ninja

# run the app
WORKDIR /app/build
ENTRYPOINT ["./MAP_ascii_from_image"]