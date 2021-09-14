#!/bin/bash

WS_DIR=$(readlink -f $(dirname $0)/../../../)
REPO_NAME="purduearc/rocket-league-test-repository-please-ignore"
CONTAINER_NAME="arc-rocket-league-dev"
echo "mounting host directory $WS_DIR as container directory /home/$USER/catkin_ws"

docker run --rm -it \
    -e USER \
    -e DISPLAY \
    -e NVIDIA_DRIVER_CAPABILITIES=all \
    -v $XAUTHORITY:/home/$USER/.Xauthority \
    -v $WS_DIR:/home/$USER/catkin_ws \
    -v ~/windows/Downloads:/home/$USER/Downloads \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v /dev:/dev \
    --name $CONTAINER_NAME \
    $@ \
    $REPO_NAME:local \
    $DOCKER_CMD
