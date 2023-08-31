FROM quay.io/school21/alpine:latest

RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools \
    texlive \
    texinfo \
    docker

RUN mkdir /test 

COPY . /project

WORKDIR "project"

RUN chmod 777 docker_dvi.sh
RUN ./docker_dvi.sh 


ENTRYPOINT ["/bin/bash"]